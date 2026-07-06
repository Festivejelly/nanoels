# Motion Planner Starvation - Problem & Solutions

## The Problem

The current `G00_01()` function uses linear interpolation: it breaks a move into `N` chunks, steps to each intermediate position, waits for the axis to arrive (`gcodeWaitNear`), then moves to the next chunk. This works fine at low speeds but starves the planner at high feedrates.

**Example: `G1 Z50 F900`**

With `LINEAR_INTERPOLATION_PRECISION = 0.1`, a 50mm move on a typical Z axis (e.g. 200 steps/mm × 50mm = 10,000 steps) gives:
```
chunks = round(10000 * 0.1) = 1000 chunks
```
At 900mm/min (15mm/sec), the machine traverses each chunk in ~0.05ms. The ESP32 must compute the next target, call `stepToContinuous`, and complete `gcodeWaitNear` within that window. It can't — so the axis catches up, briefly decelerates, and gets the next chunk late. This manifests as velocity ripple or stuttering.

**Root cause:** The planner is synchronous and blocking. G-code parsing, chunk calculation, and `gcodeWaitNear` all happen on the CPU, interleaved with the actual stepping. At high speeds the machine outruns the software.

---

## Architecture Context

- **Platform:** ESP32 with FreeRTOS
- **Stepping model:** `pendingPos` counter — no step buffer/queue
- **Acceleration:** Per-step delta inside `moveAxis()`, using `continuous` flag to prevent premature deceleration
- **Synchronisation:** `gcodeWaitNear()` spins until `pendingPos <= 10 steps`
- **No lookahead** between G-code blocks

---

## Options

### Option 1 — Reduce Chunk Density (Current Partial Fix for G0)

Already done for rapid moves: `RAPID_LINEAR_INTERPOLATION_PRECISION = 0.02` (5× fewer chunks than G1).

**Extend to G1:** Make precision feed-adaptive — fewer chunks at higher feedrates.

```cpp
float precision = max(0.005f, LINEAR_INTERPOLATION_PRECISION * (600.0f / gcodeFeedMmPerMin));
```

**Pros:** Simple, no architecture change.
**Cons:** At very low chunk counts, linear interpolation degrades — two-axis coordinated moves can drift off the intended line. Also doesn't fix the fundamental issue, just pushes it to a higher feedrate ceiling.

---

### Option 2 — Feedrate-Adaptive Wait Epsilon

Instead of waiting for `pendingPos <= 10 steps`, compute the epsilon dynamically based on the expected distance the machine will travel in one planning cycle.

```cpp
long adaptiveEpsilon = max(10L, (long)(gcodeFeedDuPerSec * loopCycleUs / 1000000L));
```

**Pros:** Simple. Lets the machine run ahead by exactly one planning cycle worth of distance.
**Cons:** Still fundamentally synchronous — doesn't eliminate the stall, just shrinks it. Requires knowing `loopCycleUs`.

---

### Option 3 — Remove gcodeWaitNear Entirely for High-Speed Moves

At high speeds, `gcodeWaitNear` causes a full synchronisation stall between every chunk. If the machine is running much faster than the planner, the axis will overshoot the wait epsilon anyway.

**Approach:** Skip `gcodeWaitNear` when above a speed threshold, only call `gcodeWaitStop` at the end of the move.

```cpp
for (long i = 0; i < chunks; i++) {
    if (controllerState != STATE_RUN) return;
    float scale = i / float(chunks);
    stepToContinuous(&x, xStart + xDiff * scale);
    stepToContinuous(&z, zStart + zDiff * scale);
    if (ACTIVE_A1) stepToContinuous(&a1, a1Start + a1Diff * scale);
    if (gcodeFeedDuPerSec < HIGH_SPEED_THRESHOLD)
        gcodeWaitNear();
}
```

**Pros:** Cheap to implement, preserves existing logic for slow moves.
**Cons:** Without `gcodeWaitNear`, the axis's `pendingPos` accumulates. The `continuous` flag prevents deceleration mid-move — which is correct — but the axis may be tens of thousands of steps "behind" at any moment, meaning a sudden stop (`E-stop`, `controllerState != STATE_RUN`) has no way to brake cleanly until `pendingPos` drains.

---

### Option 4 — Precomputed Trajectory Buffer with Atomic Handoff

Replace the chunk-by-chunk loop in `G00_01()` with a two-phase approach:

