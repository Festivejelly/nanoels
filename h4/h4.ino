// https://github.com/kachurovskiy/nanoels

/* Change values in this section to suit your hardware. */

// Define your hardware parameters here.
const int ENCODER_PPR = 600; // 600 step spindle optical rotary encoder. Fractional values not supported.
const int ENCODER_BACKLASH = 3; // Numer of impulses encoder can issue without movement of the spindle

// Spindle rotary encoder pins. Swap values if the rotation direction is wrong.
#define ENC_A 7 //GREEN
#define ENC_B 15 //WHITE

const bool DEFAULT_ENABLE_Z = true;   // Z axis enabled by default
const bool DEFAULT_ENABLE_X = true;   // X axis enabled by default
const bool DEFAULT_ENABLE_A1 = false; // Y axis disabled by default (since it's removable)

// Main lead screw (Z) parameters.
const long SCREW_Z_DU = 50000; // 5mm lead screw in deci-microns (10^-7 of a meter)
const long MOTOR_STEPS_Z = 1000;
const long SPEED_START_Z = 2 * MOTOR_STEPS_Z; // Initial speed of a motor, steps / second.
const long ACCELERATION_Z = 40 * MOTOR_STEPS_Z; // Acceleration of a motor, steps / second ^ 2.
const long SPEED_MANUAL_MOVE_Z = 4 * MOTOR_STEPS_Z; // Maximum speed of a motor during manual move, steps / second.
const bool INVERT_Z = true; // change (true/false) if the carriage moves e.g. "left" when you press "right".
const bool NEEDS_REST_Z = false; // Set to false for closed-loop drivers, true for open-loop.
const long MAX_TRAVEL_MM_Z = 300; // Lathe bed doesn't allow to travel more than this in one go, 30cm / ~1 foot
const long BACKLASH_DU_Z = 200; // 400 = 0.04mm backlash in deci-microns (10^-7 of a meter)
const char NAME_Z = 'Z'; // Text shown on screen before axis position value, GCode axis name
const bool MPG_INVERT_Z = true;  // Set to true to reverse Z axis MPG direction

// Cross-slide lead screw (X) parameters.
const long SCREW_X_DU = 20000; // 2.0mm ball screw inline screw in deci-microns (10^-7) of a meter
const long MOTOR_STEPS_X = 2000;
const long SPEED_START_X = MOTOR_STEPS_X; // Initial speed of a motor, steps / second.
const long ACCELERATION_X = 50 * MOTOR_STEPS_X; // Acceleration of a motor, steps / second ^ 2.
const long SPEED_MANUAL_MOVE_X = 6 * MOTOR_STEPS_X; // Maximum speed of a motor during manual move, steps / second.
const bool INVERT_X = false; // change (true/false) if the carriage moves e.g. "left" when you press "right".
const bool NEEDS_REST_X = false; // Set to false for all kinds of drivers or X will be unlocked when not moving.
const long MAX_TRAVEL_MM_X = 100; // Cross slide doesn't allow to travel more than this in one go, 10cm
const long BACKLASH_DU_X = 200; // 500 0.05mm backlash in deci-microns (10^-7 of a meter)
const char NAME_X = 'X'; // Text shown on screen before axis position value, GCode axis name
const bool MPG_INVERT_X = false;  // Set to true to reverse X axis MPG direction

// Manual stepping with left/right/up/down buttons. Only used when step isn't default continuous (1mm or 0.1").
const long STEP_TIME_MS = 500; // Time in milliseconds it should take to make 1 manual step.
const long DELAY_BETWEEN_STEPS_MS = 80; // Time in milliseconds to wait between steps.

/* Changing anything below shouldn't be needed for basic use. */

// Configuration for axis connected to A1. This is uncommon. Dividing head (C) motor parameters.
// Throughout the configuration below we assume 1mm = 1degree of rotation, so 1du = 0.0001degree.
const bool ACTIVE_A1 = true; // Whether the axis is connected
const long MOTOR_STEPS_A1 = 2000; // Number of motor steps for 1 rotation of the the worm gear screw (full step with 20:30 reduction)
const long SCREW_A1_DU = 50000; // Degrees multiplied by 10000 that the spindle travels per 1 turn of the worm gear. 2 degrees.
const long SPEED_START_A1 = MOTOR_STEPS_A1; // Initial speed of a motor, steps / second.
const long ACCELERATION_A1 = 40 * MOTOR_STEPS_A1; // Acceleration of a motor, steps / second ^ 2.
const long SPEED_MANUAL_MOVE_A1 = 4 * MOTOR_STEPS_A1; // Maximum speed of a motor during manual move, steps / second.
const bool INVERT_A1 = false; // change (true/false) if the carriage moves e.g. "left" when you press "right".
const bool NEEDS_REST_A1 = false; // Set to false for closed-loop drivers. Open-loop: true if you need holding torque, false otherwise.
const long MAX_TRAVEL_MM_A1 = 100; // Probably doesn't make sense to ask the dividin head to travel multiple turns.
const long BACKLASH_DU_A1 = 200; // Assuming no backlash on the worm gear
const char NAME_A1 = 'Y'; // Text shown on screen before axis position value, GCode axis name
const bool MPG_INVERT_A1 = false; // Set to true to reverse Y/A1 axis MPG direction

// Manual handwheels on A1 and A2. Ignore if you don't have them installed.
const bool PULSE_1_USE = false; // Whether there's a pulse generator connected on A11-A13 to be used for movement.
const char PULSE_1_AXIS = NAME_Z; // Set to NAME_X to make A11-A13 pulse generator control X instead.
const bool PULSE_1_INVERT = false; // Set to true to change the direction in which encoder moves the axis
const bool PULSE_2_USE = false; // Whether there's a pulse generator connected on A21-A23 to be used for movement.
const char PULSE_2_AXIS = NAME_X; // Set to NAME_Z to make A21-A23 pulse generator control Z instead.
const bool PULSE_2_INVERT = true; // Set to false to change the direction in which encoder moves the axis
const float PULSE_PER_REVOLUTION = 100; // PPR of handwheels used on A1 and/or A2.
const long PULSE_MIN_WIDTH_US = 1000; // Microseconds width of the pulse that is required for it to be registered. Prevents noise.
const long PULSE_HALF_BACKLASH = 2; // Prevents spurious reverses when moving using a handwheel. Raise to 3 or 4 if they still happen.

const int ENCODER_STEPS_INT = ENCODER_PPR * 2; // Number of encoder impulses PCNT counts per revolution of the spindle
const int ENCODER_FILTER = 2; // Encoder pulses shorter than this will be ignored. Clock cycles, 1 - 1023.
const int PCNT_LIM = 31000; // Limit used in hardware pulse counter logic.
const int PCNT_CLEAR = 30000; // Limit where we reset hardware pulse counter value to avoid overflow. Less than PCNT_LIM.
const long DUPR_MAX = 254000; // No more than 1 inch pitch
const int32_t STARTS_MAX = 124; // No more than 124-start thread
const long PASSES_MAX = 999; // No more turn or face passes than this
const long SAFE_DISTANCE_DU = 5000; // Step back 0.5mm from the material when moving between cuts in automated modes
const long SAVE_DELAY_US = 5000000; // Wait 5s after last save and last change of saveable data before saving again
const long DIRECTION_SETUP_DELAY_US = 5; // Stepper driver needs some time to adjust to direction change
const long STEPPED_ENABLE_DELAY_MS = 100; // Delay after stepper is enabled and before issuing steps

// Homing parameters
float x_home_position = -81.0;  // Position where sensor triggers (will be calibrated)
float x_home_position_saved = -81.0;
float x_home_position_calibrated = 0.0; // Set this after running M206 calibration
const long X_HOME_MAX_TRAVEL = 80; // Maximum travel distance when homing (mm)
const long X_HOME_FAST_SPEED = 200; // Fast approach speed (mm/min)
const long X_HOME_SLOW_SPEED = 50;  // Slow final approach speed (mm/min)
const long X_HOME_BACKOFF = 2;      // Distance to back off after fast trigger (mm)
const bool X_HOME_DIRECTION_INVERT = false; //set to true to invert direction

float y_home_position = -81.0;  // Position where sensor triggers (will be calibrated)
float y_home_position_saved = -81.0;
float y_home_position_calibrated = 0.0; // Set this after running M206 calibration
const long Y_HOME_MAX_TRAVEL = 80; // Maximum travel distance when homing (mm)
const long Y_HOME_FAST_SPEED = 200; // Fast approach speed (mm/min)
const long Y_HOME_SLOW_SPEED = 50;  // Slow final approach speed (mm/min)
const long Y_HOME_BACKOFF = 2;      // Distance to back off after fast trigger (mm)
const bool Y_HOME_DIRECTION_INVERT = true; //set to true to invert direction

float z_home_position = -81.0;  // Position where sensor triggers (will be calibrated)
float z_home_position_saved = -81.0;
float z_home_position_calibrated = 0.0; // Set this after running M206 calibration
const long Z_HOME_MAX_TRAVEL = 80; // Maximum travel distance when homing (mm)
const long Z_HOME_FAST_SPEED = 200; // Fast approach speed (mm/min)
const long Z_HOME_SLOW_SPEED = 50;  // Slow final approach speed (mm/min)
const long Z_HOME_BACKOFF = 2;      // Distance to back off after fast trigger (mm)
const bool Z_HOME_DIRECTION_INVERT = false; //set to true to invert direction

// Version of the pref storage format, should be changed when non-backward-compatible
// changes are made to the storage logic, resulting in Preferences wipe on first start.
#define PREFERENCES_VERSION 1
#define PREF_NAMESPACE "h4"
#define GCODE_NAMESPACE "gc"

// GCode-related constants.
const long GCODE_WAIT_EPSILON_STEPS = 10;
const float LINEAR_INTERPOLATION_PRECISION = 0.1; // 0 < x <= 1, smaller values make for quicker G1 moves
const float RAPID_LINEAR_INTERPOLATION_PRECISION = 0.02; // 0 < x <= 1, smaller values make for quicker G0 moves
const bool SPINDLE_PAUSES_GCODE = false; // pause GCode execution when spindle stops
const int GCODE_MIN_RPM = 30; // pause GCode execution if RPM is below this

// To be incremented whenever a measurable improvement is made.
#define SOFTWARE_VERSION 12

// To be changed whenever a different PCB / encoder / stepper / ... design is used.
#define HARDWARE_VERSION 4

#define Z_ENA 16
#define Z_DIR 17
#define Z_STEP 18

#define X_ENA 8
#define X_DIR 19
#define X_STEP 20

#define BUZZ 4
#define SCL 5
#define SDA 6

//Y Axis
#define Y_ENA 9  // ENA
#define Y_DIR 10 // DIR
#define Y_STEP 11 // STEP

//Uses the same pin connected in parallel
#define X_HOME_SENSOR_PIN 12
//#define Y_HOME_SENSOR_PIN 12
//#define Z_HOME_SENSOR_PIN 12

//MPG wheel section
#define MPG_RX_PIN 13  // GPIO 13 (was A22) green
#define MPG_TX_PIN 14  // GPIO 14 (was A23) yellow

#define PREF_VERSION "v"
#define PREF_DUPR "d"
#define PREF_POS_Z "zp"
#define PREF_LEFT_STOP_Z "zls"
#define PREF_RIGHT_STOP_Z "zrs"
#define PREF_ORIGIN_POS_Z "zpo"
#define PREF_POS_GLOBAL_Z "zpg"
#define PREF_MOTOR_POS_Z "zpm"
#define PREF_DISABLED_Z "zd"
#define PREF_POS_X "xp"
#define PREF_LEFT_STOP_X "xls"
#define PREF_RIGHT_STOP_X "xrs"
#define PREF_ORIGIN_POS_X "xpo"
#define PREF_POS_GLOBAL_X "xpg"
#define PREF_MOTOR_POS_X "xpm"
#define PREF_DISABLED_X "xd"
#define PREF_POS_A1 "a1p"
#define PREF_LEFT_STOP_A1 "a1ls"
#define PREF_RIGHT_STOP_A1 "a1rs"
#define PREF_ORIGIN_POS_A1 "a1po"
#define PREF_POS_GLOBAL_A1 "a1pg"
#define PREF_MOTOR_POS_A1 "a1pm"
#define PREF_DISABLED_A1 "a1d"
#define PREF_SPINDLE_POS "sp"
#define PREF_SPINDLE_POS_AVG "spa"
#define PREF_OUT_OF_SYNC "oos"
#define PREF_SPINDLE_POS_GLOBAL "spg"
#define PREF_SHOW_ANGLE "ang"
#define PREF_SHOW_TACHO "rpm"
#define PREF_STARTS "sta"
#define PREF_MODE "mod"
#define PREF_MEASURE "mea"
#define PREF_CONE_RATIO "cr"
#define PREF_TURN_PASSES "tp"
#define PREF_MOVE_STEP "ms"
#define PREF_AUX_FORWARD "af"
#define PREF_TOOL "t"
#define PREF_BACKLASH_Z "zbl"
#define PREF_BACKLASH_X "xbl"
#define PREF_BACKLASH_A1 "a1bl"
#define PREF_CURRENT_APPLIED_OFFSET_Z "cao_z"
#define PREF_CURRENT_APPLIED_OFFSET_X "cao_x"
#define PREF_MPG_AXIS "mpg_ax"
#define PREF_MPG_STEP "mpg_st"
#define PREF_X_HOME_POSITION "xhpos"
#define PREF_Y_HOME_POSITION "yhpos"
#define PREF_Z_HOME_POSITION "zhpos"

#define MOVE_STEP_1 10000 // 1mm
#define MOVE_STEP_2 1000 // 0.1mm
#define MOVE_STEP_3 100 // 0.01mm
#define MOVE_STEP_4 10 // 0.001mm

#define MOVE_STEP_IMP_1 25400 // 1/10"
#define MOVE_STEP_IMP_2 2540 // 1/100"
#define MOVE_STEP_IMP_3 254 // 1/1000" also known as 1 thou

// MPG state variables
volatile int mpgDeltaX = 0;
volatile int mpgDeltaZ = 0;
volatile int mpgDeltaA1 = 0;
volatile long mpgStepSize = MOVE_STEP_2; // Default to 0.1mm
volatile long savedMpgStepSize = MOVE_STEP_2;
volatile char mpgActiveAxis = 'N'; // 'X', 'Z', 'Y' (for A1), or 'N' (none)
volatile char savedMpgActiveAxis = 'N';
SemaphoreHandle_t mpgMutex;
bool mpgEnabled = true; // Can be toggled by stop/play

#define MODE_NORMAL 0
#define MODE_ASYNC 2
#define MODE_CONE 3
#define MODE_TURN 4
#define MODE_FACE 5
#define MODE_CUT 6
#define MODE_THREAD 7
#define MODE_ELLIPSE 8
#define MODE_GCODE 9
#define MODE_A1 10

#define SIMULATE_SPINDLE false
#define SIMULATED_RPM 300  // 60 RPM = 1 revolution per second

#define MEASURE_METRIC 0
#define MEASURE_INCH 1
#define MEASURE_TPI 2

#define ESTOP_NONE 0
#define ESTOP_KEY 1
#define ESTOP_POS 2
#define ESTOP_MARK_ORIGIN 3
#define ESTOP_ON_OFF 4
#define ESTOP_OFF_MANUAL_MOVE 5

// For MEASURE_TPI, round TPI to the nearest integer if it's within this range of it.
// E.g. 80.02tpi would be shown as 80tpi but 80.04tpi would be shown as-is.
const float TPI_ROUND_EPSILON = 0.03;

const float ENCODER_STEPS_FLOAT = ENCODER_STEPS_INT; // Convenience float version of ENCODER_STEPS_INT
const long RPM_BULK = ENCODER_STEPS_INT; // Measure RPM averaged over this number of encoder pulses
const long RPM_UPDATE_INTERVAL_MICROS = 1000000; // Don't redraw RPM more often than once per second

const long GCODE_FEED_DEFAULT_DU_SEC = 20000; // Default feed in du/sec in GCode mode
const float GCODE_FEED_MIN_DU_SEC = 167; // Minimum feed in du/sec in GCode mode - F1

#define DREAD(x) digitalRead(x)
#define DHIGH(x) digitalWrite(x, HIGH)
#define DLOW(x) digitalWrite(x, LOW)
#define DWRITE(x, y) digitalWrite(x, y)

#define DELAY(x) vTaskDelay(x / portTICK_PERIOD_MS);

// ESP32 hardware pulse counter library used to count spindle encoder pulses.
#include "driver/pcnt.h"

//#include <SPI.h>
//#include <Wire.h>
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(21, 48, 47, 38, 39, 40, 41, 42, 2, 1);
// #define LCD_HASH_INITIAL -3845709 // Random number that's unlikely to naturally occur as an actual hash
// long lcdHashLine0 = LCD_HASH_INITIAL;
// long lcdHashLine1 = LCD_HASH_INITIAL;
// long lcdHashLine2 = LCD_HASH_INITIAL;
// long lcdHashLine3 = LCD_HASH_INITIAL;
// bool splashScreen = false;

#include <Preferences.h>

//#include <Adafruit_TCA8418.h>
//Adafruit_TCA8418 keypad;
unsigned long keypadTimeUs = 0;

// Most buttons we only have "down" handling, holding them has no effect.
// Buttons with special "holding" logic have flags below.
bool buttonLeftPressed = false;
bool buttonRightPressed = false;
bool buttonUpPressed = false;
bool buttonDownPressed = false;
bool buttonOffPressed = false;
bool buttonGearsPressed = false;
bool buttonTurnPressed = false;
bool buttonPlusPressed = false;
bool buttonMinusPressed = false;

bool inNumpad = false;
int numpadDigits[20];
int numpadIndex = 0;

bool isOn = false;
volatile bool stopRequested = false;
bool nextIsOn; // isOn value that should be applied asap
bool nextIsOnFlag; // whether nextIsOn requires attention
unsigned long resetMillis = 0;
int emergencyStop = 0;

bool beepFlag = false; // allows time-critical code to ask for a beep on another core

long dupr = 0; // pitch, tenth of a micron per rotation
long savedDupr = 0; // dupr saved in Preferences
long nextDupr = dupr; // dupr value that should be applied asap
bool nextDuprFlag = false; // whether nextDupr requires attention

SemaphoreHandle_t motionMutex; // controls blocks of code where variables affecting the motion loop() are changed

int starts = 1; // number of starts in a multi-start thread
int savedStarts = 0; // starts saved in Preferences
int nextStarts = starts; // number of starts that should be used asap
bool nextStartsFlag = false; // whether nextStarts requires attention

enum ToolMode {
  TOOL_IDLE,
  TOOL_SELECT,
  TOOL_CONFIRM
};

ToolMode currentToolMode = TOOL_IDLE;
int pendingToolNumber = -1;
String pendingInput = "";
bool forceDisplayRefresh = false;
bool offsetsChanged = false;

constexpr int MAX_TOOLS = 30;

struct ToolOffset {
    float zOffsetDu;
    float xOffsetDu;
    float zCompDu;
    float xCompDu;
};

// Tool offsets in deci-microns (DU). 1mm = 10000 DU.
// set with G10 P{toolNumber} Z{zOffsetInMM} X{xOffsetInMM} 
// or set on the controller by pressing the gear icon
ToolOffset toolOffsets[MAX_TOOLS] = {
    {0, 0, 0, 0}             //T0 primary tool (parting), all offsets are based off this tool
};

int nextTool = 0;
bool nextToolFlag = false;

ToolOffset toolOffset = {0, 0, 0, 0};
ToolOffset currentAppliedOffset = {0, 0, 0, 0};

int currentTool = 0;

bool x_home_sensor_triggered = false;
bool x_homing_active = false;

struct Axis {
  SemaphoreHandle_t mutex;

  char name;
  bool active;
  bool rotational;
  float motorSteps; // motor steps per revolution of the axis
  float screwPitch; // lead screw pitch in deci-microns (10^-7 of a meter)

  long pos; // relative position of the tool in stepper motor stepss
  float fractionalPos; // fractional distance in steps that we meant to travel but couldn't
  long originPos; // relative position of the stepper motor to origin, in steps
  long posGlobal; // global position of the motor in steps
  int pendingPos; // steps of the stepper motor that we should make as soon as possible
  long motorPos; // position of the motor in stepper motor steps, same as pos unless moving back, then differs by backlashSteps
  bool continuous; // whether current movement is expected to continue until an unknown position

  long leftStop; // left stop value of pos
  long savedLeftStop; // value saved in Preferences
  long nextLeftStop; // left stop value that should be applied asap
  bool nextLeftStopFlag; // whether nextLeftStop required attention

  long rightStop; // right stop value of pos
  long savedRightStop; // value saved in Preferences
  long nextRightStop; // right stop value that should be applied asap
  bool nextRightStopFlag; // whether nextRightStop requires attention

  long speed; // motor speed in steps / second
  long speedStart; // Initial speed of a motor, steps / second.
  long speedMax; // To limit max speed e.g. for manual moves
  long speedManualMove; // Maximum speed of a motor during manual move, steps / second.
  long acceleration; // Acceleration of a motor, steps / second ^ 2.
  long decelerateSteps; // Number of steps before the end position the deceleration should start.

  bool direction; // To reset speed when direction changes.
  bool directionInitialized;
  unsigned long stepStartUs;
  int stepperEnableCounter;
  bool disabled;
  bool savedDisabled;

