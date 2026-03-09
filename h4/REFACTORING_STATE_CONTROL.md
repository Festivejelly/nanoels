# State Control Refactoring Plan

## Goal
Replace the confusing `isOn` flag and `MODE_GCODE` with clean state-based control. Eliminate blocking loops where possible.

---

## Current Architecture (Messy)

```
isOn = true/false       → Used for state AND execution control (confusing!)
MODE_NORMAL            → Normal operations
MODE_GCODE             → Gcode execution (redundant with state!)
MODE_THREAD            → Threading operations
```

**Problems:**
- `isOn` does double duty (state + control)
- `MODE_GCODE` is redundant
- Blocking loops in M0 handler
- State not clearly represented

---

## Target Architecture (Clean)

### States (What's happening)
```cpp
enum ControllerState {
  STATE_IDLE,     // Ready, waiting for commands. MPG allowed.
  STATE_RUN,      // Executing gcode. MPG blocked.
  STATE_HOLD,     // Paused (M0/M1). MPG blocked. Waiting for resume.
  STATE_ALARM     // Emergency stop. Everything blocked.
};
```

### Modes (Operation type)
```cpp
enum Mode {
  MODE_NORMAL,    // Normal operations
  MODE_THREAD     // Threading (spindle-synced)
};
// Remove MODE_GCODE entirely!
```

### Control Logic
```cpp
// MPG allowed?
if (controllerState == STATE_IDLE && mode != MODE_THREAD)

// Gcode motion allowed?
if (controllerState == STATE_RUN)

// Threading allowed?
if (mode == MODE_THREAD)
```

---

## Refactoring Steps

### ✅ **DONE** - Phase 1: Foundation
- [x] Add `ControllerState` enum
- [x] Add `controllerState` variable
- [x] Update status responses to show state
- [x] Add basic state transitions in `setIsOnFromLoop()`
- [x] Update M0 handler to use HOLD state and send "ok" immediately

---

### ✅ **DONE** - Phase 2: Remove MODE_GCODE

**Goal:** Eliminate MODE_GCODE, use STATE_RUN instead

**What was completed:**
- [x] Removed gcodeInitialized block and variable (lines 1005-1015, line 590)
- [x] Removed all MODE_GCODE references from codebase
- [x] Removed MODE_GCODE from enum definition
- [x] Verified setIsOnFromLoop() already handles states correctly (from Phase 1)

#### Step 1: Find all MODE_GCODE references
```bash
# Search for MODE_GCODE usage
grep -n "MODE_GCODE" h4.ino
```

#### Step 2: Replace MODE_GCODE checks
**Before:**
```cpp
if (mode == MODE_GCODE) { ... }
```

**After:**
```cpp
if (controllerState == STATE_RUN) { ... }
```

**Files to update:**
- Line ~988: `if (mode != MODE_GCODE)` in taskGcode
- Line ~4431: `if (showTacho || mode == MODE_GCODE)` (already fixed)
- Any other MODE_GCODE references

#### Step 3: Update setIsOnFromLoop()
**Before:**
```cpp
if (isOn) {
  mode = MODE_GCODE;  // ← Remove this
  controllerState = STATE_RUN;
} else {
  mode = MODE_NORMAL;
  controllerState = STATE_IDLE;
}
```

**After:**
```cpp
if (isOn) {
  // Don't set mode here anymore
  if (controllerState != STATE_HOLD) {
    controllerState = STATE_RUN;
  }
} else {
  if (controllerState != STATE_HOLD) {
    controllerState = STATE_IDLE;
  }
}
```

#### Step 4: Remove MODE_GCODE from enum
Delete it from the Mode enum definition (around line ~80-90)

---

### ✅ **DONE** - Phase 3: Replace isOn State Checks

**Goal:** Stop using `isOn` as a state indicator. Use `controllerState` instead.