1. **Plan phase:** `G00_01()` computes the entire trajectory into a **local temporary array** before touching the axis struct. `moveAxis()` is completely unaware of this — it just keeps draining `pendingPos` as normal.
2. **Handoff phase:** Once the full trajectory is ready, assign the buffer pointer to the axis struct in one operation. `moveAxis()` then starts consuming it independently.

This ensures `moveAxis()` never sees a half-built trajectory — it either has the old state or the complete new one, never something in between.

#### Changes to G00_01()

The chunk `for` loop gets replaced:

```
Current:
  for each chunk:
    compute position
    call stepToContinuous()   ← blocks on mutex each time
    gcodeWaitNear()           ← stalls waiting for axis to arrive

Proposed:
  // Phase 1: build trajectory locally (no axis access)
  long tempX[chunks], tempZ[chunks], tempA1[chunks];
  for each chunk:
    compute and store position in temp arrays

  // Phase 2: atomic handoff to axis struct
  assign temp arrays to axis.trajBuffer (under mutex)
  set axis.trajHead = 0, axis.trajTail = chunks

  // Phase 3: wait for buffer to drain (replaces gcodeWaitNear loop)
  wait until trajHead == trajTail

  // Phase 4: final position (unchanged)
  stepToContinuous to xEnd/zEnd/a1End
  gcodeWaitStop()
```

#### Changes to Axis struct

```cpp
struct Axis {
  // ... existing fields ...
  long* trajBuffer;   // pointer to precomputed position array
  int   trajHead;     // next index for moveAxis() to consume
  int   trajTail;     // total entries (set at handoff, not changed after)
};
```

#### Changes to moveAxis()

`moveAxis()` works purely on `pendingPos` — it decrements it one step at a time and issues the pulse itself. It doesn't call any higher-level function. So when `pendingPos` hits 0, we load the next trajectory entry by computing the new `pendingPos` directly, the same way `stepToContinuous()` does it, while we already hold the mutex:

```cpp
// At the top of moveAxis(), before the early return on pendingPos == 0:
if (a->pendingPos == 0 && a->trajHead < a->trajTail) {
    if (stopRequested) {
        a->trajHead = a->trajTail;  // discard buffer
    } else {
        long newPos = a->trajBuffer[a->trajHead++];
        a->continuous = (a->trajHead < a->trajTail); // continuous until last entry
        a->pendingPos = newPos - a->motorPos;  // backlash already baked in — see below
    }
}
```

This mirrors exactly what `stepToContinuous()` does when setting `pendingPos`, so the acceleration logic in `moveAxis()` behaves identically.

#### Backlash handling

`stepTo()` currently computes backlash per-call:
```cpp
pendingPos = newPos - a->motorPos - (newPos > a->pos ? 0 : a->backlashSteps);
```

Since G0/G1 moves **cannot change direction mid-move** (no arcs), the direction is known upfront from `xDiff`/`zDiff`/`a1Diff`. So backlash only needs to be handled **once, on the first trajectory entry**.

When populating the temp buffer in `G00_01()`, the first entry gets the backlash offset baked in:
```cpp
// Before filling the buffer, compute the backlash offset for each axis
long xBacklash  = (xDiff  < 0) ? x.backlashSteps  : 0;
long zBacklash  = (zDiff  < 0) ? z.backlashSteps  : 0;
long a1Backlash = (a1Diff < 0) ? a1.backlashSteps : 0;

// First entry: subtract backlash from motorPos baseline so moveAxis() takes up the slack
tempX[0]  = xStart  + xDiff  * scale - xBacklash;   // entry 0 only
// Entries 1..N-1: plain positions, no backlash term
tempX[i]  = xStart  + xDiff  * scale;               // i > 0
```

Then `moveAxis()` can use the simple form `pendingPos = newPos - a->motorPos` for all entries — the backlash is already encoded in the first position.

#### Multi-axis synchronisation

Because all three axes receive the same number of trajectory entries (computed from the same `chunks` value in `G00_01()`), and each axis independently consumes one entry per `moveAxis()` call, they naturally stay in sync — the same way they do now, but without `gcodeWaitNear` stalls.

#### Memory

A 50mm G1 move at `LINEAR_INTERPOLATION_PRECISION = 0.1` on a 200 step/mm axis gives 1000 chunks.
`3 axes × 1000 entries × 4 bytes = 12KB` — well within ESP32's 520KB SRAM.