  bool invertStepper; // change (true/false) if the carriage moves e.g. "left" when you press "right".
  bool needsRest; // set to false for closed-loop drivers, true for open-loop.
  bool movingManually; // whether stepper is being moved by left/right buttons
  long estopSteps; // amount of steps to exceed machine limits
  long backlashDu;     // Backlash in deci-microns
  long savedBacklashDu; // Value saved in Preferences
  long backlashSteps; // amount of steps in reverse direction to re-engage the carriage
  long gcodeRelativePos; // absolute position in steps that relative GCode refers to

  int ena; // Enable pin of this motor
  int dir; // Direction pin of this motor
  int step; // Step pin of this motor
};

void initAxis(Axis* a, char name, bool active, bool rotational, float motorSteps, float screwPitch, long speedStart, long speedManualMove,
    long acceleration, bool invertStepper, bool needsRest, long maxTravelMm, long backlashDu, int ena, int dir, int step) {
  a->mutex = xSemaphoreCreateMutex();

  a->name = name;
  a->active = active;
  a->rotational = rotational;
  a->motorSteps = motorSteps;
  a->screwPitch = screwPitch;

  a->pos = 0;
  a->fractionalPos = 0.0;
  a->originPos = 0;
  a->posGlobal = 0;
  a->pendingPos = 0;
  a->motorPos = 0;
  a->continuous = false;

  a->leftStop = 0;
  a->savedLeftStop = 0;
  a->nextLeftStopFlag = false;

  a->rightStop = 0;
  a->savedRightStop = 0;
  a->nextRightStopFlag = false;

  a->speed = speedStart;
  a->speedStart = speedStart;
  a->speedMax = LONG_MAX;
  a->speedManualMove = speedManualMove;
  a->acceleration = acceleration;
  a->decelerateSteps = 0;
  long s = speedManualMove;
  while (s > speedStart) {
    a->decelerateSteps++;
    s -= a->acceleration / float(s);
  }

  a->direction = true;
  a->directionInitialized = false;
  a->stepStartUs = 0;
  a->stepperEnableCounter = 0;
  a->disabled = false;
  a->savedDisabled = false;

  a->invertStepper = invertStepper;
  a->needsRest = needsRest;
  a->movingManually = false;
  a->estopSteps = maxTravelMm * 10000 / a->screwPitch * a->motorSteps;
  a->backlashDu = backlashDu;
  a->backlashSteps = backlashDu * a->motorSteps / a->screwPitch;
  a->gcodeRelativePos = 0;

  a->ena = ena;
  a->dir = dir;
  a->step = step;
}

Axis z;
Axis x;
Axis a1;

unsigned long saveTime = 0; // micros() of the previous Prefs write
unsigned long spindleEncTime = 0; // micros() of the previous spindle update
unsigned long spindleEncTimeDiffBulk = 0; // micros() between RPM_BULK spindle updates
unsigned long spindleEncTimeAtIndex0 = 0; // micros() when spindleEncTimeIndex was 0
int spindleEncTimeIndex = 0; // counter going between 0 and RPM_BULK - 1
long spindlePos = 0; // Spindle position
long spindlePosAvg = 0; // Spindle position accounting for encoder backlash
long savedSpindlePosAvg = 0; // spindlePosAvg saved in Preferences
long savedSpindlePos = 0; // spindlePos value saved in Preferences
int spindleCount = 0; // Last processed spindle encoder pulse counter value.
int spindlePosSync = 0; // Non-zero if gearbox is on and a soft limit was removed while axis was on it
int savedSpindlePosSync = 0; // spindlePosSync saved in Preferences
long spindlePosGlobal = 0; // global spindle position that is unaffected by e.g. zeroing
long savedSpindlePosGlobal = 0; // spindlePosGlobal saved in Preferences

ToolOffset savedToolOffsets[MAX_TOOLS]; // savedToolOffset saved in Preferences

volatile int pulse1Delta = 0; // Outstanding pulses generated by pulse generator on terminal A1.
volatile int pulse2Delta = 0; // Outstanding pulses generated by pulse generator on terminal A2.

bool showAngle = false; // Whether to show 0-359 spindle angle on screen
bool showTacho = false; // Whether to show spindle RPM on screen
bool savedShowAngle = false; // showAngle value saved in Preferences
bool savedShowTacho = false; // showTacho value saved in Preferences
int shownRpm = 0;
unsigned long shownRpmTime = 0; // micros() when shownRpm was set

long moveStep = 0; // thousandth of a mm
long savedMoveStep = 0; // moveStep saved in Preferences

volatile int mode = -1; // mode of operation (ELS, multi-start ELS, asynchronous)
int nextMode = 0; // mode value that should be applied asap
bool nextModeFlag = false; // whether nextMode needs attention
int savedMode = -1; // mode saved in Preferences

int measure = MEASURE_METRIC; // Whether to show distances in inches
int savedMeasure = MEASURE_METRIC; // measure value saved in Preferences

float coneRatio = 1; // In cone mode, how much X moves for 1 step of Z
float savedConeRatio = 0; // value of coneRatio saved in Preferences
float nextConeRatio = 0; // coneRatio that should be applied asap
bool nextConeRatioFlag = false; // whether nextConeRatio requires attention

int turnPasses = 3; // In turn mode, how many turn passes to make
int threadSpringPasses = 2; // 0 - 3 number of spring passes to take when cutting threads
int savedTurnPasses = 0; // value of turnPasses saved in Preferences

long setupIndex = 0; // Index of automation setup step
bool auxForward = true; // True for external, false for internal thread
bool savedAuxForward = false; // value of auxForward saved in Preferences

long opIndex = 0; // Index of an automation operation
bool opIndexAdvanceFlag = false; // Whether user requested to move to the next pass
long opSubIndex = 0; // Sub-index of an automation operation
int opDuprSign = 1; // 1 if dupr was positive when operation started, -1 if negative
long opDupr = 0; // dupr that the multi-pass operation started with

const int customCharMmCode = 0;
byte customCharMm[] = {
  B11010,
  B10101,
  B10101,
  B00000,
  B11010,
  B10101,
  B10101,
  B00000
};
const int customCharLimUpCode = 1;
byte customCharLimUp[] = {
  B11111,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00000,
  B00000
};
const int customCharLimDownCode = 2;
byte customCharLimDown[] = {
  B00000,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B11111,
  B00000
};
const int customCharLimLeftCode = 3;
byte customCharLimLeft[] = {
  B10000,
  B10010,
  B10100,
  B11111,
  B10100,
  B10010,
  B10000,
  B00000
};
const int customCharLimRightCode = 4;
byte customCharLimRight[] = {
  B00001,
  B01001,
  B00101,
  B11111,
  B00101,
  B01001,
  B00001,
  B00000
};
const int customCharLimUpDownCode = 5;
byte customCharLimUpDown[] = {
  B11111,
  B00100,
  B01110,
  B00000,
  B01110,
  B00100,
  B11111,
  B00000
};
const int customCharLimLeftRightCode = 6;
byte customCharLimLeftRight[] = {
  B00000,
  B10001,
  B10001,
  B11111,
  B10001,
  B10001,
  B00000,
  B00000
};

String gcodeCommand = "";
long gcodeFeedDuPerSec = GCODE_FEED_DEFAULT_DU_SEC;
long gcodeRapidFeedDuPerSecZ = 166667;   // 1000 mm/min
long gcodeRapidFeedDuPerSecX = 83333;    // 500 mm/min  
long gcodeRapidFeedDuPerSecA1 = 83333;   // 500 mm/min
int gcodeMotionMode = 0;  // Modal motion mode: 0=G0 (rapid), 1=G1 (feed)
bool gcodeInitialized = false;
bool gcodeAbsolutePositioning = true;
bool gcodeInBrace = false;
bool gcodeInSemicolon = false;
bool serialInKeycode = false;
int serialKeycode = 0;
String keycodeCommand = "";
int spindleRPM = 0;  // Requested spindle speed
int spindleDirection = 0;  // 0=stopped, 1=CW (M3), -1=CCW (M4)

hw_timer_t *async_timer = timerBegin(80);
bool timerAttached = false;

int getApproxRpm() {
  unsigned long t = micros();
  if (t > spindleEncTime + 50000) {
    // RPM less than 10.
    spindleEncTimeDiffBulk = 0;
    shownRpm = 0;
    shownRpmTime = t;
    return 0;
  }
  if (t < shownRpmTime + RPM_UPDATE_INTERVAL_MICROS) {
    // Don't update RPM too often to avoid flickering.
    return shownRpm;
  }
  int rpm = 0;
  if (spindleEncTimeDiffBulk > 0) {
    rpm = 60000000 / spindleEncTimeDiffBulk;
    if (abs(rpm - shownRpm) > (rpm < 1000 ? 3 : 5)) {
      // Don't update RPM with insignificant differences.
      shownRpm = rpm;
      shownRpmTime = t;
    }
  }
  return rpm;
}

bool stepperIsRunning(Axis* a) {
  return micros() - a->stepStartUs < 50000;
}

long stepsToDu(Axis* a, long steps) {
  return round(steps * a->screwPitch / a->motorSteps);
}

long duToSteps(Axis* a, long du) {
  return round(static_cast<double>(du) * a->motorSteps / a->screwPitch);
}

long floatDuToSteps(Axis* a, float du_float) {
    return round(static_cast<double>(du_float) * a->motorSteps / a->screwPitch);
}

long getAxisPosDu(Axis* a) {
  return stepsToDu(a, a->pos + a->originPos);
}

long getAxisStopDiffDu(Axis* a) {
  if (a->leftStop == LONG_MAX || a->rightStop == LONG_MIN) return 0;
  return stepsToDu(a, a->leftStop - a->rightStop);
}

bool needZStops() {
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_THREAD || mode == MODE_ELLIPSE;
}

bool isPassMode() {
  return mode == MODE_TURN || mode == MODE_FACE || mode == MODE_CUT || mode == MODE_THREAD || mode == MODE_ELLIPSE;
}

bool manualMovesAllowedWhenOn() {
  return mode == MODE_NORMAL || mode == MODE_ASYNC || mode == MODE_CONE || mode == MODE_A1;
}

int getLastSetupIndex() {
  if (mode == MODE_CONE || mode == MODE_GCODE) return 2;
  if (mode == MODE_TURN || mode == MODE_FACE || mode == MODE_CUT || mode == MODE_THREAD || mode == MODE_ELLIPSE) return 3;
  return 0;
}

Axis* getPitchAxis() {
  return mode == MODE_FACE ? &x : &z;
}

long getPassModeZStart() {
  if (mode == MODE_TURN || mode == MODE_THREAD) return dupr > 0 ? z.rightStop : z.leftStop;
  if (mode == MODE_FACE) return auxForward ? z.rightStop : z.leftStop;
  if (mode == MODE_ELLIPSE) return dupr > 0 ? z.leftStop : z.rightStop;
  return z.pos;
}

long getPassModeXStart() {
  if (mode == MODE_TURN || mode == MODE_THREAD) return auxForward ? x.rightStop : x.leftStop;
  if (mode == MODE_FACE || mode == MODE_CUT) return dupr > 0 ? x.rightStop : x.leftStop;
  if (mode == MODE_ELLIPSE) return x.rightStop;
  return x.pos;
}

void setAsyncTimerEnable(bool value) {
  if (value) {
    timerStart(async_timer);
  } else {
    timerStop(async_timer);
  }
}

void waitForPendingPosNear0(Axis* a) {
  //wait until we are within half a step of the target
  while (abs(a->pendingPos) > a->motorSteps / 2) {
    taskYIELD();
  }
}

void waitForPendingPos0(Axis* a) {
  while (a->pendingPos != 0) {
    taskYIELD();
  }
}

bool isContinuousStep() {
  return moveStep == (measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1);
}

// For rotational axis the moveStep of 0.1" means 0.1°.
long getMoveStepForAxis(Axis* a) {
  return (a->rotational && measure != MEASURE_METRIC) ? (moveStep / 25.4) : moveStep;
}

long getStepMaxSpeed(Axis* a) {
  return isContinuousStep() ? a->speedManualMove : min(long(a->speedManualMove), abs(getMoveStepForAxis(a)) * 1000 / STEP_TIME_MS);
}

void waitForStep(Axis* a) {
  if (isContinuousStep()) {
    // Move continuously for default step.
    waitForPendingPosNear0(a);
  } else {
    // Move with tiny pauses allowing to stop precisely.
    a->continuous = false;
    waitForPendingPos0(a);
    DELAY(DELAY_BETWEEN_STEPS_MS);
  }
}

int getAndResetPulses(Axis* a) {
  int delta = 0;
  if (PULSE_1_AXIS == a->name) {
    if (pulse1Delta < -PULSE_HALF_BACKLASH) {
      noInterrupts();
      delta = pulse1Delta + PULSE_HALF_BACKLASH;
      pulse1Delta = -PULSE_HALF_BACKLASH;
      interrupts();
    } else if (pulse1Delta > PULSE_HALF_BACKLASH) {
      noInterrupts();
      delta = pulse1Delta - PULSE_HALF_BACKLASH;
      pulse1Delta = PULSE_HALF_BACKLASH;
      interrupts();
    }
  } else if (PULSE_2_AXIS == a->name) {
    if (pulse2Delta < -PULSE_HALF_BACKLASH) {
      noInterrupts();
      delta = pulse2Delta + PULSE_HALF_BACKLASH;
      pulse2Delta = -PULSE_HALF_BACKLASH;
      interrupts();
    } else if (pulse2Delta > PULSE_HALF_BACKLASH) {
      noInterrupts();
      delta = pulse2Delta - PULSE_HALF_BACKLASH;
      pulse2Delta = PULSE_HALF_BACKLASH;
      interrupts();
    }
  }
  return delta;
}

void taskMoveZ(void *param) {

  while (emergencyStop == ESTOP_NONE) {
    int pulseDelta = getAndResetPulses(&z);
    bool left = buttonLeftPressed;
    bool right = buttonRightPressed;
    if (!left && !right && pulseDelta == 0) {
      taskYIELD();
      continue;
    }

    if (spindlePosSync != 0) {
      // Edge case.
      taskYIELD();
      continue;
    }
    if (isOn && !manualMovesAllowedWhenOn()) {
      setIsOnFromTask(false);
    }
    int sign = pulseDelta == 0 ? (left ? 1 : -1) : (pulseDelta > 0 ? 1 : -1);
    bool stepperOn = true;
    stepperEnable(&z, true);
    z.movingManually = true;
    if (isOn && dupr != 0 && mode == MODE_NORMAL) {
      // Move by moveStep in the desired direction but stay in the thread by possibly traveling a little more.
      int diff = ceil(moveStep * 1.0 / abs(dupr * starts)) * ENCODER_STEPS_FLOAT * sign * (dupr > 0 ? 1 : -1);
      long prevSpindlePos = spindlePos;
      bool resting = false;
      do {
        z.speedMax = z.speedManualMove;
        if (xSemaphoreTake(motionMutex, 100) == pdTRUE) {
          if (!resting) {
            spindlePos += diff;
            spindlePosAvg += diff;
          }
          // If spindle is moving, it will be changing spindlePos at the same time. Account for it.
          while (diff > 0 ? (spindlePos < prevSpindlePos) : (spindlePos > prevSpindlePos)) {
            spindlePos += diff;
            spindlePosAvg += diff;
          };
          prevSpindlePos = spindlePos;
          xSemaphoreGive(motionMutex);
        }

        long newPos = posFromSpindle(&z, prevSpindlePos, true);
        if (newPos != z.pos) {
          stepToContinuous(&z, newPos);
          waitForPendingPosNear0(&z);
        } else if (z.pos == (left ? z.leftStop : z.rightStop)) {
          // We're standing on a stop with the L/R move button pressed.
          resting = true;
          if (stepperOn) {
            stepperEnable(&z, false);
            stepperOn = false;
          }
          DELAY(200);
        }
      } while (left ? buttonLeftPressed : buttonRightPressed);
    } else {
      z.speedMax = getStepMaxSpeed(&z);
      int delta = 0;

      do {
        float fractionalDelta = (pulseDelta == 0 ? moveStep * sign / z.screwPitch : pulseDelta / PULSE_PER_REVOLUTION) * z.motorSteps + z.fractionalPos;
        delta = round(fractionalDelta);
        // Don't lose fractional steps when moving by 0.01" or 0.001".
        z.fractionalPos = fractionalDelta - delta;

        if (delta == 0) {
          // When moveStep is e.g. 1 micron and MOTOR_STEPS_Z is 200, make delta non-zero.
          delta = sign;
        }

        long posCopy = z.pos + z.pendingPos;
        // Don't left-right move out of stops.
        if (posCopy + delta > z.leftStop) {
          delta = z.leftStop - posCopy;
        } else if (posCopy + delta < z.rightStop) {
          delta = z.rightStop - posCopy;
        }
        z.speedMax = getStepMaxSpeed(&z);
        stepToContinuous(&z, posCopy + delta);
        waitForStep(&z);
        DELAY(50);
      } while (delta != 0 && (left ? buttonLeftPressed : buttonRightPressed));
      z.continuous = false;
      waitForPendingPos0(&z);

      if (isOn && mode == MODE_CONE) {
        if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
          setEmergencyStop(ESTOP_MARK_ORIGIN);
        } else {
          markOrigin();
          xSemaphoreGive(motionMutex);
        }
      } else if (isOn && mode == MODE_ASYNC) {
        // Restore async direction.
        updateAsyncTimerSettings();
      }
    }
    z.movingManually = false;
    if (stepperOn) {
      stepperEnable(&z, false);
    }
    z.speedMax = LONG_MAX;
    taskYIELD();
  }
  vTaskDelete(NULL);
}

void taskMoveX(void *param) {

  while (emergencyStop == ESTOP_NONE) {
    int pulseDelta = getAndResetPulses(&x);
    bool up = buttonUpPressed || pulseDelta > 0;
    bool down = buttonDownPressed || pulseDelta < 0;
    if (!up && !down) {
      taskYIELD();
      continue;
    }

    if (isOn && !manualMovesAllowedWhenOn()) {
      setIsOnFromTask(false);
    }
    x.movingManually = true;
    x.speedMax = getStepMaxSpeed(&x);
    stepperEnable(&x, true);

    int delta = 0;
    int sign = up ? 1 : -1;
    do {
      float fractionalDelta = (pulseDelta == 0 ? moveStep * sign / x.screwPitch : pulseDelta / PULSE_PER_REVOLUTION) * x.motorSteps + x.fractionalPos;
      delta = round(fractionalDelta);
      // Don't lose fractional steps when moving by 0.01" or 0.001".
      x.fractionalPos = fractionalDelta - delta;
      if (delta == 0) {
        // When moveStep is e.g. 1 micron and MOTOR_STEPS_Z is 200, make delta non-zero.
        delta = sign;
      }

      long posCopy = x.pos + x.pendingPos;
      if (posCopy + delta > x.leftStop) {
        delta = x.leftStop - posCopy;
      } else if (posCopy + delta < x.rightStop) {
        delta = x.rightStop - posCopy;
      }
      stepToContinuous(&x, posCopy + delta);
      waitForStep(&x);
      pulseDelta = getAndResetPulses(&x);
    } while (delta != 0 && (pulseDelta != 0 || (up ? buttonUpPressed : buttonDownPressed)));
    x.continuous = false;
    waitForPendingPos0(&x);

    if (isOn && mode == MODE_CONE) {
      if (xSemaphoreTake(motionMutex, 100) != pdTRUE) {
        setEmergencyStop(ESTOP_MARK_ORIGIN);
      } else {
        markOrigin();
        xSemaphoreGive(motionMutex);
      }
    }
    x.movingManually = false;
    x.speedMax = LONG_MAX;
    stepperEnable(&x, false);

    taskYIELD();
  }
  vTaskDelete(NULL);
}

void taskMoveA1(void *param) {
  while (emergencyStop == ESTOP_NONE) {
    bool plus, minus;
    
    if (mode == MODE_A1) {
      plus = buttonTurnPressed;
      minus = buttonGearsPressed;
    } else if (mode == MODE_GCODE && ACTIVE_A1) {
      plus = buttonPlusPressed;
      minus = buttonMinusPressed;
    } else {
      taskYIELD();
      continue;
    }
    
    if (!plus && !minus) {
      taskYIELD();
      continue;
    }
    a1.movingManually = true;
    a1.speedMax = getStepMaxSpeed(&a1);
    stepperEnable(&a1, true);

    int delta = 0;
    int sign = plus ? 1 : -1;
    do {
      float fractionalDelta = getMoveStepForAxis(&a1) * sign / a1.screwPitch * a1.motorSteps + a1.fractionalPos;
      delta = round(fractionalDelta);
      a1.fractionalPos = fractionalDelta - delta;
      if (delta == 0) delta = sign;

      long posCopy = a1.pos + a1.pendingPos;
      if (posCopy + delta > a1.leftStop) {
        delta = a1.leftStop - posCopy;
      } else if (posCopy + delta < a1.rightStop) {
        delta = a1.rightStop - posCopy;
      }
      stepToContinuous(&a1, posCopy + delta);
      waitForStep(&a1);
    } while (plus ? (mode == MODE_A1 ? buttonTurnPressed : buttonPlusPressed) : 
                    (mode == MODE_A1 ? buttonGearsPressed : buttonMinusPressed));
    a1.continuous = false;
    waitForPendingPos0(&a1);
    // Restore async direction.
    if (isOn && mode == MODE_A1) updateAsyncTimerSettings();
    a1.movingManually = false;
    a1.speedMax = LONG_MAX;
    stepperEnable(&a1, false);
    taskYIELD();
  }
  vTaskDelete(NULL);
}