**What was completed:**
- [x] Audited all isOn usage and categorized as state checks vs setters
- [x] Replaced all isOn state checks with controllerState checks
- [x] Updated MPG blocking logic (line 852)
- [x] Updated motion interpolation early-exit (line 2482)
- [x] Updated G4 dwell loop (lines 2527, 2530)
- [x] Updated G0/G1 motion guard (line 2539)
- [x] Updated async timer check (line 1635)
- [x] Updated setModeFromLoop check (line 1668)
- [x] Updated setTurnPasses check (line 1680)
- [x] Updated threading loops (lines 3467, 3580, 3805, 3808)
- [x] Updated setIsOnFromLoop early-return check (line 1760)
- [x] Updated debug output to show state (line 1160)
- [x] Updated main loop threading check (line 4222)

**Remaining isOn references (for Phase 4/5):**
- Setters in setIsOnFromLoop() (lines 1764, 1776)
- Setters in M0 handler (lines 2604, 2637)
- Declaration and nextIsOn variable (lines 276, 278)
- Initialization in setup() (line 1366)
- Saving previous state in threading (line 3744)

#### Step 1: Audit all isOn usage
```bash
# Find all isOn checks
grep -n "if.*isOn" h4.ino
grep -n "isOn\s*=" h4.ino
```

Create a list of each usage and categorize:
- **Category A:** State checks ("are we running?")
- **Category B:** Execution control ("can we move?")
- **Category C:** Mode transitions

#### Step 2: Replace Category A (State Checks)
**Before:**
```cpp
if (isOn) {
  // We're running gcode
}
```

**After:**
```cpp
if (controllerState == STATE_RUN) {
  // We're running gcode
}
```

**Common locations:**
- Line ~876: `if (isOn)` in applyMPGMovement → use state
- Line ~1174: Debug printing
- Line ~2561: `while (millis() - startTime < dwellMs && isOn)` in G4

#### Step 3: Replace Category B (Execution Control)
**Before:**
```cpp
if (!isOn) {
  Serial.println("error: motion not allowed when stopped");
  return false;
}
```

**After:**
```cpp
if (controllerState != STATE_RUN) {
  Serial.println("error: motion not allowed when not running");
  return false;
}
```

**Common locations:**
- Line ~2554: Motion blocking in handleGcode

#### ✅ **DONE** - Step 4: Handle setIsOnFromTask() and setIsOnFromLoop()

**What was completed:**
- [x] Removed isOn assignments from setIsOnFromLoop() (lines 1764, 1776)
- [x] Removed isOn assignments from M0 handler (lines 2604, 2637)
- [x] Kept setIsOnFromTask() unchanged (only sets flags - works correctly)
- [x] State transitions now purely use controllerState

**Remaining for Phase 5:**
- Declaration: `bool isOn` (line 276)
- Initialization: `isOn = false` in setup() (line 1366)
- Unused `previousIsOn` variable (line 3742 - never restored)

**Original plan:**
```cpp
// Old
void setIsOnFromTask(bool on)

// New - option 1: Keep name but change internals
void setIsOnFromTask(bool on) {
  if (on) {
    controllerState = STATE_RUN;
  } else {
    if (controllerState != STATE_HOLD) {
      controllerState = STATE_IDLE;
    }
  }
  nextIsOnFlag = true;
}

// New - option 2: Replace with explicit state setters
void setControllerState(ControllerState newState) {
  controllerState = newState;
}
```

**Recommendation:** Keep the existing function names initially but change their implementation to use states. This minimizes breaking changes.

---

### ✅ **DONE** - Phase 4: Eliminate M0 Blocking Loop

**Goal:** Remove the while loop from M0 handler, handle resume at the gcode task level

**What was completed:**
- [x] Removed blocking while loop from M0 handler (lines 2612-2636)
- [x] Simplified M0 handler to just set STATE_HOLD and return immediately
- [x] Updated '~' resume handler to check for STATE_HOLD and transition to STATE_IDLE
- [x] Added HOLD state check in main gcode loop to skip command processing
- [x] Real-time commands ('~', '?', '!') still processed even in HOLD state

