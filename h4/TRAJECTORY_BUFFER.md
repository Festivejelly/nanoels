# Trajectory Buffer — Implementation Notes

## Why this approach was chosen

The existing `G00_01()` function uses a synchronous chunk loop: it calculates one intermediate
position, hands it to `stepToContinuous()`, then spin-waits in `gcodeWaitNear()` until the axis
arrives within 10 steps before calculating the next chunk. At high feedrates or on moves with many
small segments (tapers, chamfers, CAM-generated arcs), the axis catches up to the planner before
the next chunk is ready, briefly decelerating between every chunk. This produces velocity ripple
and audible stuttering on coordinated multi-axis moves.

Several options were considered (see `MOTION_PLANNER_OPTIONS.md`):

| Option | Approach | Verdict |
|--------|----------|---------|
| 1 — feed-adaptive chunk density | Fewer chunks at high speed | Doesn't fix root cause |
| 2 — adaptive wait epsilon | Shrink wait window dynamically | Still fundamentally synchronous |
| 3 — skip gcodeWaitNear above threshold | No wait at high speed | E-stop safety concern |
| **4 — precomputed trajectory buffer** | **Plan all chunks upfront, hand off atomically** | **Chosen** |
| 5 — DDA in timer ISR | Hardware-timer driven stepping | Correct long-term, high effort |
| 6 — Klipper-style move queue | Full lookahead across G-code blocks | Overkill for a lathe |

**Option 4 was chosen** because it fixes the root cause (synchronous planner blocking the executor)
with a focused, low-risk change confined to two functions (`G00_01()` and `moveAxis()`), while
preserving all existing acceleration, backlash, E-stop, and threading behaviour.

## How it differs from the original

**Before:**
```
for each chunk:
    compute position
    stepToContinuous()     ← takes mutex, sets pendingPos
    gcodeWaitNear()        ← spin-waits until axis within 10 steps
```
The planner and the axis leapfrog each other. The axis decelerates every time it catches up.

**After:**
```
// Phase 1 — plan (no axis access, no mutex)
for each chunk:
    compute and store position in scratch buffer

// Phase 2 — atomic handoff (under mutex)
assign buffer pointer + set trajHead=0, trajTail=chunks on each axis

// Phase 3 — wait for buffer to drain (replaces chunk loop wait)
spin until trajHead == trajTail

// Phase 4 — final position + gcodeWaitStop (unchanged)
```
`moveAxis()` consumes the pre-built queue as fast as it steps. The planner is completely out of the
way before motion starts. The `continuous` flag is set true for all entries except the last, so
the axis never decelerates mid-buffer.

## Scope

**In scope:**
- `G00_01()` — replaced chunk loop with two-phase plan + handoff
- `moveAxis()` — one extra check when `pendingPos` hits 0: load next trajectory entry if available
- `Axis` struct — three new fields: `trajBuffer`, `trajHead`, `trajTail`
- Static global scratch buffers: `TRAJ_BUF_X`, `TRAJ_BUF_Z`, `TRAJ_BUF_Y`

**Explicitly out of scope:**
- Threading mode (encoder-slaved Z) — untouched, stable, separate code path
- All other G-code commands
- `moveAxis()` step/acceleration/direction logic — identical to before
- `gcodeWaitStop()` at the end of each move — unchanged

## Memory

Static scratch buffers sized to worst-case chunks. At `LINEAR_INTERPOLATION_PRECISION = 0.1` on
a 1000 step/mm Z axis, a 300mm move = 30,000 chunks × 4 bytes = 120KB per axis. Buffer sized at
`TRAJ_BUFFER_SIZE = 32000` entries per axis (384KB total) — within ESP32-S3's 512KB SRAM. Uses PSRAM where available as the NR16R8 has 8mb of it!

Buffers are global and reused across moves. No dynamic allocation.

## E-stop

`stopRequested` is already `volatile bool`. In `moveAxis()`, before loading the next trajectory
entry, if `stopRequested` is set, `trajHead` is set to `trajTail` to discard the remaining buffer.
No new synchronisation needed — the current step completes naturally, then motion stops.

## Backlash

G0/G1 moves cannot change direction mid-move, so backlash is computed once from the sign of
`xDiff`/`zDiff`/`yDiff` and baked into trajectory entry 0 only. All subsequent entries use plain
`newPos - motorPos`.

## Testing

Manual testing on hardware. Suggested test cases:
- Single-axis G1 at various feedrates — should behave identically to before
- Two-axis taper move (simultaneous X+Z) — expect smoother, no audible stutter
- Long G1 with many small CAM segments — expect continuous motion at full feedrate
- E-stop mid-move — expect clean stop with no runaway
- Rapid G0 move — expect no regression