void processMPGSerial() {
  static String mpgCommand = "";
  
  while (Serial1.available() > 0) {
    char c = Serial1.read();
    if (c == '\n' || c == '\r') {
      if (mpgCommand.length() > 0) {
        processMPGCommand(mpgCommand);
        mpgCommand = "";
      }
    } else if (c >= 32) {
      mpgCommand += c;
    }
  }

  // Process accumulated deltas with scaling for detents
  if (mpgEnabled && xSemaphoreTake(mpgMutex, 10) == pdTRUE) {
    bool processed = false;
    if (mpgDeltaX != 0 && mpgActiveAxis == 'X' && !x.movingManually) {
      int clicks = mpgDeltaX;  // Already detents from pendant
      mpgDeltaX = 0;
      xSemaphoreGive(mpgMutex);
      applyMPGMovement(&x, clicks);
      processed = true;
    } 
    else if (mpgDeltaZ != 0 && mpgActiveAxis == 'Z' && !z.movingManually) {
      int clicks = mpgDeltaZ;  // Already detents from pendant
      mpgDeltaZ = 0;
      xSemaphoreGive(mpgMutex);
      applyMPGMovement(&z, clicks);
      processed = true;
    }
    else if (mpgDeltaA1 != 0 && mpgActiveAxis == 'Y' && !a1.movingManually && ACTIVE_A1) {
      int clicks = mpgDeltaA1;  // Already detents from pendant
      mpgDeltaA1 = 0;
      xSemaphoreGive(mpgMutex);
      applyMPGMovement(&a1, clicks);
      processed = true;
    }

    if (!processed) {
      xSemaphoreGive(mpgMutex);
    }
  }
}

void taskMPG(void *param) {
  String mpgCommand = "";
  unsigned long lastTest = 0;

  Serial.println("taskMPG: Started and running"); 

  while (emergencyStop == ESTOP_NONE) {

    // Read commands from ESP32-C6 via Serial1
    while (Serial1.available() > 0) {
      char c = Serial1.read();

      if (c == '\n' || c == '\r') {
        if (mpgCommand.length() > 0) {
          processMPGCommand(mpgCommand);
          mpgCommand = "";
        }
      } else if (c >= 32) {
        mpgCommand += c;
      }
    }
    
    // Process accumulated deltas with scaling for detents
    if (mpgEnabled && xSemaphoreTake(mpgMutex, 10) == pdTRUE) {
    bool processed = false;
    
    if (mpgDeltaX != 0 && mpgActiveAxis == 'X' && !x.movingManually) {
      int clicks = mpgDeltaX;  // Already detents from pendant
      mpgDeltaX = 0;
      xSemaphoreGive(mpgMutex);
      applyMPGMovement(&x, clicks);
      processed = true;
    } 
    else if (mpgDeltaZ != 0 && mpgActiveAxis == 'Z' && !z.movingManually) {
      int clicks = mpgDeltaZ;  // Already detents from pendant
      mpgDeltaZ = 0;
      xSemaphoreGive(mpgMutex);
      applyMPGMovement(&z, clicks);
      processed = true;
    }
    else if (mpgDeltaA1 != 0 && mpgActiveAxis == 'Y' && !a1.movingManually && ACTIVE_A1) {
      int clicks = mpgDeltaA1;  // Already detents from pendant
      mpgDeltaA1 = 0;
      xSemaphoreGive(mpgMutex);
      applyMPGMovement(&a1, clicks);
      processed = true;
    }
    
    if (!processed) {
      xSemaphoreGive(mpgMutex);
    }
  }
    
  taskYIELD();
  }

  vTaskDelete(NULL);
}

void applyMPGMovement(Axis* a, int detents) {

  // Block MPG during threading mode
  if (mode == MODE_THREAD) {
    Serial.println("BLOCKED: Thread mode");
    return;
  }
  
  // Block MPG when G-code system is active
  if (isOn) {
    Serial.println("BLOCKED: isOn true");
    return;
  }
  
  // detents are already scaled - one detent = one increment of mpgStepSize
  
  // Calculate movement in steps
  float fractionalDelta = (mpgStepSize * detents / a->screwPitch) * a->motorSteps + a->fractionalPos;
  long delta = round(fractionalDelta);
  a->fractionalPos = fractionalDelta - delta;
  
  if (delta == 0 && detents != 0) {
    delta = detents > 0 ? 1 : -1;
  }
  
  // Check limits
  long posCopy = a->pos + a->pendingPos;
  if (posCopy + delta > a->leftStop) {
    delta = a->leftStop - posCopy;
    beepFlag = true;
  } else if (posCopy + delta < a->rightStop) {
    delta = a->rightStop - posCopy;
    beepFlag = true;
  }
  
  if (delta == 0) {
    return;
  }
  
  // Enable stepper and apply movement
  stepperEnable(a, true);
  a->speedMax = a->speedManualMove / 2;
  stepToContinuous(a, posCopy + delta);
}

void processMPGCommand(const String& cmd) {
  // Command formats:
  // AXIS:X       - Set active axis to X
  // AXIS:Z       - Set active axis to Z
  // AXIS:Y       - Set active axis to Y (A1)
  // AXIS:N       - Set active axis to None (OFF)
  // STEP:1000    - Set step size (in deci-microns)
  // JOG:5        - Jog active axis by 5 clicks
  // JOG:-3       - Jog active axis by -3 clicks
  // !            - Feed hold (from keypad STOP button)
  // ~            - Resume (from keypad PLAY button)
  // ?            - Get status
  // T4           - Change to tool 4
  // G92 ...      - Zero axis commands from keypad

  if (cmd == "?") {
    static unsigned long lastMPGStatusTime = 0;
    unsigned long now = millis();
    
    // Respond at most every 50ms (20Hz)
    if (now - lastMPGStatusTime >= 50) {
      printMPGStatusResponse();
      lastMPGStatusTime = now;
    }
    // Silently ignore if too soon
  } else if (cmd == "!") {
    stopRequested = true;
    mpgEnabled = true;
    setIsOnFromTask(false);
    Serial1.println("OK:HOLD");
  } else if (cmd == "~") {
    stopRequested = false;
    mpgEnabled = false;
    setIsOnFromTask(true);
    Serial1.println("OK:RESUME");
  } else if (cmd.startsWith("AXIS:")) {
    char axis = cmd.charAt(5);
    if (xSemaphoreTake(mpgMutex, 100) == pdTRUE) {
      if (axis == 'X' || axis == 'Z' || axis == 'Y' || axis == 'N') {
        mpgActiveAxis = axis;
        Serial1.printf("OK:AXIS:%c\n", axis);
      }
      xSemaphoreGive(mpgMutex);
    } else {
      Serial.println("Failed to get mutex");
    }
  } 
  else if (cmd.startsWith("STEP:")) {
    long stepSize = cmd.substring(5).toInt();
    if (stepSize > 0 && stepSize <= 100000) { // Max 10mm per click
      if (xSemaphoreTake(mpgMutex, 100) == pdTRUE) {
        mpgStepSize = stepSize;
        Serial1.printf("OK:STEP:%ld\n", stepSize);
        xSemaphoreGive(mpgMutex);
      }
    }
  }
  else if (cmd.startsWith("JOG:")) {
    int clicks = cmd.substring(4).toInt();
    if (clicks != 0 && mpgEnabled) {
      // CRITICAL: Always accumulate, even if mutex busy
      // Use portMAX_DELAY to wait as long as needed
      if (xSemaphoreTake(mpgMutex, portMAX_DELAY) == pdTRUE) {
        // Accumulate clicks per axis - these will be processed by taskMPG
        if (mpgActiveAxis == 'X') {
          mpgDeltaX += MPG_INVERT_X ? -clicks : clicks;
        } else if (mpgActiveAxis == 'Z') {
          mpgDeltaZ += MPG_INVERT_Z ? -clicks : clicks;
        } else if (mpgActiveAxis == 'Y') {
          mpgDeltaA1 += MPG_INVERT_A1 ? -clicks : clicks;
        }
        xSemaphoreGive(mpgMutex);
      }
    }
  } else if (cmd.startsWith("G92")) {
    // Handle zero commands from keypad
    // Process as G-code command
    handleG92(cmd);
    Serial1.println("OK:ZERO");
  } else if (cmd.startsWith("G28")) {
    // Handle zero commands from keypad
    // Process as G-code command
    handleG28(cmd);
    Serial1.println("OK:HOME");
  } else if (cmd.startsWith("T")) {
    handleChangeToolCommand(cmd);
    Serial1.println("OK:TOOLCHANGE");
  }
}

void taskGcode(void *param) {
  while (emergencyStop == ESTOP_NONE) {

    processMPGSerial();

    if (mode != MODE_GCODE) {
      gcodeInitialized = false;
    } else if (!gcodeInitialized) {
      gcodeInitialized = true;
      gcodeCommand = "";
      gcodeAbsolutePositioning = true;
      gcodeFeedDuPerSec = GCODE_FEED_DEFAULT_DU_SEC;
      gcodeInBrace = false;
      gcodeInSemicolon = false;
    }

    // Implementing a relevant subset of RS274 (Gcode) and GRBL (state management) covering basic use cases.
    char receivedChar = '\0';
    if (Serial.available() > 0) {
      receivedChar = Serial.read();
    }

    int charCode = int(receivedChar);
    if (charCode > 0) {
      if (gcodeInBrace) {
        if (receivedChar == ')') gcodeInBrace = false;
      } else if (receivedChar == '(') {
        gcodeInBrace = true;
      } else if (receivedChar == ';' /* start of comment till end of line */) {
        gcodeInSemicolon = true;
      } else if (gcodeInSemicolon && charCode >= 32) {
        // Ignoring comment.
      } else if (receivedChar == '!' /* stop */) {
        stopRequested = true;
        setIsOnFromTask(false);
      } else if (receivedChar == '~' /* resume */) {
        stopRequested = false;
        setIsOnFromTask(true);
      } else if (receivedChar == '%' /* start/end marker */) {
        // Not using % markers in this implementation.
      } else if (receivedChar == '?' /* status */) {
        printStatusResponse();
      } else if (receivedChar == '^' /* debug */) {
        printDebugResponse();
      } else if (receivedChar == '#' /* custom command for listing tool offsets*/) {
        listToolOffsets();
      } else if (receivedChar == '$') {
        printBacklashValues();
      } else {
        if (gcodeInBrace && charCode < 32) {
          Serial.println("error: comment not closed");
          setIsOnFromTask(false);
        } else if (charCode < 32 && gcodeCommand.length() > 1) { 
          if (handleGcodeCommand(gcodeCommand)) {
              Serial.println("ok");
          }
          gcodeCommand = "";
          gcodeInSemicolon = false;
        } else if (charCode < 32) {
          Serial.println("ok");
          gcodeCommand = "";
        } else if (charCode >= 32 && (charCode == 'G' || charCode == 'M' || charCode == 'T')) {
          // Split consequent G and M commands on one line.
          // No "ok" for commands in the middle of the line.
          if (gcodeCommand.length() > 0) {
            handleGcodeCommand(gcodeCommand);
          }
          gcodeCommand = receivedChar;
        } else if (charCode >= 32) {
          gcodeCommand += receivedChar;
        } else {
          // Ignoring other control characters. 
        }
      } 
    }
    taskYIELD();
  }
  vTaskDelete(NULL);
}

void printMPGStatusResponse() {
  Serial1.print("<");
  Serial1.print("Status:");
  Serial1.print(isOn ? "RUNNING" : "READY"); 
  Serial1.print("|WPos:");
  float divisor = measure == MEASURE_METRIC ? 10000.0 : 254000.0;
  Serial1.print(getAxisPosDu(&x) / divisor, 4);
  Serial1.print(",");
  Serial1.print(getAxisPosDu(&a1) / divisor, 4);
  Serial1.print(",");
  Serial1.print(getAxisPosDu(&z) / divisor, 4);
  Serial1.print("|Tool:");
  Serial1.print(currentTool);
  Serial1.print("|Steppers:");
  Serial1.print(x.disabled ? "0" : "1");
  Serial1.print(",");
  Serial1.print(a1.active && !a1.disabled ? "1" : "0");
  Serial1.print(",");
  Serial1.print(z.disabled ? "0" : "1");
  Serial1.print("|FS:");
  Serial1.print(round(gcodeFeedDuPerSec * 60 / 10000.0));
  Serial1.print(",");
  Serial1.print(getApproxRpm());
  Serial1.print(",");
  Serial1.print(spindleModulo(spindlePos) * 360 / ENCODER_STEPS_FLOAT);
  Serial1.print("|MPG:");
  Serial1.print((char)mpgActiveAxis);
  Serial1.print(",");
  Serial1.print(mpgStepSize);
  Serial1.print(">");
  Serial1.print("\r\n"); 
}

void printStatusResponse() {
  Serial.print("<");
  bool movingNow =
  (abs(x.pendingPos) > 0) ||
  (abs(z.pendingPos) > 0) ||
  (abs(a1.pendingPos) > 0);
  Serial.print(movingNow ? "Run" : "Idle");
  Serial.print("|WPos:");
  float divisor = measure == MEASURE_METRIC ? 10000.0 : 254000.0;
  Serial.print(getAxisPosDu(&x) / divisor, 3);
  Serial.print(",");
  Serial.print(getAxisPosDu(&a1) / divisor, 3);
  Serial.print(",");
  Serial.print(getAxisPosDu(&z) / divisor, 3);
  Serial.print("|Tool:");
  Serial.print(currentTool);
  Serial.print("|Steppers:");
  Serial.print(x.disabled ? "0" : "1");
  Serial.print(",");
  Serial.print(a1.active && !a1.disabled ? "1" : "0");
  Serial.print(",");
  Serial.print(z.disabled ? "0" : "1");
  Serial.print("|FS:");
  Serial.print(round(gcodeFeedDuPerSec * 60 / 10000.0));
  Serial.print(",");
  Serial.print(getApproxRpm());
  Serial.print(",");
  Serial.print(spindleModulo(spindlePos) * 360 / ENCODER_STEPS_FLOAT);
  Serial.print("|Id:H" + String(HARDWARE_VERSION) + "V" + String(SOFTWARE_VERSION) + "FJ>");
  Serial.print("\r\n"); 
}

void printDebugResponse() {
  Serial.println("=== DEBUG INFO ===");

  //Print current mode
  Serial.print("Mode: ");
  switch (mode) {
    case MODE_NORMAL: Serial.println("NORMAL"); break;
    case MODE_THREAD: Serial.println("THREAD"); break;
    case MODE_GCODE: Serial.println("GCODE"); break;
    default: Serial.println("UNKNOWN"); break;
  }
  
  // Position tracking (the mismatch we found!)
  Serial.print("Z: pos="); Serial.print(z.pos);
  Serial.print(" motorPos="); Serial.print(z.motorPos);
  Serial.print(" originPos="); Serial.print(z.originPos);
  Serial.print(" pendingPos="); Serial.println(z.pendingPos);
  
  Serial.print("X: pos="); Serial.print(x.pos);
  Serial.print(" motorPos="); Serial.print(x.motorPos);
  Serial.print(" originPos="); Serial.print(x.originPos);
  Serial.print(" pendingPos="); Serial.println(x.pendingPos);

  Serial.print("Y: pos="); Serial.print(a1.pos);
  Serial.print(" motorPos="); Serial.print(a1.motorPos);
  Serial.print(" originPos="); Serial.print(a1.originPos);
  Serial.print(" pendingPos="); Serial.println(a1.pendingPos);
  
  // Coordinate system state
  Serial.print("G-code: ");
  Serial.print(gcodeAbsolutePositioning ? "G90(abs)" : "G91(rel)");
  Serial.print(" Z.gcodeRelPos="); Serial.print(z.gcodeRelativePos);
  Serial.print(" X.gcodeRelPos="); Serial.print(x.gcodeRelativePos);
  Serial.print(" Y.gcodeRelPos="); Serial.println(a1.gcodeRelativePos);
  
  // Limits (the issue we investigated)
  Serial.print("Z limits: left="); Serial.print(z.leftStop);
  Serial.print(" right="); Serial.println(z.rightStop);
  Serial.print("X limits: left="); Serial.print(x.leftStop);
  Serial.print(" right="); Serial.println(x.rightStop);
  Serial.print("Y limits: left="); Serial.print(a1.leftStop);
  Serial.print(" right="); Serial.println(a1.rightStop);
  
  // Motion state
  Serial.print("Motion: isOn="); Serial.print(isOn);
  Serial.print(" eStop="); Serial.print(emergencyStop);
  Serial.print(" mode="); Serial.println(mode);
  
  // Tool offsets (the issue we suspected)
  Serial.print("Tool: current="); Serial.print(currentTool);
  Serial.print(" appliedOffset Z="); Serial.print(currentAppliedOffset.zOffsetDu / 10000.0, 3);
  Serial.print(" X="); Serial.println(currentAppliedOffset.xOffsetDu / 10000.0, 3);

  // Backlash
  Serial.print("Backlash: Z="); Serial.print(z.backlashSteps);
  Serial.print(" X="); Serial.print(x.backlashSteps);
  Serial.print(" Y="); Serial.println(a1.backlashSteps);

  Serial.println("==================");
  Serial.print("\r\n");
}

bool listToolOffsets() {
    String toolOffsetsStr = "toolOffsets:";
    for (int i = 0; i < MAX_TOOLS; ++i) {
        toolOffsetsStr += "T";
        toolOffsetsStr += String(i);
        toolOffsetsStr += ":";
        toolOffsetsStr += "Z=";
        toolOffsetsStr += String(toolOffsets[i].zOffsetDu / 10000.0, 3);
        toolOffsetsStr += ",";
        toolOffsetsStr += "X=";
        toolOffsetsStr += String(toolOffsets[i].xOffsetDu / 10000.0, 3);
        toolOffsetsStr += ",";
        toolOffsetsStr += "W=";
        toolOffsetsStr += String(toolOffsets[i].zCompDu / 10000.0, 3);
        toolOffsetsStr += ",";
        toolOffsetsStr += "U=";
        toolOffsetsStr += String(toolOffsets[i].xCompDu / 10000.0, 3);
        if(i < MAX_TOOLS -1) {
          toolOffsetsStr += "|";
        }
    }
    Serial.print(toolOffsetsStr);
    Serial.println();

    return true;
}

bool printBacklashValues() {
  
  Serial.println();
  Serial.print("Backlash values (mm): ");
  Serial.print(z.name);
  Serial.print("=");
  Serial.print(z.backlashDu / 10000.0, 4);
  Serial.print(" ");
  
  Serial.print(x.name);
  Serial.print("=");
  Serial.print(x.backlashDu / 10000.0, 4);
  
  if (ACTIVE_A1) {
    Serial.print(" ");
    Serial.print(a1.name);
    Serial.print("=");
    Serial.print(a1.backlashDu / 10000.0, 4);
  }
  
  Serial.println();
  return true;
}

void startPulseCounter(pcnt_unit_t unit, int gpioA, int gpioB) {
  pcnt_config_t pcntConfig;
  pcntConfig.pulse_gpio_num = gpioA;
  pcntConfig.ctrl_gpio_num = gpioB;
  pcntConfig.channel = PCNT_CHANNEL_0;
  pcntConfig.unit = unit;
  pcntConfig.pos_mode = PCNT_COUNT_INC;
  pcntConfig.neg_mode = PCNT_COUNT_DEC;
  pcntConfig.lctrl_mode = PCNT_MODE_REVERSE;
  pcntConfig.hctrl_mode = PCNT_MODE_KEEP;
  pcntConfig.counter_h_lim = PCNT_LIM;
  pcntConfig.counter_l_lim = -PCNT_LIM;
  pcnt_unit_config(&pcntConfig);
  pcnt_set_filter_value(unit, ENCODER_FILTER);
	pcnt_filter_enable(unit);
  pcnt_counter_pause(unit);
  pcnt_counter_clear(unit);
  pcnt_counter_resume(unit);
}

// Attaching interrupt on core 0 to have more time on core 1 where axes are moved.
void taskAttachInterrupts(void *param) {
  startPulseCounter(PCNT_UNIT_0, ENC_A, ENC_B);
  vTaskDelete(NULL);
}

void setEmergencyStop(int kind) {
  emergencyStop = kind;
  setAsyncTimerEnable(false);
  xSemaphoreTake(z.mutex, 10);
  xSemaphoreTake(x.mutex, 10);
  xSemaphoreTake(a1.mutex, 10);
}

void setupMPG() {

  // Initialize MPG mutex
  mpgMutex = xSemaphoreCreateMutex();

  // Load preferences with validation
  Preferences pref;
  pref.begin(PREF_NAMESPACE);
  
  char loadedAxis = pref.getChar(PREF_MPG_AXIS, 'N');
  long loadedStep = pref.getLong(PREF_MPG_STEP, MOVE_STEP_2);
  
  // Validate before using
  if (loadedAxis == 'X' || loadedAxis == 'Y' || 
      loadedAxis == 'Z' || loadedAxis == 'N') {
    mpgActiveAxis = savedMpgActiveAxis = loadedAxis;
  } else {
    Serial.println("Invalid axis in prefs, using default 'N'");
    mpgActiveAxis = savedMpgActiveAxis = 'N';
  }
  
  if (loadedStep > 0 && loadedStep <= 100000) {
    mpgStepSize = savedMpgStepSize = loadedStep;
  } else {
    Serial.println("Invalid step size in prefs, using default");
    mpgStepSize = savedMpgStepSize = MOVE_STEP_2;
  }
  
  pref.end();
  
  Serial.print("MPG prefs - Axis: ");
  Serial.print((char)mpgActiveAxis);
  Serial.print(", Step: ");
  Serial.println(mpgStepSize);
  
  // Initialize Serial1 for MPG communication
  Serial1.begin(115200, SERIAL_8N1, MPG_RX_PIN, MPG_TX_PIN);

  delay(100); 
  
  Serial.println("MPG controller initialized");
}