#### Current M0 Handler (with blocking loop)
```cpp
if (op == 0 || op == 1) {
  controllerState = STATE_HOLD;
  Serial.println("ok");

  // BLOCKING LOOP - keeps gcode task stuck here
  while (!resumed && emergencyStop == ESTOP_NONE) {
    if (Serial.available() > 0) {
      char c = Serial.peek();
      if (c == '~') { /* resume */ }
      // ...
    }
    taskYIELD();
  }

  controllerState = STATE_IDLE;
  return false;
}
```

#### New Approach: State-Based Flow Control

**Step 1: Add resume flag**
```cpp
volatile bool resumeRequested = false;
```

**Step 2: Update M0 handler (NO LOOP)**
```cpp
if (op == 0 || op == 1) {
  controllerState = STATE_HOLD;
  resumeRequested = false;
  Serial.println("ok");
  return false;  // Just return immediately
}
```

**Step 3: Handle '~' in main gcode loop**

Add to taskGcode() character processing (around line 1001):

```cpp
if (Serial.available() > 0) {
  receivedChar = Serial.read();

  // Handle real-time commands first
  if (receivedChar == '~') {
    if (controllerState == STATE_HOLD) {
      Serial.println("resume received");
      controllerState = STATE_IDLE;
      resumeRequested = true;
    }
    continue;  // Don't process as regular command
  }

  if (receivedChar == '!') {
    Serial.println("feed hold");
    setIsOnFromTask(false);
    continue;
  }

  if (receivedChar == '?') {
    printStatusResponse();
    continue;
  }

  // ... rest of character processing
}
```

**Step 4: Skip command processing when in HOLD**

Add state check in taskGcode() loop (around line 1037):

```cpp
// Don't process new commands when in HOLD state
if (controllerState == STATE_HOLD) {
  taskYIELD();
  continue;  // Skip to next iteration
}

// ... existing command processing
if (charCode < 32 && gcodeCommand.length() > 1) {
  if (handleGcodeCommand(gcodeCommand)) {
    Serial.println("ok");
  }
  gcodeCommand = "";
}
```

**Benefits:**
- No blocking loop in M0 handler
- Real-time commands ('~', '!', '?') handled at top level
- Cleaner separation of concerns
- State machine clearly visible

---

### ✅ **DONE** - Phase 5: Clean Up isOn Remnants

**What was completed:**
- [x] Removed `bool isOn` declaration (line 276)
- [x] Removed `isOn = false` initialization in setup() (line 1366)
- [x] Removed unused `bool previousIsOn` variable (line 3746)
- [x] Kept `nextIsOn` variable (still needed for cross-task flag mechanism)

**Result:** `isOn` is completely removed from the codebase! Only `nextIsOn` remains (actively used).

#### Original Step 1: Check if isOn is still needed
After phases 2-4, search for remaining `isOn` usage:
```bash
grep -n "isOn" h4.ino
```

#### Step 2: Either remove entirely or rename
**Option A: Remove completely**
If all checks replaced with state, just delete:
```cpp
bool isOn = false;  // DELETE THIS LINE
```

**Option B: Keep for compatibility but derive from state**
```cpp
// Kept for backward compatibility during transition
bool isOn() {
  return controllerState == STATE_RUN;
}
```

**Option C: Rename to clarify purpose**
```cpp
bool gcodeActive = false;  // Clearer name
```

**Recommendation:** Try to remove completely. If some code still needs it, use Option B temporarily.

---

## Testing Checklist

After each phase, test these scenarios:

### Basic Gcode Execution
- [ ] Send simple G0 move → should execute
- [ ] Send multiple commands → should queue properly
- [ ] Status shows "Run" during motion, "Idle" when stopped

### M0 Pause/Resume
- [ ] Send gcode with M0 → should pause
- [ ] Status shows "Hold" immediately
- [ ] Sender receives "ok" right away (no deadlock)
- [ ] Send '~' → should resume
- [ ] Status shows "Idle" after resume
- [ ] Next gcode line executes

### MPG Jogging
- [ ] Jog when Idle → should work
- [ ] Jog when Running → should block
- [ ] Jog when Hold → should block
- [ ] Jog when Thread → should block

### Threading
- [ ] Start threading → should work
- [ ] MPG blocked during thread
- [ ] State shows correctly