**Do NOT stack-allocate the temp arrays** (e.g. `long tempZ[chunks]`). FreeRTOS tasks have limited stack (typically 4–8KB). A 1000-entry `long` array alone is 4KB — three of them would immediately overflow the stack and cause a crash or silent corruption. Instead use either:
- A **statically sized global scratch buffer** (simplest — allocate worst-case size once at startup)
- `malloc`/`free` around the plan phase (fine on ESP32, but adds risk if heap is fragmented)

#### E-stop

`stopRequested` is already a `volatile bool` checked throughout the codebase. In `moveAxis()`, before consuming the next trajectory entry, check it:

The check lives at the top of `moveAxis()` as shown above — `stopRequested` is read before loading the next entry, so the buffer is discarded cleanly without needing a separate flush call.

Because `stopRequested` is `volatile`, no mutex is needed to read it safely from `moveAxis()`. The buffer drains naturally — no need to zero `pendingPos` forcefully, the current step just completes and then the buffer is marked empty.

**Pros:**
- `G00_01()` does all maths upfront in one burst — no per-chunk stalls
- `moveAxis()` never waits for the planner; consumes targets as fast as it steps
- Minimal change to `moveAxis()` — just one extra check when `pendingPos` hits 0
- Atomic handoff means no partial-trajectory race condition

**Cons:**
- Requires adding `trajBuffer/Head/Tail` to the Axis struct
- Memory for trajectory must be managed (static scratch buffer recommended)
- `G00_01()` must finish planning before motion starts (one burst of CPU upfront, then free)

**Effort:** Medium. Focused change — only `G00_01()` and `moveAxis()` are affected.

---

### Option 5 — DDA (Digital Differential Analyser) Stepped in Interrupt / Timer

Replace chunk-based interpolation with a hardware-timer-driven DDA that computes and issues steps directly in an ISR, completely independently of the FreeRTOS task loop.

The G-code task sets up the DDA parameters (start, end, speed) and then waits on a semaphore. The ISR steps both axes in real time at the required ratio, then signals completion.

**Pros:**
- Eliminates planner starvation entirely — the ISR runs at the step rate, not the task rate
- Velocity is exact regardless of CPU load
- Standard approach in Grbl, Marlin, etc.

**Cons:**
- Large architectural change — `moveAxis()` and the step logic must be ISR-safe
- ISR must be very short (no floating point, no FreeRTOS calls)
- Requires pre-computing DDA parameters before the move starts (one planning cycle latency)
- Coordinating E-stop and state changes with ISR is tricky (volatile flags, critical sections)

**Effort:** High. This is the "right" solution for a serious CNC controller and is how production firmware (Grbl, Klipper) works.

---

### Option 6 — Klipper-Style "Move Queue" with Lookahead

Pre-parse multiple G-code blocks, compute a velocity profile across the entire queue (junction deviation, cornering speed), then feed a pre-planned trajectory to the stepper driver. This is what Klipper does on a Raspberry Pi + MCU split.

**Pros:**
- Best possible motion quality
- Handles cornering, jerk, and blending automatically

**Cons:**
- Extremely complex to implement from scratch on a single ESP32
- Probably overkill for a lathe (mostly single-axis or two-axis moves, rarely rapid multi-axis cornering)

**Effort:** Very high.

---

## Recommendation

| Priority | Option | Effort | Impact |
|----------|--------|--------|--------|
| **Immediate** | Option 3 — skip `gcodeWaitNear` above threshold | Low | Fixes stutter for pure high-speed single-axis G1 moves |
| **Short term** | Option 1 — feed-adaptive chunk density | Low | Raises the feedrate ceiling |
| **Medium term** | Option 4 — precomputed trajectory buffer | Medium | Decouples planner from executor cleanly, no race conditions |
| **Long term** | Option 5 — DDA in timer ISR | High | Eliminates the problem class entirely |

Option 3 + 1 can be done today with minimal risk. Option 4 is the right structural fix. Option 5 is the correct long-term architecture if pushing toward production-quality high-speed machining.

---

## Notes on This Codebase

- `LINEAR_INTERPOLATION_PRECISION = 0.1` is in `h4.ino` line ~123
- `RAPID_LINEAR_INTERPOLATION_PRECISION = 0.02` is in `h4.ino` line ~124
- `gcodeWaitNear()` waits for `pendingPos <= GCODE_WAIT_EPSILON_STEPS` (10 steps)
- `continuous = true` suppresses deceleration inside `moveAxis()` — critical for interpolated moves
- The ESP32 has two cores; currently `moveAxis()` and the G-code task share core 1 via FreeRTOS cooperative scheduling