void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  pinMode(Z_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT);
  pinMode(Z_ENA, OUTPUT);
  DHIGH(Z_STEP);

  pinMode(X_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(X_ENA, OUTPUT);
  DHIGH(X_STEP);

  if (ACTIVE_A1) {
    pinMode(Y_DIR, OUTPUT);
    pinMode(Y_STEP, OUTPUT);
    pinMode(Y_ENA, OUTPUT); 
    DHIGH(Y_STEP);
  }

  pinMode(X_HOME_SENSOR_PIN, INPUT_PULLUP);

  pinMode(BUZZ, OUTPUT);

  Serial.begin(115200);

  delay(100);

  Preferences pref;
  pref.begin(PREF_NAMESPACE);

  if (pref.getInt(PREF_VERSION) != PREFERENCES_VERSION) {
      Serial.println("New pref version. Wiping.");
    pref.clear();
    pref.putInt(PREF_VERSION, PREFERENCES_VERSION);
  }

  initAxis(&z, NAME_Z, true, false, MOTOR_STEPS_Z, SCREW_Z_DU, SPEED_START_Z, SPEED_MANUAL_MOVE_Z, ACCELERATION_Z, INVERT_Z, NEEDS_REST_Z, MAX_TRAVEL_MM_Z, BACKLASH_DU_Z, Z_ENA, Z_DIR, Z_STEP);
  initAxis(&x, NAME_X, true, false, MOTOR_STEPS_X, SCREW_X_DU, SPEED_START_X, SPEED_MANUAL_MOVE_X, ACCELERATION_X, INVERT_X, NEEDS_REST_X, MAX_TRAVEL_MM_X, BACKLASH_DU_X, X_ENA, X_DIR, X_STEP);
  initAxis(&a1, NAME_A1, ACTIVE_A1, false, MOTOR_STEPS_A1, SCREW_A1_DU, SPEED_START_A1, SPEED_MANUAL_MOVE_A1, ACCELERATION_A1, INVERT_A1, NEEDS_REST_A1, MAX_TRAVEL_MM_A1, BACKLASH_DU_A1, Y_ENA, Y_DIR, Y_STEP);

  // Load saved backlash values (after initAxis)
  z.savedBacklashDu = z.backlashDu = pref.getLong(PREF_BACKLASH_Z, BACKLASH_DU_Z);
  z.backlashSteps = z.backlashDu * z.motorSteps / z.screwPitch;
  
  x.savedBacklashDu = x.backlashDu = pref.getLong(PREF_BACKLASH_X, BACKLASH_DU_X);
  x.backlashSteps = x.backlashDu * x.motorSteps / x.screwPitch;
  
  if (ACTIVE_A1) {
    a1.savedBacklashDu = a1.backlashDu = pref.getLong(PREF_BACKLASH_A1, BACKLASH_DU_A1);
    a1.backlashSteps = a1.backlashDu * a1.motorSteps / a1.screwPitch;
  }

  isOn = false;
  gcodeMotionMode = 0;  // Initialize once at startup
  savedDupr = dupr = pref.getLong(PREF_DUPR);
  motionMutex = xSemaphoreCreateMutex();
  savedStarts = starts = min(STARTS_MAX, max(static_cast<int32_t>(1), pref.getInt(PREF_STARTS)));

  a1.savedDisabled = a1.disabled = pref.getBool(PREF_DISABLED_A1, false);
  savedSpindlePos = spindlePos = pref.getLong(PREF_SPINDLE_POS);
  savedSpindlePosAvg = spindlePosAvg = pref.getLong(PREF_SPINDLE_POS_AVG);
  savedSpindlePosSync = spindlePosSync = pref.getInt(PREF_OUT_OF_SYNC);
  savedSpindlePosGlobal = spindlePosGlobal = pref.getLong(PREF_SPINDLE_POS_GLOBAL);
  savedShowAngle = showAngle = pref.getBool(PREF_SHOW_ANGLE);
  savedShowTacho = showTacho = pref.getBool(PREF_SHOW_TACHO);
  savedMoveStep = moveStep = pref.getLong(PREF_MOVE_STEP, MOVE_STEP_1);
  setModeFromLoop(MODE_NORMAL);
  savedMeasure = measure = pref.getInt(PREF_MEASURE);
  savedConeRatio = coneRatio = pref.getFloat(PREF_CONE_RATIO, coneRatio);
  savedTurnPasses = turnPasses = pref.getInt(PREF_TURN_PASSES, turnPasses);
  savedAuxForward = auxForward = pref.getBool(PREF_AUX_FORWARD, true);
  currentTool = 0;

  loadToolOffsets(pref);

  currentAppliedOffset = {0, 0, 0, 0};

  x_home_position_saved = x_home_position = pref.getFloat(PREF_X_HOME_POSITION, -80.0);
  x_home_position_calibrated = x_home_position;

  y_home_position_saved = y_home_position = pref.getFloat(PREF_Y_HOME_POSITION, -80.0);
  y_home_position_calibrated = y_home_position;

  z_home_position_saved = z_home_position = pref.getFloat(PREF_Z_HOME_POSITION, -80.0);
  z_home_position_calibrated = z_home_position;

  shownRpm = 0;
  spindleEncTimeDiffBulk = 0;

  //reset(); //load defaults on power on

  pref.end();

  if (!z.needsRest && !z.disabled) {
    DHIGH(z.ena);
  }
  if (!x.needsRest && !x.disabled) {
    DHIGH(x.ena);
  }
  if (a1.active && !a1.needsRest && !a1.disabled) {
    DHIGH(a1.ena);
  }

  if (!z.needsRest && !z.disabled && DEFAULT_ENABLE_Z) {
    DHIGH(z.ena);
  } else {
    z.disabled = !DEFAULT_ENABLE_Z;
    updateEnable(&z);
  }
  
  if (!x.needsRest && !x.disabled && DEFAULT_ENABLE_X) {
    DHIGH(x.ena);
  } else {
    x.disabled = !DEFAULT_ENABLE_X;
    updateEnable(&x);
  }
  
  if (a1.active) {
    a1.disabled = !DEFAULT_ENABLE_A1;
    updateEnable(&a1);
  }

  delay(1000);

  setupMPG();

  xTaskCreatePinnedToCore(taskAttachInterrupts, "taskAttachInterrupts", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
  xTaskCreatePinnedToCore(taskGcode, "taskGcode", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);

  //xTaskCreatePinnedToCore(taskMPG, "taskMPG", 10000 /* stack size */, NULL, 0 /* priority */, NULL, 0 /* core */);
}

bool saveToPrefs() {

  Preferences pref;
  pref.begin(PREF_NAMESPACE);

  if (dupr != savedDupr) pref.putLong(PREF_DUPR, savedDupr = dupr);
  if (starts != savedStarts) pref.putInt(PREF_STARTS, savedStarts = starts);
  if (showAngle != savedShowAngle) pref.putBool(PREF_SHOW_ANGLE, savedShowAngle = showAngle);
  if (showTacho != savedShowTacho) pref.putBool(PREF_SHOW_TACHO, savedShowTacho = showTacho);
  if (moveStep != savedMoveStep) pref.putLong(PREF_MOVE_STEP, savedMoveStep = moveStep);
  if (mode != savedMode) pref.putInt(PREF_MODE, savedMode = mode);
  if (measure != savedMeasure) pref.putInt(PREF_MEASURE, savedMeasure = measure);
  if (coneRatio != savedConeRatio) pref.putFloat(PREF_CONE_RATIO, savedConeRatio = coneRatio);
  if (turnPasses != savedTurnPasses) pref.putInt(PREF_TURN_PASSES, savedTurnPasses = turnPasses);
  if (auxForward != savedAuxForward) pref.putBool(PREF_AUX_FORWARD, savedAuxForward = auxForward);

  if (areToolOffsetsChanged()) saveToolOffsets(pref);
  if (z.backlashDu != z.savedBacklashDu) pref.putLong(PREF_BACKLASH_Z, z.savedBacklashDu = z.backlashDu);
  if (x.backlashDu != x.savedBacklashDu) pref.putLong(PREF_BACKLASH_X, x.savedBacklashDu = x.backlashDu);
  if (ACTIVE_A1 && a1.backlashDu != a1.savedBacklashDu) pref.putLong(PREF_BACKLASH_A1, a1.savedBacklashDu = a1.backlashDu);

    // Save MPG prefs using the constants
  if (mpgActiveAxis != savedMpgActiveAxis) {
    pref.putChar(PREF_MPG_AXIS, savedMpgActiveAxis = mpgActiveAxis);
  }
  if (mpgStepSize != savedMpgStepSize) {
    pref.putLong(PREF_MPG_STEP, savedMpgStepSize = mpgStepSize);
  }

  if (x_home_position != x_home_position_saved) {
      pref.putFloat(PREF_X_HOME_POSITION, x_home_position);
      x_home_position_saved = x_home_position;
  }

  if (y_home_position != y_home_position_saved) {
      pref.putFloat(PREF_Y_HOME_POSITION, y_home_position);
      y_home_position_saved = y_home_position;
  }

   if (z_home_position != z_home_position_saved) {
       pref.putFloat(PREF_Z_HOME_POSITION, z_home_position);
       z_home_position_saved = z_home_position;
   }

  offsetsChanged = false;

  pref.end();
  return true;
}

bool areToolOffsetsChanged() {
  for (int i = 0; i < MAX_TOOLS; ++i) {
    if (toolOffsets[i].xOffsetDu != savedToolOffsets[i].xOffsetDu ||
        toolOffsets[i].zOffsetDu != savedToolOffsets[i].zOffsetDu ||
        toolOffsets[i].xCompDu != savedToolOffsets[i].xCompDu ||
        toolOffsets[i].zCompDu != savedToolOffsets[i].zCompDu) {
      return true;
    }
  }
  return false;
}

void saveToolOffsets(Preferences& pref) {
    for (int i = 0; i < MAX_TOOLS; ++i) {
        String xKey = "tool" + String(i) + "X";
        String zKey = "tool" + String(i) + "Z";
        String xCompKey = "tool" + String(i) + "U";  // Using U to match G-code parameter
        String zCompKey = "tool" + String(i) + "W";  // Using W to match G-code parameter

        pref.putFloat(xKey.c_str(), toolOffsets[i].xOffsetDu);
        pref.putFloat(zKey.c_str(), toolOffsets[i].zOffsetDu);
        pref.putFloat(xCompKey.c_str(), toolOffsets[i].xCompDu);
        pref.putFloat(zCompKey.c_str(), toolOffsets[i].zCompDu);
    }
}

void loadToolOffsets(Preferences& pref) {
    for (int i = 0; i < MAX_TOOLS; ++i) {
        String xKey = "tool" + String(i) + "X";
        String zKey = "tool" + String(i) + "Z";
        String xCompKey = "tool" + String(i) + "U";
        String zCompKey = "tool" + String(i) + "W";

        toolOffsets[i].xOffsetDu = pref.getFloat(xKey.c_str(), 0.0);
        toolOffsets[i].zOffsetDu = pref.getFloat(zKey.c_str(), 0.0);
        toolOffsets[i].xCompDu = pref.getFloat(xCompKey.c_str(), 0.0);
        toolOffsets[i].zCompDu = pref.getFloat(zCompKey.c_str(), 0.0);

        // Update saved values
        savedToolOffsets[i] = toolOffsets[i];
    }
}

void markAxisOrigin(Axis* a) {
  bool hasSemaphore = xSemaphoreTake(a->mutex, 10) == pdTRUE;
  if (!hasSemaphore) {
    beepFlag = true;
  }
  if (a->leftStop != LONG_MAX) {
    a->leftStop -= a->pos;
  }
  if (a->rightStop != LONG_MIN) {
    a->rightStop -= a->pos;
  }
  a->motorPos -= a->pos;
  a->originPos += a->pos;
  a->pos = 0;
  a->fractionalPos = 0;
  a->pendingPos = 0;
  if (hasSemaphore) {
    xSemaphoreGive(a->mutex);
  }
}

void zeroSpindlePos() {
  spindlePos = 0;
  spindlePosAvg = 0;
  spindlePosSync = 0;
}

// Loose the thread and mark current physical positions of
// encoder and stepper as a new 0. To be called when dupr changes
// or ELS is turned on/off. Without this, changing dupr will
// result in stepper rushing across the lathe to the new position.
// Must be called while holding motionMutex.
void markOrigin() {
  markAxisOrigin(&z);
  markAxisOrigin(&x);
  markAxisOrigin(&a1);
  zeroSpindlePos();
}

void markAxis0(Axis* a) {
  a->originPos = -a->pos;
}

Axis* getAsyncAxis() {
  return mode == MODE_A1 ? &a1 : &z;
}

void updateAsyncTimerSettings() {
  // dupr and therefore direction can change while we're in async mode.
  setDir(getAsyncAxis(), dupr > 0);

  // dupr can change while we're in async mode, keep updating timer frequency.
  timerAlarm(async_timer, getTimerLimit(), true, 0);
  // without this timer stops working if already above new limit
  timerWrite(async_timer, 0);
}

void setDupr(long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextDupr = value;
  nextDuprFlag = true;
}

// Must be called while holding motionMutex.
void applyDupr() {
  if (nextDupr == dupr) {
    return;
  }
  dupr = nextDupr;
  markOrigin();
  if (mode == MODE_ASYNC || mode == MODE_A1) {
    updateAsyncTimerSettings();
  }
}

void setStarts(int value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextStarts = value;
  nextStartsFlag = true;
}

// Must be called while holding motionMutex.
void applyStarts() {
  if (starts == nextStarts) {
    return;
  }
  starts = nextStarts;
  markOrigin();
}

void setMeasure(int value) {
  if (measure == value) {
    return;
  }
  measure = value;
  moveStep = measure == MEASURE_METRIC ? MOVE_STEP_1 : MOVE_STEP_IMP_1;
}

unsigned int getTimerLimit() {
  if (dupr == 0) {
    return 65535;
  }
  return min(long(65535), long(1000000 / (z.motorSteps * abs(dupr) / z.screwPitch)) - 1); // 1000000/Hz - 1
}

// Only used for async movement in ASYNC and A1 modes.
// Keep code in this method to absolute minimum to achieve high stepper speeds.
void IRAM_ATTR onAsyncTimer() {
  Axis* a = getAsyncAxis();
  if (!isOn || a->movingManually || (mode != MODE_ASYNC && mode != MODE_A1)) {
    return;
  } else if (dupr > 0 && a->pos < a->leftStop) {
    if (a->pos <= a->motorPos) {
      a->pos++;
    }
    a->motorPos++;
    a->posGlobal++;
  } else if (dupr < 0 && a->pos > a->rightStop) {
    if (a->pos >= a->motorPos + a->backlashSteps) {
      a->pos--;
    }
    a->motorPos--;
    a->posGlobal--;
  } else {
    return;
  }

  DLOW(a->step);
  a->stepStartUs = micros();
  delayMicroseconds(10);
  DHIGH(a->step);
}

void setModeFromTask(int value) {
  nextMode = value;
  nextModeFlag = true;
}

void setModeFromLoop(int value) {
  if (mode == value) {
    return;
  }
  if (isOn) {
    setIsOnFromLoop(false);
  }
  if (mode == MODE_THREAD) {
    setStarts(1);
  } else if (mode == MODE_ASYNC || mode == MODE_A1) {
    setAsyncTimerEnable(false);
  }
  mode = value;
  setupIndex = 0;
  if (mode == MODE_ASYNC || mode == MODE_A1) {
    if (!timerAttached) {
      timerAttached = true;
      timerAttachInterrupt(async_timer, &onAsyncTimer);
    }
    updateAsyncTimerSettings();
    setAsyncTimerEnable(true);
  }
}

void setTurnPasses(int value) {
  if (isOn) {
    beep();
  } else {
    turnPasses = value;
  }
}

void setConeRatio(float value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  nextConeRatio = value;
  nextConeRatioFlag = true;
}

void applyConeRatio() {
  if (nextConeRatio == coneRatio) {
    return;
  }
  coneRatio = nextConeRatio;
  markOrigin();
}

void reset() {
  z.nextLeftStopFlag = false;
  z.nextRightStopFlag = false;
  z.pos = 0;
  z.originPos = 0;
  z.posGlobal = 0;
  z.motorPos = 0;
  z.pendingPos = 0;
  z.disabled = false;
  x.nextLeftStopFlag = false;
  x.nextRightStopFlag = false;
  x.pos = 0;
  x.originPos = 0;
  x.posGlobal = 0;
  x.motorPos = 0;
  x.pendingPos = 0;
  x.disabled = false;
  a1.nextLeftStopFlag = false;
  a1.nextRightStopFlag = false;
  a1.pos = 0;
  a1.originPos = 0;
  a1.posGlobal = 0;
  a1.motorPos = 0;
  a1.pendingPos = 0;
  auxForward = true;

  // Reset spindle RPM display
  shownRpm = 0;
  spindleEncTimeDiffBulk = 0;
}

long normalizePitch(long pitch) {
  int scale = 1;
  if (measure == MEASURE_METRIC) {
    // Drop the 3rd and 4th precision point if any.
    scale = 100;
  } else if (measure == MEASURE_INCH) {
    // Always drop the 4th precision point in inch representation if any.
    scale = 254;
  }
  return round(pitch / scale) * scale;
}

void beep() {
  tone(BUZZ, 1000, 500);
}

void setIsOnFromTask(bool on) {
  nextIsOn = on;
  nextIsOnFlag = true;
}

void setIsOnFromLoop(bool on) {
  if (isOn && on) {
    return;
  }
  if (!on) {
    isOn = false;
    setupIndex = 0;
  }
  stepperEnable(&z, on);
  stepperEnable(&x, on);
  stepperEnable(&a1, on);
  markOrigin();
  if (on) {
    isOn = true;
    opDuprSign = dupr >= 0 ? 1 : -1;
    opDupr = dupr;
    opIndex = 0;
    opIndexAdvanceFlag = false;
    opSubIndex = 0;
    setupIndex = 0;
  }
}

// void buttonOffRelease() {
//   if (millis() - resetMillis > 3000) {
//     reset();
//     splashScreen = true;
//   }
// }

void setLeftStop(Axis* a, long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  a->nextLeftStop = value;
  a->nextLeftStopFlag = true;
}

void leaveStop(Axis* a, long oldStop) {
  if (mode == MODE_CONE) {
    // To avoid rushing to a far away position if standing on limit.
    markOrigin();
  } else if (mode == MODE_NORMAL && a == getPitchAxis() && a->pos == oldStop) {
    // Spindle is most likely out of sync with the stepper because
    // it was spinning while the lead screw was on the stop.
    spindlePosSync = spindleModulo(spindlePos - spindleFromPos(a, a->pos));
  }
}

void applyLeftStop(Axis* a) {
  // Accept left stop even if it's lower than pos.
  // Stop button press processing takes time during which motor could have moved.
  long oldStop = a->leftStop;
  a->leftStop = a->nextLeftStop;
  leaveStop(a, oldStop);
}

void setRightStop(Axis* a, long value) {
  // Can't apply changes right away since we might be in the middle of motion logic.
  a->nextRightStop = value;
  a->nextRightStopFlag = true;
}

void applyRightStop(Axis* a) {
  // Accept right stop even if it's higher than pos.
  // Stop button press processing takes time during which motor could have moved.
  long oldStop = a->rightStop;
  a->rightStop = a->nextRightStop;
  leaveStop(a, oldStop);
}

void buttonLeftStopPress(Axis* a) {
  setLeftStop(a, a->leftStop == LONG_MAX ? a->pos : LONG_MAX);
}

void buttonRightStopPress(Axis* a) {
  setRightStop(a, a->rightStop == LONG_MIN ? a->pos : LONG_MIN);
}

void buttonDisplayPress() {
  if (!showAngle && !showTacho) {
    showAngle = true;
  } else if (showAngle) {
    showAngle = false;
    showTacho = true;
  } else {
    showTacho = false;
  }
}

void buttonMoveStepPress() {
  if (measure == MEASURE_METRIC) {
    if (moveStep == MOVE_STEP_1) {
      moveStep = MOVE_STEP_2;
    } else if (moveStep == MOVE_STEP_2) {
      moveStep = MOVE_STEP_3;
    } else if (moveStep == MOVE_STEP_3) {
      moveStep = MOVE_STEP_4;  
    } else {
      moveStep = MOVE_STEP_1;
    }
  } else {
    if (moveStep == MOVE_STEP_IMP_1) {
      moveStep = MOVE_STEP_IMP_2;
    } else if (moveStep == MOVE_STEP_IMP_2) {
      moveStep = MOVE_STEP_IMP_3;
    } else {
      moveStep = MOVE_STEP_IMP_1;
    }
  }
}

void setDir(Axis* a, bool dir) {
  // Start slow if direction changed.
  if (a->direction != dir || !a->directionInitialized) {
    a->speed = a->speedStart;
    a->direction = dir;
    a->directionInitialized = true;
    DWRITE(a->dir, dir ^ a->invertStepper);
    delayMicroseconds(DIRECTION_SETUP_DELAY_US);
  }
}

// Moves the stepper so that the tool is located at the newPos.
bool stepToContinuous(Axis* a, long newPos) {
  return stepTo(a, newPos, true);
}

bool stepToFinal(Axis* a, long newPos) {
  return stepTo(a, newPos, false);
}

bool stepTo(Axis* a, long newPos, bool continuous) {
  if (xSemaphoreTake(a->mutex, 10) == pdTRUE) {
    a->continuous = continuous;
    if (newPos == a->pos) {
      a->pendingPos = 0;
    } else {
      a->pendingPos = newPos - a->motorPos - (newPos > a->pos ? 0 : a->backlashSteps);
    }
    xSemaphoreGive(a->mutex);
    return true;
  }
  return false;
}

// Calculates stepper position from spindle position.
long posFromSpindle(Axis* a, long s, bool respectStops) {
  long newPos = s * a->motorSteps / a->screwPitch / ENCODER_STEPS_FLOAT * dupr * starts;

  // Respect left/right stops.
  if (respectStops) {
    if (newPos < a->rightStop) {
      newPos = a->rightStop;
    } else if (newPos > a->leftStop) {
      newPos = a->leftStop;
    }
  }

  return newPos;
}

// Calculates spindle position from stepper position.
long spindleFromPos(Axis* a, long p) {
  return p * a->screwPitch * ENCODER_STEPS_FLOAT / a->motorSteps / (dupr * starts);
}

void stepperEnable(Axis* a, bool value) {
  if (!a->needsRest || !a->active) {
    return;
  }
  if (value) {
    a->stepperEnableCounter++;
    if (value == 1) {
      updateEnable(a);
    }
  } else if (a->stepperEnableCounter > 0) {
    a->stepperEnableCounter--;
    if (a->stepperEnableCounter == 0) {
      updateEnable(a);
    }
  }
}

void updateEnable(Axis* a) {
  if (!a->disabled && (!a->needsRest || a->stepperEnableCounter > 0)) {
    DHIGH(a->ena);
    // Stepper driver needs some time before it will react to pulses.
    DELAY(STEPPED_ENABLE_DELAY_MS);
  } else {
    DLOW(a->ena);
  }
}

void moveAxis(Axis* a) {
  // Most of the time a step isn't needed.

  if (a->pendingPos == 0) {
    if (a->speed > a->speedStart) {
      a->speed--;
    }
    return;
  }

  unsigned long nowUs = micros();
  float delayUs = 1000000.0 / a->speed;
  if (nowUs - a->stepStartUs < delayUs - 5) {
    // Not enough time has passed to issue this step.
    return;
  }

  if (xSemaphoreTake(a->mutex, 1) == pdTRUE) {

    if (a->pendingPos != 0) {
      bool dir = a->pendingPos > 0;
      setDir(a, dir);

      DLOW(a->step);
      int delta = dir ? 1 : -1;
      a->pendingPos -= delta;
      if (dir && a->motorPos >= a->pos) {
        a->pos++;
      } else if (!dir && a->motorPos <= (a->pos - a->backlashSteps)) {
        a->pos--;
      }
      a->motorPos += delta;
      a->posGlobal += delta;

      bool accelerate = a->continuous || a->pendingPos >= a->decelerateSteps || a->pendingPos <= -a->decelerateSteps;
      a->speed += (accelerate ? 1 : -1) * a->acceleration * delayUs / 1000000.0;
      if (a->speed > a->speedMax) {
        a->speed = a->speedMax;
      } else if (a->speed < a->speedStart) {
        a->speed = a->speedStart;
      }
      a->stepStartUs = nowUs;

      DHIGH(a->step);
    }
    xSemaphoreGive(a->mutex);
  }
}

void modeGearbox() {
  if (z.movingManually) {
    return;
  }
  z.speedMax = LONG_MAX;
  stepToContinuous(&z, posFromSpindle(&z, spindlePosAvg, true));
}

long spindleModulo(long value) {
  value = value % ENCODER_STEPS_INT;
  if (value < 0) {
    value += ENCODER_STEPS_INT;
  }
  return value;
}

long auxSafeDistance, startOffset;
void modeTurn(Axis* main, Axis* aux) {
  if (main->movingManually || aux->movingManually || turnPasses <= 0 ||
      main->leftStop == LONG_MAX || main->rightStop == LONG_MIN ||
      aux->leftStop == LONG_MAX || aux->rightStop == LONG_MIN ||
      dupr == 0 || (dupr * opDuprSign < 0) || starts < 1) {
    setIsOnFromLoop(false);
    return;
  }

  int springPasses = 0;
  if (mode == MODE_THREAD) {
    springPasses = threadSpringPasses;
    if (springPasses < 0) springPasses = 0;
    if (springPasses > 3) springPasses = 3; // 0-3 is plenty
  }

  // Variables below have to be re-calculated every time because origin can change
  // while TURN is running e.g. due to dupr change.
  long mainStartStop = opDuprSign > 0 ? main->rightStop : main->leftStop;
  long mainEndStop = opDuprSign > 0 ? main->leftStop : main->rightStop;
  long auxStartStop = auxForward ? aux->rightStop : aux->leftStop;
  long auxEndStop = auxForward ? aux->leftStop : aux->rightStop;

  int totalPasses = turnPasses + ((mode == MODE_THREAD) ? springPasses : 0);

  // opIndex 0 is only executed once, do setup calculations here.
  if (opIndex == 0) {
    auxSafeDistance = (auxForward ? -1 : 1) * SAFE_DISTANCE_DU * aux->motorSteps / aux->screwPitch;
    startOffset = starts == 1 ? 0 : round(ENCODER_STEPS_FLOAT / starts);

    // Move to right-bottom limit.
    main->speedMax = main->speedManualMove;
    aux->speedMax = aux->speedManualMove;
    long auxPos = auxStartStop;
    // Overstep by 1 so that "main" backlash is taken out before "opSubIndex == 1".
    long mainPos = mainStartStop + (opDuprSign > 0 ? -1 : 1);
    stepToFinal(main, mainPos);
    stepToFinal(aux, auxPos);
    if (main->pos == mainPos && aux->pos == auxPos) {
      stepToFinal(main, mainStartStop);
      opIndex = 1;
      opSubIndex = 0;
    }
  } else if (opIndex <= totalPasses * starts) {
    if (opIndexAdvanceFlag && (opIndex + starts) < totalPasses * starts) {
      opIndexAdvanceFlag = false;
      opIndex += starts;
    }

    long auxPos;
    long passNum = (long)ceil(opIndex / float(starts));

    if (mode == MODE_THREAD) {
        if (passNum > turnPasses) {
            // NEW: spring passes at final depth
            auxPos = auxEndStop;
        } else {
            // Progressive depth for threading
            float fraction = (turnPasses - passNum) / float(turnPasses);
            fraction = fraction * fraction;  // non-linear progression
            auxPos = auxEndStop - (auxEndStop - auxStartStop) * fraction;
        }
    } else {
        // Linear depth for regular turning/facing operations
        auxPos = auxEndStop - (auxEndStop - auxStartStop) / turnPasses * (turnPasses - passNum);
    }

    // Bringing X to starting position.
    if (opSubIndex == 0) {
      stepToFinal(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 1;
        spindlePosSync = spindleModulo(spindlePosGlobal - spindleFromPos(main, main->posGlobal) + startOffset * (opIndex - 1));
        return; // Instead of jumping to the next step, let spindlePosSync get to 0 first.
      }
    }
    // spindlePosSync counted down to 0, start thread from here.
    if (opSubIndex == 1) {
      markOrigin();
      main->speedMax = LONG_MAX;
      opSubIndex = 2;
      // markOrigin() changed Start/EndStop values, re-calculate them.
      return;
    }
    // Doing the pass cut.
    if (opSubIndex == 2) {
      // In case we were pushed to the next opIndex before finishing the current one.
      stepToFinal(aux, auxPos);
      stepToContinuous(main, posFromSpindle(main, spindlePos, true));
      if (main->pos == mainEndStop) {
        opSubIndex = 3;
      }
    }
    // Retracting the tool
    if (opSubIndex == 3) {
      long auxPos = auxStartStop + auxSafeDistance;
      stepToFinal(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 4;
      }
    }
    // Returning to start of main.
    if (opSubIndex == 4) {
      main->speedMax = main->speedManualMove;
      // Overstep by 1 so that "main" backlash is taken out before "opSubIndex == 2".
      long mainPos = mainStartStop + (opDuprSign > 0 ? -1 : 1);
      stepToFinal(main, mainPos);
      if (main->pos == mainPos) {
        stepToFinal(main, mainStartStop);
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    // Move to right-bottom limit.
    main->speedMax = main->speedManualMove;
    long auxPos = auxStartStop;
    long mainPos = mainStartStop;
    stepToFinal(main, mainPos);
    stepToFinal(aux, auxPos);
    if (main->pos == mainPos && aux->pos == auxPos) {
      setIsOnFromLoop(false);
      beep();
    }
  }
}

void modeCone() {
  if (z.movingManually || x.movingManually || coneRatio == 0) {
    return;
  }

  float zToXRatio = -coneRatio / 2 / z.motorSteps * x.motorSteps / x.screwPitch * z.screwPitch * (auxForward ? 1 : -1);
  if (zToXRatio == 0) {
    return;
  }

  // TODO: calculate maximum speeds and accelerations to avoid potential desync.
  x.speedMax = LONG_MAX;
  z.speedMax = LONG_MAX;

  // Respect limits of both axis by translating them into limits on spindlePos value.
  long spindle = spindlePosAvg;
  long spindleMin = LONG_MIN;
  long spindleMax = LONG_MAX;
  if (z.leftStop != LONG_MAX) {
    (dupr > 0 ? spindleMax : spindleMin) = spindleFromPos(&z, z.leftStop);
  }
  if (z.rightStop != LONG_MIN) {
    (dupr > 0 ? spindleMin: spindleMax) = spindleFromPos(&z, z.rightStop);
  }
  if (x.leftStop != LONG_MAX) {
    long lim = spindleFromPos(&z, round(x.leftStop / zToXRatio));
    if (zToXRatio < 0) {
      (dupr > 0 ? spindleMin: spindleMax) = lim;
    } else {
      (dupr > 0 ? spindleMax : spindleMin) = lim;
    }
  }
  if (x.rightStop != LONG_MIN) {
    long lim = spindleFromPos(&z, round(x.rightStop / zToXRatio));
    if (zToXRatio < 0) {
      (dupr > 0 ? spindleMax : spindleMin) = lim;
    } else {
      (dupr > 0 ? spindleMin: spindleMax) = lim;
    }
  }
  if (spindle > spindleMax) {
    spindle = spindleMax;
  } else if (spindle < spindleMin) {
    spindle = spindleMin;
  }

  stepToContinuous(&z, posFromSpindle(&z, spindle, true));
  stepToContinuous(&x, round(z.pos * zToXRatio));
}

void modeCut() {
  if (x.movingManually || turnPasses <= 0 || x.leftStop == LONG_MAX || x.rightStop == LONG_MIN || dupr == 0 || dupr * opDuprSign < 0) {
    setIsOnFromLoop(false);
    return;
  }

  long startStop = opDuprSign > 0 ? x.rightStop : x.leftStop;
  long endStop = opDuprSign > 0 ? x.leftStop : x.rightStop;

  if (opIndex == 0) {
    // Move to back limit.
    x.speedMax = x.speedManualMove;
    long xPos = startStop;
    stepToFinal(&x, xPos);
    if (x.pos == xPos) {
      opIndex = 1;
      opSubIndex = 0;
    }
  } else if (opIndex <= turnPasses) {
    // Set spindlePos and x.pos in sync.
    if (opSubIndex == 0) {
      spindlePosAvg = spindlePos = spindleFromPos(&x, x.pos);
      opSubIndex = 1;
    }
    // Doing the pass cut.
    if (opSubIndex == 1) {
      x.speedMax = LONG_MAX;
      long endPos = endStop - (endStop - startStop) / turnPasses * (turnPasses - opIndex);
      long xPos = posFromSpindle(&x, spindlePosAvg, true);
      if (dupr > 0 && xPos > endPos) xPos = endPos;
      else if (dupr < 0 && xPos < endPos) xPos = endPos;
      stepToContinuous(&x, xPos);
      if (x.pos == endPos) {
        opSubIndex = 2;
      }
    }
    // Returning to start.
    if (opSubIndex == 2) {
      x.speedMax = x.speedManualMove;
      stepToFinal(&x, startStop);
      if (x.pos == startStop) {
        opSubIndex = 0;
        opIndex++;
      }
    }
  } else {
    setIsOnFromLoop(false);
    beep();
  }
}

void modeEllipse(Axis* main, Axis* aux) {
  if (main->movingManually || aux->movingManually || turnPasses <= 0 ||
      main->leftStop == LONG_MAX || main->rightStop == LONG_MIN ||
      aux->leftStop == LONG_MAX || aux->rightStop == LONG_MIN ||
      main->leftStop == main->rightStop ||
      aux->leftStop == aux->rightStop ||
      dupr == 0 || dupr != opDupr) {
    setIsOnFromLoop(false);
    return;
  }

  // Start from left or right depending on the pitch.
  long mainStartStop = opDuprSign > 0 ? main->rightStop : main->leftStop;
  long mainEndStop = opDuprSign > 0 ? main->leftStop : main->rightStop;
  long auxStartStop = aux->rightStop;
  long auxEndStop = aux->leftStop;

  main->speedMax = main->speedManualMove;
  aux->speedMax = aux->speedManualMove;

  if (opIndex == 0) {
    opIndex = 1;
    opSubIndex = 0;
    spindlePos = 0;
    spindlePosAvg = 0;
  } else if (opIndex <= turnPasses) {
    float pass0to1 = opIndex / float(turnPasses);
    long mainDelta = round(pass0to1 * (mainEndStop - mainStartStop));
    long auxDelta = round(pass0to1 * (auxEndStop - auxStartStop));
    long spindleDelta = spindleFromPos(main, mainDelta);

    // Move to starting position.
    if (opSubIndex == 0) {
      long auxPos = auxStartStop;
      stepToFinal(aux, auxPos);
      if (aux->pos == auxPos) {
        opSubIndex = 1;
      }
    } else if (opSubIndex == 1) {
      long mainPos = mainEndStop - mainDelta;
      stepToFinal(main, mainPos);
      if (main->pos == mainPos) {
        opSubIndex = 2;
        spindlePos = 0;
        spindlePosAvg = 0;
      }
    } else if (opSubIndex == 2) {
      float progress0to1 = 0;
      if ((spindleDelta > 0 && spindlePosAvg >= spindleDelta) || (spindleDelta < 0 && spindlePosAvg <= spindleDelta)) {
        progress0to1 = 1;
      } else {
        progress0to1 = spindlePosAvg / float(spindleDelta);
      }
      float mainCoeff = auxForward ? cos(HALF_PI * (3 + progress0to1)) : (1 + sin(HALF_PI * (progress0to1 - 1)));
      long mainPos = mainEndStop - mainDelta + round(mainDelta * mainCoeff);
      float auxCoeff = auxForward ? (1 + sin(HALF_PI * (3 + progress0to1))) : sin(HALF_PI * progress0to1);
      long auxPos = auxStartStop + round(auxDelta * auxCoeff);
      stepToContinuous(main, mainPos);
      stepToContinuous(aux, auxPos);
      if (progress0to1 == 1 && main->pos == mainPos && aux->pos == auxPos) {
        opIndex++;
        opSubIndex = 0;
      }
    }
  } else if (opIndex == turnPasses + 1) {
    stepToFinal(aux, auxStartStop);
    if (aux->pos == auxStartStop) {
      setIsOnFromLoop(false);
      beep();
    }
  }
}

long mmOrInchToAbsolutePos(Axis* a, float mmOrInch) {
  long scaleToDu = measure == MEASURE_METRIC ? 10000 : 254000;
  long part1 = a->gcodeRelativePos;
  long part2 = round(mmOrInch * scaleToDu / a->screwPitch * a->motorSteps);
  return part1 + part2;
}

String getValueString(const String& command, char letter) {
  int index = command.indexOf(letter);
  if (index == -1) {
    return "";
  }
  String valueString;
  for (int i = index + 1; i < command.length(); i++) {
    char c = command.charAt(i);
    if (isDigit(c) || c == '.' || c == '-') {
      valueString += c;
    } else {
      break;
    }
  }
  return valueString;
}

float getFloat(const String& command, char letter) {
  return getValueString(command, letter).toFloat();
}

int getInt(const String& command, char letter) {
  return getValueString(command, letter).toInt();
}

void updateAxisSpeeds(long diffX, long diffZ, long diffA1, bool isRapid = false) {
  if (diffX == 0 && diffZ == 0 && diffA1 == 0) return;
  long absX = abs(diffX);
  long absZ = abs(diffZ);
  long absC = abs(diffA1);
  
  // Calculate speed for each axis independently
  float stepsPerSecX, stepsPerSecZ, stepsPerSecA1;
  
  if (isRapid) {
    // G0 rapid move - use per-axis rapid feedrates
    stepsPerSecX = gcodeRapidFeedDuPerSecX * x.motorSteps / x.screwPitch;
    float minStepsPerSecX = GCODE_FEED_MIN_DU_SEC * x.motorSteps / x.screwPitch;
    if (stepsPerSecX > x.speedManualMove) stepsPerSecX = x.speedManualMove;
    else if (stepsPerSecX < minStepsPerSecX) stepsPerSecX = minStepsPerSecX;
    
    stepsPerSecZ = gcodeRapidFeedDuPerSecZ * z.motorSteps / z.screwPitch;
    float minStepsPerSecZ = GCODE_FEED_MIN_DU_SEC * z.motorSteps / z.screwPitch;
    if (stepsPerSecZ > z.speedManualMove) stepsPerSecZ = z.speedManualMove;
    else if (stepsPerSecZ < minStepsPerSecZ) stepsPerSecZ = minStepsPerSecZ;
    
    stepsPerSecA1 = gcodeRapidFeedDuPerSecA1 * a1.motorSteps / a1.screwPitch;
    float minStepsPerSecA1 = GCODE_FEED_MIN_DU_SEC * a1.motorSteps / a1.screwPitch;
    if (stepsPerSecA1 > a1.speedManualMove) stepsPerSecA1 = a1.speedManualMove;
    else if (stepsPerSecA1 < minStepsPerSecA1) stepsPerSecA1 = minStepsPerSecA1;
  } else {
    // G1 feed move - use programmed feedrate (same for all axes in coordinated move)
    stepsPerSecX = gcodeFeedDuPerSec * x.motorSteps / x.screwPitch;
    float minStepsPerSecX = GCODE_FEED_MIN_DU_SEC * x.motorSteps / x.screwPitch;
    if (stepsPerSecX > x.speedManualMove) stepsPerSecX = x.speedManualMove;
    else if (stepsPerSecX < minStepsPerSecX) stepsPerSecX = minStepsPerSecX;
    
    stepsPerSecZ = gcodeFeedDuPerSec * z.motorSteps / z.screwPitch;
    float minStepsPerSecZ = GCODE_FEED_MIN_DU_SEC * z.motorSteps / z.screwPitch;
    if (stepsPerSecZ > z.speedManualMove) stepsPerSecZ = z.speedManualMove;
    else if (stepsPerSecZ < minStepsPerSecZ) stepsPerSecZ = minStepsPerSecZ;
    
    stepsPerSecA1 = gcodeFeedDuPerSec * a1.motorSteps / a1.screwPitch;
    float minStepsPerSecA1 = GCODE_FEED_MIN_DU_SEC * a1.motorSteps / a1.screwPitch;
    if (stepsPerSecA1 > a1.speedManualMove) stepsPerSecA1 = a1.speedManualMove;
    else if (stepsPerSecA1 < minStepsPerSecA1) stepsPerSecA1 = minStepsPerSecA1;
  }
  
  float secX = absX / stepsPerSecX;
  float secZ = absZ / stepsPerSecZ;
  float secA1 = absC / stepsPerSecA1;
  float sec = ACTIVE_A1 ? max(max(secX, secZ), secA1) : max(secX, secZ);
  if (sec > 0) {
    x.speedMax = (absX > 0) ? min(stepsPerSecX, absX / sec) : stepsPerSecX;
    z.speedMax = (absZ > 0) ? min(stepsPerSecZ, absZ / sec) : stepsPerSecZ;
    a1.speedMax = (absC > 0) ? min(stepsPerSecA1, absC / sec) : stepsPerSecA1;
  } else {
    // No movement or zero time - use feedrate-limited speed
    x.speedMax = stepsPerSecX;
    z.speedMax = stepsPerSecZ;
    a1.speedMax = stepsPerSecA1;
  }
}

void setFeedRate(const String& command) {
  // Don't parse F parameter for M-codes (like M220 F500)
  if (command.charAt(0) == 'M') {
    return;
  }
  
  if (command.indexOf('F') >= 0) {
    float feedRate = getFloat(command, 'F');
    if (feedRate > 0) {
      gcodeFeedDuPerSec = round(feedRate * (measure == MEASURE_METRIC ? 10000 : 254000) / 60.0);
    }
  }
}

void setSpindleSpeed(const String& command) {
  // Only process if S is the first parameter
  String trimmed = command;
  trimmed.trim();
  if (!trimmed.startsWith("S")) return;
  
  float rpm = getFloat(command, 'S');
  if (rpm >= 0) {
    long newRPM = round(rpm);
    if (spindleRPM != newRPM) {
      spindleRPM = newRPM;
      Serial.print("Spindle RPM set to ");
      Serial.print(spindleRPM);
      Serial.println(" (not implemented)");
    } else {
      spindleRPM = newRPM;
    }
  }
}

/**
 * Check for stop command from MPG pendant (Serial1) or main serial
 * Call this inside any blocking loop that needs to be interruptible
 * 
 * @param axis - Optional axis to clean up if stopping (can be nullptr)
 * @return true if stop was requested and handled, false otherwise
 */
bool checkForStopCommand(Axis* axis = nullptr) {
    // Check the global flag first (set by interrupt, other task, etc)

    while (Serial1.available() > 0) {
        char c = Serial1.peek();
        if (c == '!') {
            Serial1.readStringUntil('\n');
            stopRequested = true;
            Serial1.println("OK:HOLD");
            break;
        } else if (c == '?') {
              Serial1.readStringUntil('\n');
              printMPGStatusResponse();  // Just respond, no recursion risk
        } else if (c == '\n' || c == '\r') {
            Serial1.read();  // Discard stray newlines
        } else {
            break;  // Leave other commands for later
        }
    }

    bool stopDetected = stopRequested;
    
    if (stopDetected) {
        Serial.println("Stop command received");
        
        if (axis != nullptr) {
            axis->continuous = false;
            if (xSemaphoreTake(axis->mutex, 100) == pdTRUE) {
                axis->pendingPos = 0;
                xSemaphoreGive(axis->mutex);
            }
            axis->movingManually = false;
            axis->speedMax = LONG_MAX;
            stepperEnable(axis, false);
        }
        
        setIsOnFromTask(false);
        mpgEnabled = false;
        
        return true;
    }
    
    return false;
}

void gcodeWaitEpsilon(int epsilon) {

  while (abs(x.pendingPos) > epsilon ||
         abs(z.pendingPos) > epsilon ||
         abs(a1.pendingPos) > epsilon ||
         (SPINDLE_PAUSES_GCODE && getApproxRpm() < GCODE_MIN_RPM)) {

          checkForStopCommand();

    taskYIELD();
  }
}

void gcodeWaitNear() {
  gcodeWaitEpsilon(GCODE_WAIT_EPSILON_STEPS);
}

void gcodeWaitStop() {
  gcodeWaitEpsilon(0);
}

// Rapid positioning / linear interpolation.
void G00_01(const String& command, bool isRapid = false) {
  long xStart = x.pos;
  long zStart = z.pos;
  long a1Start = a1.pos;
  long xEnd = command.indexOf(x.name) >= 0 ? mmOrInchToAbsolutePos(&x, getFloat(command, x.name)) : xStart;
  long zEnd = command.indexOf(z.name) >= 0 ? mmOrInchToAbsolutePos(&z, getFloat(command, z.name)) : zStart;
  long a1End = command.indexOf(a1.name) >= 0 ? mmOrInchToAbsolutePos(&a1, getFloat(command, a1.name)) : a1Start;
  long xDiff = xEnd - xStart;
  long zDiff = zEnd - zStart;
  long a1Diff = a1End - a1Start;
  updateAxisSpeeds(xDiff, zDiff, a1Diff, isRapid);
  float precision = isRapid ? RAPID_LINEAR_INTERPOLATION_PRECISION : LINEAR_INTERPOLATION_PRECISION;
  long chunks = round(max(max(abs(xDiff), abs(zDiff)), abs(a1Diff)) * precision);
  for (long i = 0; i < chunks; i++) {
    if (!isOn) return;
    float scale = i / float(chunks);
    stepToContinuous(&x, xStart + xDiff * scale);
    stepToContinuous(&z, zStart + zDiff * scale);
    if (ACTIVE_A1) stepToContinuous(&a1, a1Start + a1Diff * scale);
    gcodeWaitNear();
  }
  // Changed: use stepToContinuous instead of stepToFinal
  stepToContinuous(&x, xEnd);
  stepToContinuous(&z, zEnd);
  if (ACTIVE_A1) stepToContinuous(&a1, a1End);
  gcodeWaitStop();
}

// G4 Dwell command - pauses execution for specified time
// Format: G4 P[milliseconds] or G4 S[seconds]
// Examples:
//   G4 P500    - Dwell for 500 milliseconds
//   G4 S2      - Dwell for 2 seconds
//   G4 P1000   - Dwell for 1 second (1000ms)
void G04(const String& command) {
  unsigned long dwellMs = 0;
  
  // Check for P parameter (milliseconds)
  if (command.indexOf('P') >= 0) {
    float pValue = getFloat(command, 'P');
    dwellMs = (unsigned long)pValue;
  }
  // Check for S parameter (seconds) - convert to milliseconds
  else if (command.indexOf('S') >= 0) {
    float sValue = getFloat(command, 'S');
    dwellMs = (unsigned long)(sValue * 1000);
  }
  
  // If no valid parameter found, default to 0 (no dwell)
  if (dwellMs == 0) {
    return;
  }
  
  // Ensure all axes have stopped moving before dwelling
  gcodeWaitStop();
  
  // Perform the dwell
  // Use taskYIELD() in loop to allow other tasks to run during dwell
  unsigned long startTime = millis();
  while (millis() - startTime < dwellMs && isOn) {
    taskYIELD();
    // Check if we need to stop (e.g., emergency stop or user intervention)
    if (!isOn) {
      break;
    }
  }
}

bool handleGcode(const String& command) {
  int op = getInt(command, 'G');
  if (op == 0 || op == 1) { // 0 also covers X and Z commands without G.
    if (!isOn) {
      Serial.println("error: motion not allowed when stopped");
      return false;
    }
    if (command.indexOf('G') >= 0) { //if theres a G0 update
        gcodeMotionMode = op;  // Update: 0 for G0, 1 for G1
    } //else moe at the same rate as before

    // Use modal state to determine if rapid or feed
    G00_01(command, gcodeMotionMode == 0);
  } else if (op == 4) {      
    G04(command);  // dwell
  } else if (op == 10) {
      if (!handleG10(command)) {
          Serial.println("error: invalid tool number");
          return false;
      }
      Serial.println("Tool set successfully");
      return true;
  } else if (op == 28) {
      handleG28(command);
      return true;
  } else if (op == 33) {
    return handleG33(command);
  } else if (op == 20 || op == 21) {
    setMeasure(op == 20 ? MEASURE_INCH : MEASURE_METRIC);
  } else if (op == 90 || op == 91) {
    gcodeAbsolutePositioning = op == 90;
  } else if (op == 92) { // G92 - Set position
    // G92 X0 Z0 - Sets X and Z axis to 0 at current position
    if (handleG92(command)) {
      Serial.println("Position set");
      return true;
    }
    return false;
  } else if (op == 94) {
    /* no-op feed per minute */
  } else if (op == 18) {
    /* no-op ZX plane selection */
  } else {
    Serial.print("error: unsupported command ");
    Serial.println(command);
    return false;
  }
  return true;
}

bool handleMcode(const String& command) {
  int op = getInt(command, 'M');
  if (op == 0 || op == 1) {

    setIsOnFromTask(false);   // sets nextIsOn = false, nextIsOnFlag = true
    nextIsOn = false;         // defensive clear just in case
    isOn = false;
    
    while (!nextIsOn && emergencyStop == ESTOP_NONE) {
      if (Serial.available() > 0) {
        char c = Serial.peek();   // look, don't eat

        // Handle only real-time control characters
        if (c == '~') { 
          Serial.read(); 
          nextIsOn = true; 
        } else if (c == '?') {
          Serial.read();
          printStatusResponse();
        } else if (c == '!') {
          Serial.read();
          setIsOnFromTask(false); // ensure everything stops
          //exit out of loop and return false to indicate stop
          return false;

        } else {
          // Leave all other bytes in the buffer — do NOT Serial.read() them
        }
      }
      taskYIELD();
    }
    
    isOn = true;
    nextIsOnFlag = false;
    nextIsOn = false;

    return true;
  } else if (op == 2 || op == 30) {
    setIsOnFromTask(false);
  } else if (op == 3) {
    // M3 - Spindle on clockwise
    spindleDirection = 1;
    Serial.print("Spindle CW");
    if (spindleRPM > 0) {
      Serial.print(" at ");
      Serial.print(spindleRPM);
      Serial.print(" RPM");
    }
    Serial.println(" (not implemented)");
  } else if (op == 4) {
    // M4 - Spindle on counter-clockwise
    spindleDirection = -1;
    Serial.print("Spindle CCW");
    if (spindleRPM > 0) {
      Serial.print(" at ");
      Serial.print(spindleRPM);
      Serial.print(" RPM");
    }
    Serial.println(" (not implemented)");
  } else if (op == 5) {
    // M5 - Spindle stop
    spindleDirection = 0;
    Serial.println("Spindle stop (not implemented)");
  } else if (op == 17) {
    if (handleM17(command)) {
      Serial.println("Motors enabled");
      return true;
    }
    return false;
  } else if (op == 18 || op == 84) { // M84 is alternative for M18
    if (handleM18(command)) {
      Serial.println("Motors disabled");
      return true;
    }
    return false;
  } else if (op == 119) {
      handleM119(command);
      return true;
  } else if (op == 220) {
      handleM220(command);
      return true;
  } else if (op == 206) {
      if (command.indexOf('S') >= 0) {
          handleM206Save(command);
          return true;
      } else if (command.indexOf('R') >= 0) {
          handleM206Report(command);
          return true;
      } else {
          handleM206(command);
          return true;
      }
  } else if (op == 500) {
    if (saveToPrefs()) {
      Serial.println("Settings saved");
    } else {
      Serial.println("No changes to save");
    }
    return true;
  } else if (op == 700) {
    setModeFromTask(MODE_NORMAL);
    return true;
  } else if (op == 905) {
      if (handleM905(command)) {
        Serial.println("Backlash values updated");
        return true;
      }
      return false;
  } else if (op == 999) { 
    Serial.println("Restarting controller...");
    delay(100);  // Let the message send
    ESP.restart();
    return true;
  } else {
    setIsOnFromTask(false);
    Serial.print("error: unsupported command ");
    Serial.println(command);
    return false;
  }
  return true;
}

// ============================================
// HOMING FUNCTIONS
// ============================================

// Check if X home sensor is triggered
bool isHomeSensorTriggered() {
  return digitalRead(X_HOME_SENSOR_PIN) == LOW;
}

// M119 - Report endstop/sensor status
bool handleM119(const String& command) {
  Serial.print("Home Sensor: ");
  Serial.println(isHomeSensorTriggered() ? "TRIGGERED" : "open");
  return true;
}

// M206 - X-axis home calibration routine
// Run this after zeroing X with your edge finder
bool handleM206(const String& command) {
  // Count how many axes are specified
  int axisCount = 0;
  bool hasX = command.indexOf('X') >= 0;
  bool hasY = command.indexOf('Y') >= 0;
  bool hasZ = command.indexOf('Z') >= 0;
  
  if (hasX) axisCount++;
  if (hasY) axisCount++;
  if (hasZ) axisCount++;
  
  // Only allow one axis at a time
  if (axisCount > 1) {
    Serial.println("Error: M206 can only calibrate one axis at a time");
    Serial.println("Usage: M206 X, M206 Y, M206 Z, or M206 X-43 (manual set)");
    return false;
  }
  
  if (axisCount == 0) {
    Serial.println("Error: M206 requires an axis parameter (X, Y, or Z)");
    Serial.println("Usage: M206 X, M206 Y, M206 Z, or M206 X-43 (manual set)");
    return false;
  }
  
  // Determine which axis to calibrate
  Axis* axis = nullptr;
  char axisName = 0;
  int sensorPin = 0;
  long maxTravel = 0;
  long fastSpeed = 0;
  long slowSpeed = 0;
  long backoff = 0;
  float* calibratedPos = nullptr;
  bool homeDirectionInvert = false;
  
  if (hasX) {
    axis = &x;
    axisName = 'X';
    sensorPin = X_HOME_SENSOR_PIN;
    maxTravel = X_HOME_MAX_TRAVEL;
    fastSpeed = X_HOME_FAST_SPEED;
    slowSpeed = X_HOME_SLOW_SPEED;
    backoff = X_HOME_BACKOFF;
    calibratedPos = &x_home_position_calibrated;
    homeDirectionInvert = X_HOME_DIRECTION_INVERT;
  } else if (hasY) {
    if (!ACTIVE_A1) {
      Serial.println("Error: Y-axis (A1) not active");
      return false;
    }
    axis = &a1;
    axisName = 'Y';
    sensorPin = X_HOME_SENSOR_PIN;
    maxTravel = Y_HOME_MAX_TRAVEL;
    fastSpeed = Y_HOME_FAST_SPEED;
    slowSpeed = Y_HOME_SLOW_SPEED;
    backoff = Y_HOME_BACKOFF;
    calibratedPos = &y_home_position_calibrated;
    homeDirectionInvert = Y_HOME_DIRECTION_INVERT;
  } else if (hasZ) {
    axis = &z;
    axisName = 'Z';
    sensorPin = X_HOME_SENSOR_PIN;
    maxTravel = Z_HOME_MAX_TRAVEL;
    fastSpeed = Z_HOME_FAST_SPEED;
    slowSpeed = Z_HOME_SLOW_SPEED;
    backoff = Z_HOME_BACKOFF;
    calibratedPos = &z_home_position_calibrated;
    homeDirectionInvert = Z_HOME_DIRECTION_INVERT;
  }
  
  // Auto-calibration mode
  Serial.print("Starting ");
  Serial.print(axisName);
  Serial.println("-axis home calibration...");
  
  axis->movingManually = true;
  axis->speedMax = LONG_MAX;
  stepperEnable(axis, true);
  
  // Phase 1: Fast approach toward sensor
  Serial.println("Phase 1: Fast approach...");
  
  long maxTravelSteps = duToSteps(axis, maxTravel * 10000);
  // Convert mm/min to steps/sec
  // fastSpeed is in mm/min
  // screwPitch is in deci-microns (10000 DU = 1mm)
  long fastSpeedSteps = (fastSpeed * 10000 * axis->motorSteps) / (axis->screwPitch * 60);
  
  axis->speedMax = fastSpeedSteps;
  axis->continuous = true;
  long targetPos = axis->pos + (homeDirectionInvert ? maxTravelSteps : -maxTravelSteps);
  
  stepToContinuous(axis, targetPos);
  
  unsigned long startTime = millis();
  while (digitalRead(sensorPin) != LOW) {
    DELAY(5);
    if (millis() - startTime > 60000) {
      axis->continuous = false;
      axis->movingManually = false;
      axis->speedMax = LONG_MAX;
      stepperEnable(axis, false);
      Serial.println("Error: Timeout waiting for sensor");
      return false;
    }
  }
  
  axis->continuous = false;
  if (xSemaphoreTake(axis->mutex, 100) == pdTRUE) {
    axis->pendingPos = 0;
    xSemaphoreGive(axis->mutex);
  }
  
  Serial.println("Sensor triggered!");
  
  // Phase 2: Back off
  Serial.println("Phase 2: Backing off...");
  
  long backoffSteps = duToSteps(axis, backoff * 10000);
  stepToContinuous(axis, axis->pos + (homeDirectionInvert ? -backoffSteps : backoffSteps));
  
  while (axis->pendingPos != 0) {
    DELAY(5);
  }
  
  DELAY(100);
  
  if (digitalRead(sensorPin) == LOW) {
    axis->movingManually = false;
    axis->speedMax = LONG_MAX;
    Serial.println("Error: Sensor still triggered after backoff");
    return false;
  }
  
  // Phase 3: Slow precise approach
  Serial.println("Phase 3: Slow precise approach...");
  
  long slowSpeedSteps = (slowSpeed * 10000 * axis->motorSteps) / (axis->screwPitch * 60);
  axis->speedMax = slowSpeedSteps;
  axis->continuous = true;
  stepToContinuous(axis, axis->pos + (homeDirectionInvert ? backoffSteps * 2 : -backoffSteps * 2));
  
  while (digitalRead(sensorPin) != LOW) {
    DELAY(1);
  }
  
  axis->continuous = false;
  if (xSemaphoreTake(axis->mutex, 100) == pdTRUE) {
    axis->pendingPos = 0;
    xSemaphoreGive(axis->mutex);
  }
  
  float homePosMM = getAxisPosDu(axis) / 10000.0;
  *calibratedPos = homePosMM;
  
  Serial.println("========================================");
  Serial.print(axisName);
  Serial.println("-AXIS HOME CALIBRATION COMPLETE");
  Serial.println("========================================");
  Serial.print("Home position: ");
  Serial.print(axisName);
  Serial.println(*calibratedPos, 3);
  Serial.println("");
  Serial.print("To save this value, send: M206 S");
  Serial.println(axisName);
  Serial.print("To recalibrate, send: M206 ");
  Serial.println(axisName);
  Serial.println("========================================");

  // Final backoff from sensor
  Serial.println("Backing off from sensor...");
  
  axis->speedMax = fastSpeedSteps;
  
  stepToContinuous(axis, axis->pos + (homeDirectionInvert ? -backoffSteps : backoffSteps));
  
  while (axis->pendingPos != 0) {
    DELAY(5);
  }
  
  axis->continuous = false;
  if (xSemaphoreTake(axis->mutex, 100) == pdTRUE) {
    axis->pendingPos = 0;
    xSemaphoreGive(axis->mutex);
  }
  
  DELAY(100);
  
  if (digitalRead(sensorPin) == LOW) {
    Serial.println("Warning: Sensor still triggered after backoff");
  }
  
  axis->movingManually = false;
  axis->speedMax = LONG_MAX;
  
  return true;
}


bool handleM206Save(const String& command) {
  // Count how many axes are specified
  int axisCount = 0;
  bool hasX = command.indexOf('X') >= 0;
  bool hasY = command.indexOf('Y') >= 0;
  bool hasZ = command.indexOf('Z') >= 0;
  
  if (hasX) axisCount++;
  if (hasY) axisCount++;
  if (hasZ) axisCount++;
  
  // Must specify exactly one axis
  if (axisCount != 1) {
    Serial.println("Error: M206 S requires exactly one axis parameter");
    Serial.println("Usage: M206 S X, or M206 S X-80.5");
    return false;
  }
  
  char axisName = 0;
  float* calibratedPos = nullptr;
  float* savedHomePos = nullptr;
  float* currentHomePos = nullptr;
  String prefKey;
  
  if (hasX) {
    axisName = 'X';
    calibratedPos = &x_home_position_calibrated;
    savedHomePos = &x_home_position_saved;
    currentHomePos = &x_home_position;
    prefKey = PREF_X_HOME_POSITION;
  } else if (hasY) {
    if (!ACTIVE_A1) {
      Serial.println("Error: Y-axis not active");
      return false;
    }
    axisName = 'Y';
    calibratedPos = &y_home_position_calibrated;
    savedHomePos = &y_home_position_saved;
    currentHomePos = &y_home_position;
    prefKey = PREF_Y_HOME_POSITION;
  } else if (hasZ) {
    axisName = 'Z';
    calibratedPos = &z_home_position_calibrated;
    savedHomePos = &z_home_position_saved;
    currentHomePos = &z_home_position;
    prefKey = PREF_Z_HOME_POSITION;
  }
  
  // Check if a value was provided
  String valueStr = getValueString(command, axisName);
  float valueToSave;
  
  if (valueStr.length() > 0) {
    // M206 S X-99 → Set directly
    valueToSave = valueStr.toFloat();
    *calibratedPos = valueToSave;
    *currentHomePos = valueToSave;
    
    Serial.print("Set ");
  } else {
    // M206 S X → Save calibrated value
    if (*calibratedPos == 0.0) {
      Serial.print("Error: Run M206 ");
      Serial.print(axisName);
      Serial.println(" calibration first");
      return false;
    }
    valueToSave = *calibratedPos;
    
    Serial.print("Saved ");
  }
  
  *savedHomePos = valueToSave;
  
  // Save to EEPROM
  Preferences pref;
  pref.begin(PREF_NAMESPACE);
  pref.putFloat(prefKey.c_str(), valueToSave);
  pref.end();
  
  Serial.print(axisName);
  Serial.print(" home position: ");
  Serial.println(valueToSave, 3);
  
  return true;
}

bool handleM206Report(const String& command) {
  // Read the actual values from EEPROM
  Preferences pref;
  pref.begin(PREF_NAMESPACE, true);  // true = read-only mode
  float eepromX = pref.getFloat(PREF_X_HOME_POSITION, -999.0);
  float eepromY = pref.getFloat(PREF_Y_HOME_POSITION, -999.0);
  float eepromZ = pref.getFloat(PREF_Z_HOME_POSITION, -999.0);
  pref.end();
  
  Serial.println("========================================");
  Serial.println("HOME POSITION STATUS");
  Serial.println("========================================");
  
  // X-axis
  Serial.println("X-AXIS:");
  Serial.print("  EEPROM:            X");
  Serial.println(eepromX, 4);
  Serial.print("  Runtime:           X");
  Serial.println(x_home_position, 4);
  Serial.print("  Saved:             X");
  Serial.println(x_home_position_saved, 4);
  Serial.print("  Last calibrated:   X");
  if (x_home_position_calibrated != 0.0) {
    Serial.println(x_home_position_calibrated, 4);
  } else {
    Serial.println("[not calibrated]");
  }
  Serial.println();
  
  // Y-axis
  if (ACTIVE_A1) {
    Serial.println("Y-AXIS:");
    Serial.print("  EEPROM:            Y");
    Serial.println(eepromY, 4);
    Serial.print("  Runtime:           Y");
    Serial.println(y_home_position, 4);
    Serial.print("  Saved:             Y");
    Serial.println(y_home_position_saved, 4);
    Serial.print("  Last calibrated:   Y");
    if (y_home_position_calibrated != 0.0) {
      Serial.println(y_home_position_calibrated, 4);
    } else {
      Serial.println("[not calibrated]");
    }
    Serial.println();
  }
  
  // Z-axis
  Serial.println("Z-AXIS:");
  Serial.print("  EEPROM:            Z");
  Serial.println(eepromZ, 4);
  Serial.print("  Runtime:           Z");
  Serial.println(z_home_position, 4);
  Serial.print("  Saved:             Z");
  Serial.println(z_home_position_saved, 4);
  Serial.print("  Last calibrated:   Z");
  if (z_home_position_calibrated != 0.0) {
    Serial.println(z_home_position_calibrated, 4);
  } else {
    Serial.println("[not calibrated]");
  }
  
  Serial.println("========================================");
  
  return true;
}

bool performAxisHome(Axis* axis, char axisName, int sensorPin, 
                     long maxTravel, long fastSpeed, long slowSpeed, 
                     long backoff, float homePosition, bool homeDirectionInvert) {
  Serial.print("Homing ");
  Serial.print(axisName);
  Serial.println(" axis...");
  
  axis->movingManually = true;
  axis->speedMax = LONG_MAX;
  stepperEnable(axis, true);
  
  // Fast approach
  long maxTravelSteps = duToSteps(axis, maxTravel * 10000);
  long fastSpeedSteps = (fastSpeed * 10000 * axis->motorSteps) / (axis->screwPitch * 60);
  
  axis->speedMax = fastSpeedSteps;
  axis->continuous = true;
  long targetPos = axis->pos + (homeDirectionInvert ? maxTravelSteps : -maxTravelSteps);
  
  stepToContinuous(axis, targetPos);
  
  unsigned long startTime = millis();
  while (digitalRead(sensorPin) != LOW) {
    if (checkForStopCommand(axis)) {
        Serial.println("Homing aborted during fast approach");
        return false;
    }
    DELAY(5);
    if (millis() - startTime > 60000) {
      axis->continuous = false;
      axis->movingManually = false;
      axis->speedMax = LONG_MAX;
      stepperEnable(axis, false);
      Serial.println("Error: Homing timeout");
      return false;
    }
  }
  
  axis->continuous = false;
  if (xSemaphoreTake(axis->mutex, 100) == pdTRUE) {
    axis->pendingPos = 0;
    xSemaphoreGive(axis->mutex);
  }
  
  // Back off
  long backoffSteps = duToSteps(axis, backoff * 10000);
  stepToContinuous(axis, axis->pos + (homeDirectionInvert ? -backoffSteps : backoffSteps));
  
  while (axis->pendingPos != 0) {
    if (checkForStopCommand(axis)) {
        Serial.println("Homing aborted during backoff");
        return false;
    }
    DELAY(5);
  }
  
  DELAY(100);
  
  // Slow approach
  long slowSpeedSteps = (slowSpeed * 10000 * axis->motorSteps) / (axis->screwPitch * 60);
  axis->speedMax = slowSpeedSteps;
  axis->continuous = true;
  stepToContinuous(axis, axis->pos + (homeDirectionInvert ? backoffSteps * 2 : -backoffSteps * 2));
  
  while (digitalRead(sensorPin) != LOW) {
    if (checkForStopCommand(axis)) {
        Serial.println("Homing aborted during slow approach");
        return false;
    }
    DELAY(5);
  }
  
  axis->continuous = false;
  if (xSemaphoreTake(axis->mutex, 100) == pdTRUE) {
    axis->pendingPos = 0;
    xSemaphoreGive(axis->mutex);
  }
  
  // Set position
  long homeSteps = round(homePosition * 10000 / axis->screwPitch * axis->motorSteps);
  axis->originPos = homeSteps - axis->pos;
  
  Serial.print(axisName);
  Serial.print(" axis homed to: ");
  Serial.print(axisName);
  Serial.println(homePosition, 2);
  

  //back off from sensor
  axis->speedMax = fastSpeedSteps;
  
  stepToContinuous(axis, axis->pos + (homeDirectionInvert ? -backoffSteps : backoffSteps));
  
  while (axis->pendingPos != 0) {
    DELAY(5);
  }
  
  axis->continuous = false;
  if (xSemaphoreTake(axis->mutex, 100) == pdTRUE) {
    axis->pendingPos = 0;
    xSemaphoreGive(axis->mutex);
  }
  
  DELAY(100);
  
  if (digitalRead(sensorPin) == LOW) {
    Serial.println("Warning: Sensor still triggered after final backoff");
  }

  axis->movingManually = false;
  axis->speedMax = LONG_MAX;

  return true;
}

// G28 - Home X axis (use sensor)
bool handleG28(const String& command) {
  // Count how many axes are specified
  int axisCount = 0;
  bool hasX = command.indexOf('X') >= 0;
  bool hasY = command.indexOf('Y') >= 0;
  bool hasZ = command.indexOf('Z') >= 0;
  
  if (hasX) axisCount++;
  if (hasY) axisCount++;
  if (hasZ) axisCount++;
  
  // Must specify exactly one axis
  if (axisCount > 1) {
    Serial.println("Error: G28 can only home one axis at a time");
    Serial.println("Usage: G28 X, G28 Y, or G28 Z");
    return false;
  }
  
  if (axisCount == 0) {
    Serial.println("Error: G28 requires an axis parameter");
    Serial.println("Usage: G28 X, G28 Y, or G28 Z");
    return false;
  }
  
  if (hasY && !ACTIVE_A1) {
    Serial.println("Error: Y-axis (A1) not active");
    return false;
  }
  
  // Home the requested axis
  if (hasX) {
    return performAxisHome(&x, 'X', X_HOME_SENSOR_PIN,
                          X_HOME_MAX_TRAVEL, X_HOME_FAST_SPEED,
                          X_HOME_SLOW_SPEED, X_HOME_BACKOFF,
                          x_home_position,  X_HOME_DIRECTION_INVERT);
  } else if (hasY) {
    return performAxisHome(&a1, 'Y', X_HOME_SENSOR_PIN,
                          Y_HOME_MAX_TRAVEL, Y_HOME_FAST_SPEED,
                          Y_HOME_SLOW_SPEED, Y_HOME_BACKOFF,
                          y_home_position, Y_HOME_DIRECTION_INVERT);
  } else if (hasZ) {
    return performAxisHome(&z, 'Z', X_HOME_SENSOR_PIN,
                          Z_HOME_MAX_TRAVEL, Z_HOME_FAST_SPEED,
                          Z_HOME_SLOW_SPEED, Z_HOME_BACKOFF,
                          z_home_position, Z_HOME_DIRECTION_INVERT);
  }
  
  return false;
}


// M220 - Set rapid feedrate (G0) in mm/min or in/min
// M220 → Report current rapid feed rates
// M220 F500 → Set all axes to 500 mm/min
// M220 X500 Z1000 → Set specific axes to different rates
bool handleM220(const String& command) {

  bool hasF = command.indexOf('F') >= 0;
  bool hasZ = command.indexOf('Z') >= 0;
  bool hasX = command.indexOf('X') >= 0;
  bool hasY = command.indexOf('Y') >= 0;
  
  // No parameters → Report current values
  if (!hasF && !hasZ && !hasX && !hasY) {
    Serial.println("=== Rapid Feed Rates (mm/min) ===");
    float zRate = gcodeRapidFeedDuPerSecZ * 60.0 / (measure == MEASURE_METRIC ? 10000 : 254000);
    float xRate = gcodeRapidFeedDuPerSecX * 60.0 / (measure == MEASURE_METRIC ? 10000 : 254000);
    float yRate = gcodeRapidFeedDuPerSecA1 * 60.0 / (measure == MEASURE_METRIC ? 10000 : 254000);
    
    Serial.print("Z: "); Serial.println(zRate, 1);
    Serial.print("X: "); Serial.println(xRate, 1);
    if (ACTIVE_A1) {
      Serial.print("Y: "); Serial.println(yRate, 1);
    }
    return true;
  }
  
  bool changed = false;
  long scaleFactor = measure == MEASURE_METRIC ? 10000 : 254000;
  
  // F parameter → Set all axes
  if (hasF) {
    float feedRate = getFloat(command, 'F');
    if (feedRate > 0) {
      long duPerSec = round(feedRate * scaleFactor / 60.0);
      gcodeRapidFeedDuPerSecZ = duPerSec;
      gcodeRapidFeedDuPerSecX = duPerSec;
      gcodeRapidFeedDuPerSecA1 = duPerSec;
      
      Serial.print("All axes rapid feed set to: ");
      Serial.print(feedRate, 1);
      Serial.println(" mm/min");
      changed = true;
    }
  }
  
  // Individual axis settings
  if (hasZ) {
    float zRate = getFloat(command, 'Z');
    if (zRate > 0) {
      gcodeRapidFeedDuPerSecZ = round(zRate * scaleFactor / 60.0);
      Serial.print("Z rapid feed: ");
      Serial.print(zRate, 1);
      Serial.println(" mm/min");
      changed = true;
    }
  }
  
  if (hasX) {
    float xRate = getFloat(command, 'X');
    if (xRate > 0) {
      gcodeRapidFeedDuPerSecX = round(xRate * scaleFactor / 60.0);
      Serial.print("X rapid feed: ");
      Serial.print(xRate, 1);
      Serial.println(" mm/min");
      changed = true;
    }
  }
  
  if (hasY) {
    if (!ACTIVE_A1) {
      Serial.println("Error: Y-axis not active");
      return false;
    }
    float yRate = getFloat(command, 'Y');
    if (yRate > 0) {
      gcodeRapidFeedDuPerSecA1 = round(yRate * scaleFactor / 60.0);
      Serial.print("Y rapid feed: ");
      Serial.print(yRate, 1);
      Serial.println(" mm/min");
      changed = true;
    }
  }
  
  return changed;
}

bool handleM17(const String& command) {
  bool changed = false;
  
  // Check if specific axes are mentioned
  if (command.indexOf(z.name) >= 0 || command.length() <= 3) {
    z.disabled = false;
    updateEnable(&z);
    changed = true;
  }
  
  if (command.indexOf(x.name) >= 0 || command.length() <= 3) {
    x.disabled = false;
    updateEnable(&x);
    changed = true;
  }
  
  if (ACTIVE_A1 && (command.indexOf(a1.name) >= 0 || command.length() <= 3)) {
    a1.disabled = false;
    updateEnable(&a1);
    changed = true;
  }
  
  return changed;
}

bool handleM18(const String& command) {
  bool changed = false;
  
  // Check if specific axes are mentioned
  if (command.indexOf(z.name) >= 0 || command.length() <= 3) {
    z.disabled = true;
    updateEnable(&z);
    changed = true;
  }
  
  if (command.indexOf(x.name) >= 0 || command.length() <= 3) {
    x.disabled = true;
    updateEnable(&x);
    changed = true;
  }
  
  if (ACTIVE_A1 && (command.indexOf(a1.name) >= 0 || command.length() <= 3)) {
    a1.disabled = true;
    updateEnable(&a1);
    changed = true;
  }
  
  return changed;
}

bool handleM905(const String& command) {
  bool changed = false;
  
  if (command.indexOf(z.name) >= 0) {
    float zBacklashMm = getFloat(command, z.name);
    if (zBacklashMm >= 0) { // Ensure non-negative
      long zBacklashDu = round(zBacklashMm * 10000); // Convert mm to deci-microns
      z.backlashDu = zBacklashDu;
      z.backlashSteps = zBacklashDu * z.motorSteps / z.screwPitch;
      changed = true;
    } else {
      Serial.println("error: backlash must be non-negative");
      return false;
    }
  }
  
  if (command.indexOf(x.name) >= 0) {
    float xBacklashMm = getFloat(command, x.name);
    if (xBacklashMm >= 0) {
      long xBacklashDu = round(xBacklashMm * 10000); // Convert mm to deci-microns
      x.backlashDu = xBacklashDu;
      x.backlashSteps = xBacklashDu * x.motorSteps / x.screwPitch;
      changed = true;
    } else {
      Serial.println("error: backlash must be non-negative");
      return false;
    }
  }
  
  if (ACTIVE_A1 && command.indexOf(a1.name) >= 0) {
    float a1BacklashMm = getFloat(command, a1.name);
    if (a1BacklashMm >= 0) {
      long a1BacklashDu = round(a1BacklashMm * 10000); // Convert mm to deci-microns
      a1.backlashDu = a1BacklashDu;
      a1.backlashSteps = a1BacklashDu * a1.motorSteps / a1.screwPitch;
      changed = true;
    } else {
      Serial.println("error: backlash must be non-negative");
      return false;
    }
  }
  
  return changed;
}

void synchronizeSpindleForThreading(long zStartPos, long threadPitch) {
  // Set spindle position to match current Z position for clean thread start
  // This establishes the phase relationship between spindle and Z axis
  if (xSemaphoreTake(motionMutex, 100) == pdTRUE) {
    // Calculate what spindle position should be for current Z position
    long expectedSpindlePos = zStartPos * z.screwPitch * ENCODER_STEPS_FLOAT / (z.motorSteps * threadPitch);
    
    // Adjust spindle tracking to match
    spindlePos = expectedSpindlePos;
    spindlePosAvg = expectedSpindlePos;
    spindlePosSync = 0;
    
    xSemaphoreGive(motionMutex);
  }
}

void executeThreadingCutMove(long zStart, long zEnd, long xCutDepth, long threadPitch) {
  // Set up for synchronized motion - let spindle control speed
  z.speedMax = LONG_MAX;
  x.speedMax = LONG_MAX;
  
  // Position X at cutting depth and hold it there
  stepToFinal(&x, xCutDepth);
  gcodeWaitStop();
  
  // Follow spindle for Z motion until we reach the end
  while (isOn) {
    // Calculate target Z position based on current spindle position
    // Reading spindlePosAvg without mutex - it's atomic on 32-bit ESP32
    long targetZ = spindlePosAvg * z.motorSteps / z.screwPitch / ENCODER_STEPS_FLOAT * threadPitch;
    
    // Constrain to our threading range
    if (zEnd > zStart) {
      targetZ = constrain(targetZ, zStart, zEnd);
    } else {
      targetZ = constrain(targetZ, zEnd, zStart);
    }
    
    // Queue the synchronized move - main loop's moveAxis() will execute it
    stepToContinuous(&z, targetZ);
    stepToContinuous(&x, xCutDepth);  // Keep X at cutting depth
    
    // Check if we've reached the end
    if (targetZ == zEnd && abs(z.pendingPos) <= GCODE_WAIT_EPSILON_STEPS) {
      break;
    }
    
    taskYIELD();  // Let main loop process the queued moves
  }
  
  // Ensure we end exactly at target
  stepToFinal(&z, zEnd);
  gcodeWaitStop();
}

// G33 Threading command handler (New)
// Format: G33 Z[end] X[end] P[pitch] H[passes] Q[start_z] R[start_x]
// Parameters:
//   Z - End Z position
//   X - End X position
//   P - Thread pitch in mm
//   H - Number of passes (optional, default 3)
//   Q - Start Z position (optional, defaults to current position)
//   R - Start X position (optional, defaults to current position)
// Example: G33 Z20 X-4.188 P1.5 H4 Q0 R-5 - External M10x1.5 thread
// Example: G33 Z20 X-5.1 P1.5 H4 Q0 R-4.5 - Internal M10x1.5 thread
bool handleG33New(const String &command) {
  // Extract and validate parameters
  if (command.indexOf('Z') == -1 || command.indexOf('X') == -1 || command.indexOf('P') == -1) {
    Serial.println("error: G33 requires Z, X, and P parameters");
    return false;
  }
  
  long zStart = command.indexOf('Q') >= 0 ? mmOrInchToAbsolutePos(&z, getFloat(command, 'Q')) : z.pos;
  long xStart = command.indexOf('R') >= 0 ? mmOrInchToAbsolutePos(&x, getFloat(command, 'R')) : x.pos;
  long zEnd = mmOrInchToAbsolutePos(&z, getFloat(command, 'Z'));
  long xEnd = mmOrInchToAbsolutePos(&x, getFloat(command, 'X'));
  
  float pitchMm = getFloat(command, 'P');
  if (pitchMm <= 0) {
    Serial.println("error: Invalid pitch value");
    return false;
  }
  long threadPitch = round(pitchMm * 10000);
  
  int passes = command.indexOf('H') >= 0 ? getInt(command, 'H') : 3;
  if (passes <= 0 || passes > PASSES_MAX) {
    Serial.println("error: Invalid number of passes (1-" + String(PASSES_MAX) + ")");
    return false;
  }
  
  // Validate we're at start position
  long zTolerance = duToSteps(&z, 200); // 0.02mm tolerance  
  long xTolerance = duToSteps(&x, 200);
  
  if (abs(z.pos - zStart) > zTolerance) {
    Serial.println("error: Z position mismatch for threading start");
    Serial.printf("Expected: %.3f, Actual: %.3f\n", 
        stepsToDu(&z, zStart)/10000.0, 
        stepsToDu(&z, z.pos)/10000.0);
    return false;
  }
  
  if (abs(x.pos - xStart) > xTolerance) {
    Serial.println("error: X position mismatch for threading start");
    Serial.printf("Expected: %.3f, Actual: %.3f\n", 
        stepsToDu(&x, xStart)/10000.0, 
        stepsToDu(&x, x.pos)/10000.0);
    return false;
  }
  
  // Calculate threading characteristics
  bool isExternal = (xStart < xEnd);
  long xDepth = abs(xEnd - xStart);
  long xDirection = isExternal ? 1 : -1;
  
  // Calculate safe retract position
  long safeRetractSteps = SAFE_DISTANCE_DU * x.motorSteps / x.screwPitch;
  long xSafe = xStart + (isExternal ? -safeRetractSteps : safeRetractSteps);
  
  // Debug output
  Serial.println("========================================");
  Serial.println("G33 THREADING");
  Serial.println("========================================");
  Serial.printf("Type: %s\n", isExternal ? "EXTERNAL" : "INTERNAL");
  Serial.printf("Pitch: %.3fmm\n", pitchMm);
  Serial.printf("Passes: %d\n", passes);
  Serial.printf("Z: %.3f -> %.3f (%.3fmm travel)\n", 
      stepsToDu(&z, zStart)/10000.0, 
      stepsToDu(&z, zEnd)/10000.0,
      abs(stepsToDu(&z, zEnd - zStart))/10000.0);
  Serial.printf("X: %.3f -> %.3f (%.3fmm depth)\n",
      stepsToDu(&x, xStart)/10000.0,
      stepsToDu(&x, xEnd)/10000.0,
      abs(stepsToDu(&x, xEnd - xStart))/10000.0);
  Serial.println("========================================");
  
  // Execute threading passes
  for (int pass = 1; pass <= passes; pass++) {
    if (!isOn) {
      Serial.println("Threading aborted");
      return false;
    }
    
    // Calculate depth for this pass (progressive, squared for lighter first passes)
    float remainingPasses = passes - pass;
    float depthRatio = 1.0 - pow(remainingPasses / float(passes), 2);
    long currentXEnd = xStart + round(xDepth * depthRatio * xDirection);
    
    Serial.printf("Pass %d/%d: X depth %.3fmm (%.1f%%)\n", 
        pass, passes,
        abs(stepsToDu(&x, currentXEnd - xStart))/10000.0,
        depthRatio * 100);
    
    // 1. Position to start of cut
    z.speedMax = z.speedManualMove;
    x.speedMax = x.speedManualMove;
    stepToFinal(&z, zStart);
    stepToFinal(&x, currentXEnd);
    gcodeWaitStop();
    
    // 2. Synchronize with spindle for threading
    synchronizeSpindleForThreading(zStart, threadPitch);
    
    // 3. Execute threading cut following spindle
    executeThreadingCutMove(zStart, zEnd, currentXEnd, threadPitch);
    
    // 4. Retract to safe position
    x.speedMax = x.speedManualMove;
    stepToFinal(&x, xSafe);
    gcodeWaitStop();
    
    // 5. Return to start Z for next pass (if not last pass)
    if (pass < passes) {
      z.speedMax = z.speedManualMove;
      stepToFinal(&z, zStart);
      gcodeWaitStop();
    }
  }
  
  // Final positioning - return to start
  z.speedMax = z.speedManualMove;
  stepToFinal(&z, zStart);
  gcodeWaitStop();
  
  Serial.println("Threading complete");
  Serial.println("========================================");
  
  return true;
}


// G33 Threading command handler (Legacy)
// Format: G33 L[length] Z[end] X[end] P[pitch] H[passes] Q[start_z] R[start_x]
// Parameters:
//   L - Length of thread
//   Z - End Z position (cant be used in conjunction with L)
//   X - End X position
//   P - Thread pitch in mm
//   H - Number of passes (optional, default 3)
//   Q - Start Z position (optional, defaults to current position)
//   R - Start X position (optional, defaults to current position)
// Example: G33 Z20 X-4.188 P1.5 H4 Q0 R-5 - External M10x1.5 thread
// Example: G33 Z20 X-5.1 P1.5 H4 Q0 R-4.5 - Internal M10x1.5 thread
bool handleG33(const String& command) {

    // Validate required parameters
    bool hasZ = command.indexOf('Z') >= 0;
    bool hasL = command.indexOf('L') >= 0;
    bool hasX = command.indexOf('X') >= 0;
    bool hasP = command.indexOf('P') >= 0;

    // X and P are always required
    if (!hasX) {
        Serial.println("error: G33 requires X parameter");
        return false;
    }

    if (!hasP) {
        Serial.println("error: G33 requires P parameter (pitch)");
        return false;
    }

    // Z and L are mutually exclusive, but one is required
    if (hasZ && hasL) {
        Serial.println("error: G33 cannot have both Z and L parameters");
        return false;
    }

    if (!hasZ && !hasL) {
        Serial.println("error: G33 requires Z (end position) or L (length) parameter");
        return false;
    }

    // Get start positions (optional, default to current position)
    long zStart = command.indexOf('Q') >= 0 ? 
        mmOrInchToAbsolutePos(&z, getFloat(command, 'Q')) : 
        z.pos;
    long xStart = command.indexOf('R') >= 0 ? 
        mmOrInchToAbsolutePos(&x, getFloat(command, 'R')) : 
        x.pos;

    // Get end positions
    long zEnd;
    if (hasL) {
        float lengthMm = getFloat(command, 'L');
        long lengthSteps = duToSteps(&z, round(lengthMm * 10000));
        zEnd = zStart + lengthSteps;
    } else {
        zEnd = mmOrInchToAbsolutePos(&z, getFloat(command, 'Z'));
    }
    long xEnd = mmOrInchToAbsolutePos(&x, getFloat(command, 'X'));
    
    // Get pitch in machine units (deci-microns)
    float pitchMm = getFloat(command, 'P');
    if (pitchMm <= 0) {
        Serial.println("error: Invalid pitch value");
        return false;
    }
    long threadPitch = round(pitchMm * 10000);

    // Get and validate number of passes
    int passes = command.indexOf('H') >= 0 ? getInt(command, 'H') : 3;
    if (passes <= 0 || passes > PASSES_MAX) {
        Serial.println("error: Invalid number of passes (1-" + String(PASSES_MAX) + ")");
        return false;
    }

    // Determine threading characteristics from G-code parameters
    bool isExternal = (xStart < xEnd);      // External if moving from more negative to less negative
    bool isRightHanded = (zStart < zEnd);   // Right-handed if moving in positive Z direction

    // Set dupr sign to match threading direction
    // modeTurn uses opDuprSign (derived from dupr) to determine start/end stops:
    //   opDuprSign > 0: starts at rightStop, ends at leftStop (right-to-left cutting)
    //   opDuprSign < 0: starts at leftStop, ends at rightStop (left-to-right cutting)
    // So for left-handed threads (cutting left-to-right), we need negative dupr
    if (!isRightHanded) {
      threadPitch = -threadPitch;
    }
    
    long zTolerance = duToSteps(&z, 100); // 0.01mm tolerance  
    long xTolerance = duToSteps(&x, 100);

    if (abs(z.pos - zStart) > zTolerance) {
        Serial.println("error: Z position mismatch for threading start");
        return false;
    }

    if (abs(x.pos - xStart) > xTolerance) {
        Serial.println("error: X position mismatch for threading start");
        return false;
    }

    // Store current mode and settings
    int previousMode = mode;
    long previousDupr = dupr;
    bool previousIsOn = isOn;
    bool previousAuxForward = auxForward;

    // Set up threading mode and parameters
    setModeFromLoop(MODE_THREAD);
    setDupr(threadPitch);
    // Set auxForward based on our external/internal determination for compatibility
    auxForward = isExternal;
    setTurnPasses(passes);

    // Set stops as offsets from current position (now at start position)
    long zOffset = abs(zEnd - zStart);
    long xOffset = abs(xEnd - xStart);

    // Set Z stops based on threading direction
    if (isRightHanded) {
        // Right-handed: start at right stop, end at left stop
        setRightStop(&z, 0);        // Start position
        setLeftStop(&z, zOffset);   // End position
    } else {
        // Left-handed: start at left stop, end at right stop  
        // Moving Left to right requires more negative
        zOffset = zEnd - zStart;
        setLeftStop(&z, 0);         // Start position
        setRightStop(&z, zOffset);  // End position
    }

    // Set X stops based on threading type
    if (isExternal) {
        // External: algorithm expects safe at right stop, cutting at left stop
        setRightStop(&x, 0);        // Start position (safe)
        setLeftStop(&x, xOffset);   // End position (cutting depth)
    } else {
        // Internal: algorithm expects safe at left stop, cutting at right stop
        // Internal: moving from less negative to more negative (away from centerline)
        // The offset should represent steps away from centerline
        xOffset = xEnd - xStart;
        setLeftStop(&x, 0);         // Start position (safe)
        setRightStop(&x, xOffset);  // End position (cutting depth)
    }

    // Wait for stops to be applied
    while (z.nextLeftStopFlag || z.nextRightStopFlag || 
           x.nextLeftStopFlag || x.nextRightStopFlag) {
        delay(10);
    }

    Serial.print("Z Left Stop: ");
    Serial.print(stepsToDu(&z, z.leftStop) / 10000.0, 3);
    Serial.println("mm");

    Serial.print("Z Right Stop: ");
    Serial.print(stepsToDu(&z, z.rightStop) / 10000.0, 3);
    Serial.println("mm");

    Serial.print("X Forward Stop: ");
    Serial.print(stepsToDu(&x, x.leftStop) / 10000.0, 3);
    Serial.println("mm");

    Serial.print("X Back Stop: ");
    Serial.print(stepsToDu(&x, x.rightStop) / 10000.0, 3);
    Serial.println("mm");

    // Start threading operation
    setIsOnFromLoop(true);
    
    // Wait for threading to complete
    while (isOn) {
        checkForStopCommand();
        delay(10);
        if (!isOn) break;
    }

    Serial.println("G33: Threading while loop exited");

    // Clear the soft stops
    setLeftStop(&z, LONG_MAX);
    setRightStop(&z, LONG_MIN);
    setLeftStop(&x, LONG_MAX);
    setRightStop(&x, LONG_MIN);

    Serial.println("G33: Stops cleared");

    // Wait for stops to be cleared
    while (z.nextLeftStopFlag || z.nextRightStopFlag || 
           x.nextLeftStopFlag || x.nextRightStopFlag) {
        delay(10);
    }

    // Restore previous mode and settings
    setModeFromLoop(previousMode);
    setDupr(previousDupr);
    auxForward = previousAuxForward;
    setIsOnFromLoop(true);
    Serial.println("G33: Mode restored, returning");
    return true;
}

/**
 * G10 - Set Tool Offset and Compensation Values
 * 
 * Sets the tool offset and optional compensation values for a specified tool.
 * Tool 0 is reserved as the reference tool.
 * 
 * Format: G10 P[tool] Z[z_offset] X[x_offset] W[z_comp] U[x_comp]
 * 
 * Parameters:
 * P - Tool number (1-9)
 * Z - Z axis offset from reference tool (mm, optional)
 * X - X axis offset from reference tool (mm, optional)
 * W - Z axis cutting compensation (mm, optional)
 * U - X axis cutting compensation (mm, optional)
 * 
 * Example:
 * G10 P2 Z1 X-3        // Set tool 2 offset: Z=1mm, X=-3mm
 * G10 P2 X-27          // Set only X offset, leave Z unchanged
 * G10 P2 Z1 X-3 W-0.05 U-0.1  // Set offsets plus compensations
 * 
 * Notes:
 * - Only specified parameters are updated; others remain unchanged
 * - Offsets (Z,X) define the tool's geometric position relative to tool 0
 * - Compensation values (W,U) adjust for tool deflection or cutting variations
 * - All values are in millimeters
 * - Positive X moves tool away from spindle center
 * - Positive Z moves tool away from chuck
 * 
 * @param command The G10 command string to parse
 * @return true if command was valid and executed, false otherwise
 */
bool handleG10(const String& command) {
    int toolIndex = getInt(command, 'P');
    
    // Check if toolIndex is within the valid range
    if (toolIndex < 1 || toolIndex >= MAX_TOOLS) {
        return false;
    }

    // Only update offsets that are explicitly specified in the command
    if (command.indexOf('Z') != -1) {
        float zOffset = getFloat(command, 'Z');
        toolOffsets[toolIndex].zOffsetDu = zOffset * 10000;
    }

    if (command.indexOf('X') != -1) {
        float xOffset = getFloat(command, 'X');
        toolOffsets[toolIndex].xOffsetDu = xOffset * 10000;
    }

    // Get compensation values if present, otherwise leave existing values unchanged
    if (command.indexOf('U') != -1) {
        float xComp = getFloat(command, 'U');
        toolOffsets[toolIndex].xCompDu = xComp * 10000;
    }

    if (command.indexOf('W') != -1) {
        float zComp = getFloat(command, 'W');
        toolOffsets[toolIndex].zCompDu = zComp * 10000;
    }

    offsetsChanged = true;
    return true;
}

// Set position (G92) implementation
bool handleG92(const String& command) {
  bool changed = false;
  
  // Check for X, Y(A1), Z axis parameters
  if (command.indexOf(z.name) >= 0) {
    float value = getFloat(command, z.name);
    long steps = round(value * (measure == MEASURE_METRIC ? 10000 : 254000) / z.screwPitch * z.motorSteps);
    z.originPos = steps - z.pos;
    changed = true;
  }
  
  if (command.indexOf(x.name) >= 0) {
    float value = getFloat(command, x.name);
    long steps = round(value * (measure == MEASURE_METRIC ? 10000 : 254000) / x.screwPitch * x.motorSteps);
    x.originPos = steps - x.pos;
    changed = true;
  }
  
  if (command.indexOf(a1.name) >= 0) {
    float value = getFloat(command, a1.name);
    long steps = round(value * (measure == MEASURE_METRIC ? 10000 : 254000) / a1.screwPitch * a1.motorSteps);
    a1.originPos = steps - a1.pos;
    changed = true;
  }

  // If no axis specified, zero all axes
  if (!changed && command.length() <= 3) {
    z.originPos = -z.pos;
    x.originPos = -x.pos;
    if (ACTIVE_A1) a1.originPos = -a1.pos;
    changed = true;
  }
  
  return changed;
}

bool handleChangeToolCommand(String command) {
  int toolNumber = command.substring(1).toInt();
  if (toolNumber >= 0 && toolNumber < MAX_TOOLS) {   
        nextTool = toolNumber;
        nextToolFlag = true; // Indicate a tool change is pending
        return true;
  } else {
    Serial.println("error: invalid tool number");
    return false;
  }
}

// void enterToolMode() {
//   currentToolMode = TOOL_SELECT;
//   pendingToolNumber = -1;
//   pendingInput = "";
//   updateToolDisplay();
// }

// void exitToolMode() {
//   lcd.clear();
//   currentToolMode = TOOL_IDLE;
//   lcdHashLine0 = LCD_HASH_INITIAL;
//   lcdHashLine1 = LCD_HASH_INITIAL;
//   lcdHashLine2 = LCD_HASH_INITIAL;
//   lcdHashLine3 = LCD_HASH_INITIAL;
//   forceDisplayRefresh = true;
// }

// void processToolNumericInput(int inputValue) {
//     if (currentToolMode == TOOL_SELECT) {
//         pendingInput += String(inputValue);
//         pendingToolNumber = pendingInput.toInt();
//         if (pendingToolNumber >= MAX_TOOLS) {
//             pendingToolNumber = MAX_TOOLS - 1;
//             pendingInput = String(pendingToolNumber);
//         }
//     }
//     updateToolDisplay();
// }

// void processToolSpecialInput(int keyCode) {
//     if (currentToolMode == TOOL_SELECT && keyCode == B_BACKSPACE) {
//         if (pendingInput.length() > 0) {
//             pendingInput = pendingInput.substring(0, pendingInput.length() - 1);
//             pendingToolNumber = pendingInput.length() > 0 ? pendingInput.toInt() : -1;
//         }
//     }
//     updateToolDisplay();
// }

// void processToolConfirmation() {
//   switch (currentToolMode) {
//     case TOOL_SELECT:
//       if (pendingToolNumber >= 0 && pendingToolNumber < MAX_TOOLS) {
//         currentToolMode = TOOL_CONFIRM;
//       } else {
//         lcd.setCursor(0, 3);
//         lcd.print("Invalid tool number");
//         delay(2000);
//         pendingToolNumber = -1;
//         pendingInput = "";
//       }
//       break;
//     case TOOL_CONFIRM:
//       // Here we'll change the tool without editing
//       changeTool(pendingToolNumber);
//       lcd.clear();
//       lcd.setCursor(0, 1);
//       lcd.print("Tool changed to T");
//       lcd.print(pendingToolNumber);
//       delay(2000);
//       exitToolMode();
//       break;
//   }
//   updateToolDisplay();
// }

// void handleToolConfirmOff() {
//   currentToolMode = TOOL_SELECT;
//     pendingInput = "";  // Clear input
//     updateToolDisplay();
// }

void changeTool(int newToolNumber) {
    currentTool = newToolNumber;
    ToolOffset newToolOffset = toolOffsets[newToolNumber];

    // Calculate total offset for new tool (geometry + compensation)
    ToolOffset newTotalOffset;
    newTotalOffset.zOffsetDu = newToolOffset.zOffsetDu + newToolOffset.zCompDu;
    newTotalOffset.xOffsetDu = newToolOffset.xOffsetDu + newToolOffset.xCompDu;

    // Calculate the net change needed
    ToolOffset netOffset;
    netOffset.zOffsetDu = newTotalOffset.zOffsetDu - currentAppliedOffset.zOffsetDu;
    netOffset.xOffsetDu = newTotalOffset.xOffsetDu - currentAppliedOffset.xOffsetDu;

    // Apply the net change
    applyToolOffset(netOffset);
    
    // Update our tracking of what's currently applied
    currentAppliedOffset = newTotalOffset;
    
    // Keep the base tool offset info for reference (without compensation)
    toolOffset = newToolOffset;
}

void applyToolOffset(ToolOffset offset) {
    long xOffsetSteps = floatDuToSteps(&x, offset.xOffsetDu);
    long zOffsetSteps = floatDuToSteps(&z, offset.zOffsetDu);
    
    x.originPos += xOffsetSteps;
    z.originPos += zOffsetSteps;
}

// Process one command, return ok flag.
bool handleGcodeCommand(String command) {
  command.trim();
  if (command.length() == 0) return false;

  // Trim N.. prefix.
  char code = command.charAt(0);
  int spaceIndex = command.indexOf(' ');
  if (code == 'N' && spaceIndex > 0) {
    command = command.substring(spaceIndex + 1);
    code = command.charAt(0);
  }

  // Update position for relative calculations right before performing them.
  z.gcodeRelativePos = gcodeAbsolutePositioning ? -z.originPos : z.pos;
  x.gcodeRelativePos = gcodeAbsolutePositioning ? -x.originPos : x.pos;
  a1.gcodeRelativePos = gcodeAbsolutePositioning ? -a1.originPos : a1.pos;

  setFeedRate(command);
  setSpindleSpeed(command);
  switch (code) {
    case 'G':
    case NAME_Z:
    case NAME_X:
    case NAME_A1: return handleGcode(command);
    case 'F': return true; /* feed already handled above */
    case 'S': return true; /* spindle speed already handled above */
    case 'M': return handleMcode(command);
    case 'T': return handleChangeToolCommand(command);
    default: Serial.print("error: unsupported command "); Serial.println(code); return false;
  }
  return false;
}

void discountFullSpindleTurns() {
  // When standing at the stop, ignore full spindle turns.
  // This allows to avoid waiting when spindle direction reverses
  // and reduces the chance of the skipped stepper steps since
  // after a reverse the spindle starts slow.
  if (dupr != 0 && !stepperIsRunning(&z) && (mode == MODE_NORMAL || mode == MODE_CONE)) {
    int spindlePosDiff = 0;
    if (z.pos == z.rightStop) {
      long stopSpindlePos = spindleFromPos(&z, z.rightStop);
      if (dupr > 0) {
        if (spindlePos < stopSpindlePos - ENCODER_STEPS_INT) {
          spindlePosDiff = ENCODER_STEPS_INT;
        }
      } else {
        if (spindlePos > stopSpindlePos + ENCODER_STEPS_INT) {
          spindlePosDiff = -ENCODER_STEPS_INT;
        }
      }
    } else if (z.pos == z.leftStop) {
      long stopSpindlePos = spindleFromPos(&z, z.leftStop);
      if (dupr > 0) {
        if (spindlePos > stopSpindlePos + ENCODER_STEPS_INT) {
          spindlePosDiff = -ENCODER_STEPS_INT;
        }
      } else {
        if (spindlePos < stopSpindlePos - ENCODER_STEPS_INT) {
          spindlePosDiff = ENCODER_STEPS_INT;
        }
      }
    }
    if (spindlePosDiff != 0) {
      spindlePos += spindlePosDiff;
      spindlePosAvg += spindlePosDiff;
    }
  }
}

#ifdef SIMULATE_SPINDLE
void simulateSpindle() {

  if (spindlePosSync != 0) {
    spindlePosSync = 0;
  }

  static unsigned long lastSimTime = 0;
  unsigned long now = micros();
  
  if (lastSimTime == 0) {
    lastSimTime = now;
    return;
  }
  
  // Calculate how many encoder counts should have occurred
  float countsPerMicrosecond = (ENCODER_STEPS_INT * SIMULATED_RPM) / 60000000.0;
  long elapsed = now - lastSimTime;
  int delta = (int)(elapsed * countsPerMicrosecond);
  
  if (delta > 0) {
    spindlePos += delta;
    spindlePosAvg += delta;
    spindlePosGlobal += delta;
    spindleEncTime = now;
    lastSimTime = now;
    
    // Simulate RPM display timing
    spindleEncTimeDiffBulk = 60000000 / SIMULATED_RPM;
    shownRpm = SIMULATED_RPM;
    shownRpmTime = now;
  }
}
#endif

void processSpindleCounter() {
  int16_t count;
  pcnt_get_counter_value(PCNT_UNIT_0, &count);
  int delta = count - spindleCount;
  if (delta == 0) {
    return;
  }
  if (count >= PCNT_CLEAR || count <= -PCNT_CLEAR) {
    pcnt_counter_clear(PCNT_UNIT_0);
    spindleCount = 0;
  } else {
    spindleCount = count;
  }

  unsigned long microsNow = micros();
  if (showTacho || mode == MODE_GCODE) {
    if (spindleEncTimeIndex >= RPM_BULK) {
      spindleEncTimeDiffBulk = microsNow - spindleEncTimeAtIndex0;
      spindleEncTimeAtIndex0 = microsNow;
      spindleEncTimeIndex = 0;
    }
    spindleEncTimeIndex += abs(delta);
  } else {
    spindleEncTimeDiffBulk = 0;
  }

  spindlePos += delta;
  spindlePosGlobal += delta;
  if (spindlePosGlobal > ENCODER_STEPS_INT) {
    spindlePosGlobal -= ENCODER_STEPS_INT;
  } else if (spindlePosGlobal < 0) {
    spindlePosGlobal += ENCODER_STEPS_INT;
  }
  if (spindlePos > spindlePosAvg) {
    spindlePosAvg = spindlePos;
  } else if (spindlePos < spindlePosAvg - ENCODER_BACKLASH) {
    spindlePosAvg = spindlePos + ENCODER_BACKLASH;
  }
  spindleEncTime = microsNow;

  if (spindlePosSync != 0) {
    spindlePosSync += delta;
    if (spindlePosSync % ENCODER_STEPS_INT == 0) {
      spindlePosSync = 0;
      Axis* a = getPitchAxis();
      spindlePosAvg = spindlePos = spindleFromPos(a, a->pos);
    }
  }
}

// Apply changes requested by the keyboard thread.
void applySettings() {
  if (nextDuprFlag) {
    applyDupr();
    nextDuprFlag = false;
  }
  if (nextStartsFlag) {
    applyStarts();
    nextStartsFlag = false;
  }
  if (z.nextLeftStopFlag) {
    applyLeftStop(&z);
    z.nextLeftStopFlag = false;
  }
  if (z.nextRightStopFlag) {
    applyRightStop(&z);
    z.nextRightStopFlag = false;
  }
  if (x.nextLeftStopFlag) {
    applyLeftStop(&x);
    x.nextLeftStopFlag = false;
  }
  if (x.nextRightStopFlag) {
    applyRightStop(&x);
    x.nextRightStopFlag = false;
  }
  if (a1.nextLeftStopFlag) {
    applyLeftStop(&a1);
    a1.nextLeftStopFlag = false;
  }
  if (a1.nextRightStopFlag) {
    applyRightStop(&a1);
    a1.nextRightStopFlag = false;
  }
  if (nextConeRatioFlag) {
    applyConeRatio();
    nextConeRatioFlag = false;
  }
  if (nextIsOnFlag) {
    setIsOnFromLoop(nextIsOn);
    nextIsOnFlag = false;
  }
  if (nextModeFlag) {
    setModeFromLoop(nextMode);
    nextModeFlag = false;
  }
  if (nextToolFlag) {
    changeTool(nextTool);
    nextToolFlag = false;
  }
}

void loop() {

  if (emergencyStop != ESTOP_NONE) {
    return;
  }

  if (xSemaphoreTake(motionMutex, 1) != pdTRUE) {
    return;
  }

  applySettings();

  // To simulte RPM and spindle indexing
  // #if (SIMULATE_SPINDLE == true)
  //  simulateSpindle();
  // #else
  //   processSpindleCounter();
  // #endif

  processSpindleCounter();
  discountFullSpindleTurns();
  unsigned long t3 = micros();

  if (!isOn || dupr == 0 || spindlePosSync != 0) {
    // None of the modes work.
  } else if (mode == MODE_NORMAL) {
    modeGearbox();
  } else if (mode == MODE_TURN) {
    modeTurn(&z, &x);
  } else if (mode == MODE_FACE) {
    modeTurn(&x, &z);
  } else if (mode == MODE_CUT) {
    modeCut();
  } else if (mode == MODE_CONE) {
    modeCone();
  } else if (mode == MODE_THREAD) {
    modeTurn(&z, &x);
  } else if (mode == MODE_ELLIPSE) {
    modeEllipse(&z, &x);
  }

  moveAxis(&z);
  moveAxis(&x);
  if (ACTIVE_A1) moveAxis(&a1);

  xSemaphoreGive(motionMutex);

}