### Emergency Stop
- [ ] Trigger estop → should stop everything
- [ ] State shows "Alarm"
- [ ] Everything blocked

### Status Queries
- [ ] Send '?' during idle → shows "Idle"
- [ ] Send '?' during run → shows "Run"
- [ ] Send '?' during hold → shows "Hold"
- [ ] Send '?' during alarm → shows "Alarm"

---

## Migration Strategy

### Day 1: Foundation (Already Done!)
- ✅ State enum added
- ✅ Status responses updated
- ✅ M0 sends "ok" immediately

### Day 2: Remove MODE_GCODE (Done!)
- ✅ Phase 2 steps 1-4
- ✅ Removed gcodeInitialized block
- ✅ Removed all MODE_GCODE references
- TODO: Test gcode execution
- TODO: Test status responses

### Day 3: Replace isOn Checks (Done!)
- ✅ Phase 3 steps 1-3
- ✅ Updated all state checks with controllerState
- ✅ Replaced 13+ isOn checks across codebase
- TODO: Test MPG blocking
- TODO: Test gcode motion
- TODO: Test threading operations

### Day 4: Refactor State Transitions (Done!)
- ✅ Phase 3 step 4
- ✅ Removed isOn assignments from setIsOnFromLoop()
- ✅ Removed isOn assignments from M0 handler
- ✅ State transitions now purely use controllerState
- TODO: Test state transitions
- TODO: Test pause/resume
- TODO: Test threading operations

### Day 5: Eliminate M0 Blocking Loop (Done!)
- ✅ Phase 4 all steps
- ✅ Removed blocking loop from M0 handler
- ✅ Updated '~' handling to be state-aware
- ✅ Added HOLD state check in main loop
- TODO: Test pause/resume thoroughly
- TODO: Test real-time commands

### Day 6: Clean Up (Done!)
- ✅ Phase 5
- ✅ Removed isOn completely (declaration, initialization, unused variables)
- ✅ Kept nextIsOn/nextIsOnFlag (still needed for flag mechanism)
- TODO: Final testing of all functionality

### Day 7: Naming Cleanup (Done!)
- ✅ Renamed nextIsOn → nextRunning
- ✅ Renamed nextIsOnFlag → nextRunningFlag
- ✅ Renamed setIsOnFromTask → setRunningFromTask
- ✅ Renamed setIsOnFromLoop → setRunningFromLoop
- ✅ Zero "isOn" references remaining (except in comments/documentation)

---

## Rollback Plan

If something breaks:

1. **Git is your friend:** Commit after each phase
   ```bash
   git commit -m "Phase 2: Removed MODE_GCODE"
   ```

2. **Keep old code commented** during transition:
   ```cpp
   // OLD: if (isOn) { ... }
   if (controllerState == STATE_RUN) { ... }  // NEW
   ```

3. **Test incrementally:** Don't move to next phase until current one works

---

## Questions to Resolve

1. **Should MODE_NORMAL even exist?**
   - Could just have no mode, or mode == MODE_THREAD vs mode == MODE_NONE

2. **What about pendant stop/resume?**
   - Currently pendant '~' handler sets isOn
   - Should it set state instead?
   - Line ~924-927 in processMPGCommand

3. **Emergency stop state management?**
   - When to set STATE_ALARM?
   - How to recover from ALARM?

4. **What happens during homing (G28)?**
   - Should state be RUN or special HOMING state?
   - Currently uses movingManually flag

---

## Success Criteria

When refactoring is complete:

✅ No more `MODE_GCODE`
✅ `controllerState` clearly represents system state
✅ Status responses accurately reflect state
✅ MPG blocking logic is simple and clear
✅ M0 pause/resume works without deadlock
✅ No blocking loops in command handlers
✅ All tests pass
✅ Code is more readable and maintainable

---

## Notes

- Take it slow - this is a significant architectural change
- Commit frequently
- Test after each step
- Don't be afraid to pause and reconsider approach
- The state machine should be obvious from reading the code

Good luck! 🚀
