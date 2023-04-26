#ifndef CONFIGURATION_PRUSA_H
#define CONFIGURATION_PRUSA_H

#include <limits.h>
#include "printers.h"
/*------------------------------------
 GENERAL SETTINGS
 *------------------------------------*/
// Printer revision
#define PRINTER_TYPE PRINTER_MK3S
#define PRINTER_NAME PRINTER_MK3S_NAME
#define PRINTER_MMU_TYPE PRINTER_MK3S_MMU2
#define PRINTER_MMU_NAME PRINTER_MK3S_MMU2_NAME
#define FILAMENT_SIZE "1_75mm_MK3"
#define NOZZLE_TYPE "E3Dv6full"

// Developer flag
#define DEVELOPER

// Printer name
#define CUSTOM_MENDEL_NAME "Not again!"

// Electronics
#define MOTHERBOARD BOARD_EINSY_1_0a
#define STEEL_SHEET
#define HAS_SECOND_SERIAL_PORT

// PSU
#define PSU_Delta                                 // uncomment if DeltaElectronics PSU installed

/*------------------------------------
 AXIS SETTINGS
 *------------------------------------*/
#define NUM_AXIS 4 // The axis order in all axis related arrays is X, Y, Z, E
#define HOMING_FEEDRATE {3000, 3000, 800, 0}  // set the homing speeds (mm/min) // 3000 is also valid for stallGuard homing. Valid range: 2200 - 3000

// BED_ZERO_REF_X/Y are the machine coordinates when the nozzle is zeroed to the bed's print area (0;0)
#define BED_ZERO_REF_X 2.5f	//(- 22.f + X_PROBE_OFFSET_FROM_EXTRUDER) // -22 + 23 = 1
#define BED_ZERO_REF_Y 7.5f	//(- 0.6f + Y_PROBE_OFFSET_FROM_EXTRUDER + 4.f) // -0.6 + 5 + 4 = 8.4
/** [0,0] bed print area point X coordinate in bed coordinates ver. 05d/24V */
#define BED_PRINT_ZERO_REF_X 0.0f //2.0f
/** [0,0] bed print area point Y coordinate in bed coordinates ver. 05d/24V */
#define BED_PRINT_ZERO_REF_Y 0.0f //9.4f
/** [0,0] steel sheet print area point X coordinate in bed print area coordinates */
#define SHEET_PRINT_ZERO_REF_X 0.0f
/** [0,0] steel sheet print area point Y coordinate in bed print area coordinates */
#define SHEET_PRINT_ZERO_REF_Y 0.0f

#define X_BED_SIZE 250
#define Y_BED_SIZE 210
/** Directly specify the bed size. 
 * This allows Marlin to do extra logic related to the bed size when it differs from the movement limits below. 
 * If the XY carriage is able to move outside of the bed, you can specify a wider range below.*/

// Travel limits after homing: 0 - MAX
#define X_MAX_POS X_BED_SIZE 
#define X_MIN_POS -BED_ZERO_REF_X
#define Y_MAX_POS Y_BED_SIZE // 212
#define Y_MIN_POS -BED_ZERO_REF_Y //orig -4
#define Z_MAX_POS 210
#define Z_MIN_POS 0.15
/** The above defines the printable area of the 3d printer after homing.
For the X and Y axis you just measure the travel length of the nozzle from the home position. 
The maximum travel length will either be restricted by the size of the buildplatform or by the maximum travel distance of the axis.

When setting up the Z axis for the first time, it is best to set the Z axis travel length 
a bit shorter than what is measured until a software and hardware test of the 3d printer is completed.

This will help to avoid accidentally crashing the build bed into the hot end during initial tests. 
The Z axis travel length can be fine tuned later after the tests have been satisfied.

The measurement units are in millimeters and are defined from line 249 for the maximum positions in the Marlin firmware configuration file.
The minimum positions can be left at the default 0 for this configuration **/
 
/** Another definition:
These values specify the physical limits of the machine. 
Usually the [XYZ]_MIN_POS values are set to 0, because endstops are positioned at the bed limits. 
[XYZ]_MAX_POS should be set to the farthest reachable point. 
By default, these are used as your homing positions as well. 
However, the MANUAL_[XYZ]_HOME_POS options can be used to override these, if needed. **/

// Home position
#define MANUAL_X_HOME_POS 0
#define MANUAL_Y_HOME_POS -2.2
#define MANUAL_Z_HOME_POS 0.2

//#define DEFAULT_Y_OFFSET    4.f // Default distance of Y_MIN_POS point from endstop, when the printer is not calibrated.

#define X_PROBE_OFFSET_FROM_EXTRUDER (31.0)  // Z probe to nozzle X offset: -left  +right
#define Y_PROBE_OFFSET_FROM_EXTRUDER (12.5)  // Z probe to nozzle Y offset: -front +behind
#define Z_PROBE_OFFSET_FROM_EXTRUDER (-0.4)  // Z probe to nozzle Z offset: -below (always!)

/**
 * @brief Positions of the bed reference points in print area coordinates. ver. 05d/24V
 *
 * Numeral constants are in bed coordinates, subtracting macro defined values converts it to print area coordinates.
 *
 * The points are the following: front left, front right, rear right, rear left 
 **/                                                                                                              //NEW    //MK3S originals                                               
#define BED_REF_POINT0_X	35.5f - BED_PRINT_ZERO_REF_X - X_PROBE_OFFSET_FROM_EXTRUDER - SHEET_PRINT_ZERO_REF_X   // 4.5   //37.0
#define BED_REF_POINT0_Y	8.5f  - BED_PRINT_ZERO_REF_Y - Y_PROBE_OFFSET_FROM_EXTRUDER - SHEET_PRINT_ZERO_REF_Y   //-4     //18.4

#define BED_REF_POINT1_X	243.0f - BED_PRINT_ZERO_REF_X - X_PROBE_OFFSET_FROM_EXTRUDER - SHEET_PRINT_ZERO_REF_X  // 212   //245.0
#define BED_REF_POINT1_Y	8.5f   - BED_PRINT_ZERO_REF_Y - Y_PROBE_OFFSET_FROM_EXTRUDER - SHEET_PRINT_ZERO_REF_Y  //-4     //18.4

#define BED_REF_POINT2_X	243.0f - BED_PRINT_ZERO_REF_X - X_PROBE_OFFSET_FROM_EXTRUDER - SHEET_PRINT_ZERO_REF_X  // 212   //245.0
#define BED_REF_POINT2_Y	200.5f - BED_PRINT_ZERO_REF_Y - Y_PROBE_OFFSET_FROM_EXTRUDER - SHEET_PRINT_ZERO_REF_Y  // 188   //210.4

#define BED_REF_POINT3_X	35.5f  - BED_PRINT_ZERO_REF_X - X_PROBE_OFFSET_FROM_EXTRUDER - SHEET_PRINT_ZERO_REF_X  // 4.5   //37.0
#define BED_REF_POINT3_Y	200.5f - BED_PRINT_ZERO_REF_Y - Y_PROBE_OFFSET_FROM_EXTRUDER - SHEET_PRINT_ZERO_REF_Y  // 188   //210.4

#define BED_X0 1     //(2.f - BED_ZERO_REF_X) //1
#define BED_Y0 1     //(9.4f - BED_ZERO_REF_Y) //1
#define BED_Xn 205   //(206.f - BED_ZERO_REF_X) //205
#define BED_Yn 205   //(213.4f - BED_ZERO_REF_Y) //205

#define BED_X(i, n) ((float)i * (BED_Xn - BED_X0) / (n - 1) + BED_X0)
#define BED_Y(i, n) ((float)i * (BED_Yn - BED_Y0) / (n - 1) + BED_Y0)

// Radius used in function 'xyzcal_searchZ' to find approx Z-axis position of bed reference point.
#define XYZ_CAL_SEARCH_RADIUS 450 // Default 900

// Mesh definitions 1;1 - 205;205 + probe offset
#define MESH_MIN_X (BED_X0 + X_PROBE_OFFSET_FROM_EXTRUDER)   //31   //24 orig probe nozzle offset?
#define MESH_MAX_X (BED_Xn + X_PROBE_OFFSET_FROM_EXTRUDER)   //228
#define MESH_MIN_Y (BED_Y0 + Y_PROBE_OFFSET_FROM_EXTRUDER)   //12   //6 
#define MESH_MAX_Y (BED_Y0 + Y_PROBE_OFFSET_FROM_EXTRUDER)   //210

#define MESH_HOME_Z_CALIB 0.2
#define MESH_HOME_Z_SEARCH 5.0f           // Z lift for homing, mesh bed leveling etc.

// Backlash - 
//#define BACKLASH_X
//#define BACKLASH_Y

// Canceled home position
#define X_CANCEL_POS 50
#define Y_CANCEL_POS 190
#define Z_CANCEL_LIFT 50

//Pause print position
#define X_PAUSE_POS 50
#define Y_PAUSE_POS 190
#define Z_PAUSE_LIFT 20

// Steps per unit {X,Y,Z,E}
#define DEFAULT_AXIS_STEPS_PER_UNIT   {100,100,3200/8,786.5}

// Endstop inverting
#define X_MIN_ENDSTOP_INVERTING 0 // set to 1 to invert the logic of the endstop.
#define Y_MIN_ENDSTOP_INVERTING 0 // set to 1 to invert the logic of the endstop.
#define Z_MIN_ENDSTOP_INVERTING 0 // set to 1 to invert the logic of the endstop.

// Direction inverting
#define INVERT_X_DIR 1    // for Mendel set to 0, for Orca set to 1
#define INVERT_Y_DIR 0    // for Mendel set to 1, for Orca set to 0
#define INVERT_Z_DIR 1     // for Mendel set to 0, for Orca set to 1
#define INVERT_E0_DIR 0   // for direct drive extruder v9 set to 1, for geared extruder set to 0
#define INVERT_E1_DIR 0    // for direct drive extruder v9 set to 1, for geared extruder set to 0
#define INVERT_E2_DIR 0   // for direct drive extruder v9 set to 1, for geared extruder set to 0

#define DEFAULT_MAX_FEEDRATE                {200, 200, 12, 120}      // (mm/sec)   max feedrate (M203)
#define DEFAULT_MAX_FEEDRATE_SILENT         {100, 100, 12, 120}      // (mm/sec)   max feedrate (M203), silent mode

#define DEFAULT_MAX_ACCELERATION            {1000, 1000, 200, 5000}  // (mm/sec^2) max acceleration (M201)
#define DEFAULT_MAX_ACCELERATION_SILENT     {960, 960, 200, 5000}    // (mm/sec^2) max acceleration (M201), silent mode

#define DEFAULT_ACCELERATION          1250   // X, Y, Z and E max acceleration in mm/s^2 for printing moves (M204P)
#define DEFAULT_RETRACT_ACCELERATION  1250   // X, Y, Z and E max acceleration in mm/s^2 for retracts (M204R)
#define DEFAULT_TRAVEL_ACCELERATION   1250   // X, Y, Z and E max acceleration in mm/s^2 for travels (M204T)

#define MANUAL_FEEDRATE {2700, 2700, 1000, 100}   // set the speeds for manual moves (mm/min)

//Silent mode limits
#define SILENT_MAX_ACCEL_XY      960ul  // max acceleration in silent mode in mm/s^2
#define SILENT_MAX_FEEDRATE_XY   100  // max feedrate in mm/s

//Normal mode limits
#define NORMAL_MAX_ACCEL_XY     2500ul  // max acceleration in normal mode in mm/s^2
#define NORMAL_MAX_FEEDRATE_XY   200  // max feedrate in mm/s

//number of bytes from end of the file to start check
#define END_FILE_SECTION 20000

#define Z_AXIS_ALWAYS_ON 1

//Crash detection
#define CRASHDET_TIMER 45 //seconds
#define CRASHDET_COUNTER_MAX 3 

// New XYZ calibration
#define NEW_XYZCAL

// Watchdog support
#define WATCHDOG

// Power panic
#define UVLO_SUPPORT

// Fan check
//#define FANCHECK

// Safety timer
#define SAFETYTIMER
#define DEFAULT_SAFETYTIMER_TIME_MINS 30
#define FARM_DEFAULT_SAFETYTIMER_TIME_ms (45*60*1000ul)

// Offline crash dumper
// #define XFLASH_DUMP     // enable dump functionality (including D20/D21/D22)
// #define MENU_DUMP       // enable "Memory dump" in Settings menu
// #define EMERGENCY_DUMP  // trigger crash on stack corruption and WDR

// Online crash dumper
#define EMERGENCY_SERIAL_DUMP   // Request dump via serial on stack corruption and WDR
#define MENU_SERIAL_DUMP        // Enable "Memory dump" in Settings menu

// Filament sensor
#define FILAMENT_SENSOR
#define IR_SENSOR


// Minimum ambient temperature limit to start triggering MINTEMP errors [C]
// this value is litlebit higher that real limit, because ambient termistor is on the board and is temperated from it,
// temperature inside the case is around 31C for ambient temperature 25C, when the printer is powered on long time and idle
// the real limit is 15C (same as MINTEMP limit), this is because 15C is end of scale for both used thermistors (bed, heater)
#define MINTEMP_MINAMBIENT      10  // Default 10
#define MINTEMP_MINAMBIENT_RAW  1002 // Default 1002

#define DEBUG_DCODE2
#define DEBUG_DCODE3
#define DEBUG_DCODE6

#define DEBUG_BUILD     //Uncomment to disable DEBUG mode
//#define DEBUG_SEC_LANG   //secondary language debug output at startup
//#define DEBUG_XFLASH   //debug external spi flash
#ifdef DEBUG_BUILD
//#define _NO_ASM
#define DEBUG_DCODES //D codes
// #define DEBUG_STACK_MONITOR        //Stack monitor in stepper ISR
//#define DEBUG_FSENSOR_LOG          //Reports fsensor status to serial
//#define DEBUG_CRASHDET_COUNTERS  //Display crash-detection counters on LCD
//#define DEBUG_RESUME_PRINT       //Resume/save print debug enable 
//#define DEBUG_UVLO_AUTOMATIC_RECOVER // Power panic automatic recovery debug output 
//#define DEBUG_DISABLE_XMINLIMIT  //x min limit ignored
//#define DEBUG_DISABLE_XMAXLIMIT  //x max limit ignored
//#define DEBUG_DISABLE_YMINLIMIT  //y min limit ignored
//#define DEBUG_DISABLE_YMAXLIMIT  //y max limit ignored
//#define DEBUG_DISABLE_ZMINLIMIT  //z min limit ignored
//#define DEBUG_DISABLE_ZMAXLIMIT  //z max limit ignored
#define DEBUG_DISABLE_STARTMSGS //no startup messages 
//#define DEBUG_DISABLE_MINTEMP   //mintemp error ignored
// #define DEBUG_DISABLE_SWLIMITS  //sw limits ignored
//#define DEBUG_DISABLE_LCD_STATUS_LINE  //empty four lcd line
#define DEBUG_DISABLE_PREVENT_EXTRUDER //cold extrusion and long extrusion allowed
//#define DEBUG_DISABLE_PRUSA_STATISTICS //disable prusa_statistics() mesages
//#define DEBUG_DISABLE_FORCE_SELFTEST //disable force selftest
//#define DEBUG_XSTEP_DUP_PIN 21   //duplicate x-step output to pin 21 (SCL on P3)
//#define DEBUG_YSTEP_DUP_PIN 21   //duplicate y-step output to pin 21 (SCL on P3)
// #define DEBUG_DISABLE_FANCHECK     //disable fan check (no ISR INT7, check disabled)
//#define DEBUG_DISABLE_FSENSORCHECK //disable fsensor check (no ISR INT7, check disabled)
// #define DEBUG_DUMP_TO_2ND_SERIAL   //dump received characters to 2nd serial line
#define DEBUG_STEPPER_TIMER_MISSED // Stop on stepper timer overflow, beep and display a message.
// #define PLANNER_DIAGNOSTICS // Show the planner queue status on printer display.
// #define CMD_DIAGNOSTICS //Show cmd queue length on printer display
#endif /* DEBUG_BUILD */

//#define FSENSOR_QUALITY

#define LINEARITY_CORRECTION
#define TMC2130_LINEARITY_CORRECTION
#define TMC2130_LINEARITY_CORRECTION_XYZ
#define TMC2130_VARIABLE_RESOLUTION

/*------------------------------------
 TMC2130 default settings
 *------------------------------------*/

#define TMC2130_FCLK 12000000       // fclk = 12MHz

#define TMC2130_USTEPS_XY   16        // microstep resolution for XY axes
#define TMC2130_USTEPS_Z    16        // microstep resolution for Z axis
#define TMC2130_USTEPS_E    32        // microstep resolution for E axis
#define TMC2130_INTPOL_XY   1         // extrapolate 256 for XY axes
#define TMC2130_INTPOL_Z    1         // extrapolate 256 for Z axis
#define TMC2130_INTPOL_E    1         // extrapolate 256 for E axis

#define TMC2130_PWM_GRAD_X  2         // PWMCONF
#define TMC2130_PWM_AMPL_X  230       // PWMCONF
#define TMC2130_PWM_AUTO_X  1         // PWMCONF
#define TMC2130_PWM_FREQ_X  2         // PWMCONF

#define TMC2130_PWM_GRAD_Y  2         // PWMCONF
#define TMC2130_PWM_AMPL_Y  235       // PWMCONF
#define TMC2130_PWM_AUTO_Y  1         // PWMCONF
#define TMC2130_PWM_FREQ_Y  2         // PWMCONF

#define TMC2130_PWM_GRAD_Z  4         // PWMCONF
#define TMC2130_PWM_AMPL_Z  200       // PWMCONF
#define TMC2130_PWM_AUTO_Z  1         // PWMCONF
#define TMC2130_PWM_FREQ_Z  2         // PWMCONF

#define TMC2130_PWM_GRAD_E  4         // PWMCONF
#define TMC2130_PWM_AMPL_E  240       // PWMCONF
#define TMC2130_PWM_AUTO_E  1         // PWMCONF
#define TMC2130_PWM_FREQ_E  2         // PWMCONF

// experimental setting for E-motor cooler operation
#define TMC2130_PWM_GRAD_Ecool  84        // PWMCONF 730mA @ 375mm/min  970mA phase peak at feedrate 900mm/min
#define TMC2130_PWM_AMPL_Ecool  43        // PWMCONF 500mA phase peak at feedrate 10 mm/min
#define TMC2130_PWM_AUTO_Ecool  0         // PWMCONF

#define TMC2130_TOFF_XYZ    3         // CHOPCONF // fchop = 27.778kHz
#define TMC2130_TOFF_E      3         // CHOPCONF // fchop = 27.778kHz
//#define TMC2130_TOFF_E      4         // CHOPCONF // fchop = 21.429kHz
//#define TMC2130_TOFF_E      5         // CHOPCONF // fchop = 17.442kHz

//#define TMC2130_STEALTH_E // Extruder stealthChop mode
//#define TMC2130_CNSTOFF_E // Extruder constant-off-time mode (similar to MK2)

//#define TMC2130_PWM_DIV   683         // PWM frequency divider (1024, 683, 512, 410)
#define TMC2130_PWM_DIV   512         // PWM frequency divider (1024, 683, 512, 410)
#define TMC2130_PWM_CLK   (2 * TMC2130_FCLK / TMC2130_PWM_DIV) // PWM frequency (23.4kHz, 35.1kHz, 46.9kHz, 58.5kHz for 12MHz fclk)

#define TMC2130_TPWMTHRS  0         // TPWMTHRS - Sets the switching speed threshold based on TSTEP from stealthChop to spreadCycle mode
#define TMC2130_TPWMTHRS_E 403      // Switch extruder from StealthChop to SpreadCycle at around 900mm/min
#define TMC2130_THIGH     0         // THIGH - unused

//#define TMC2130_TCOOLTHRS_X 450       // TCOOLTHRS - coolstep treshold
//#define TMC2130_TCOOLTHRS_Y 450       // TCOOLTHRS - coolstep treshold
#define TMC2130_TCOOLTHRS_X 430       // TCOOLTHRS - coolstep treshold
#define TMC2130_TCOOLTHRS_Y 430       // TCOOLTHRS - coolstep treshold
#define TMC2130_TCOOLTHRS_Z 500       // TCOOLTHRS - coolstep treshold
#define TMC2130_TCOOLTHRS_E 500       // TCOOLTHRS - coolstep treshold

#define TMC2130_SG_HOMING       1     // stallguard homing
#define TMC2130_SG_THRS_X       3     // stallguard sensitivity for X axis
#define TMC2130_SG_THRS_Y       3     // stallguard sensitivity for Y axis
#define TMC2130_SG_THRS_Z       4     // stallguard sensitivity for Z axis
#define TMC2130_SG_THRS_E       3     // stallguard sensitivity for E axis
#define TMC2130_SG_THRS_HOME {3, 3, TMC2130_SG_THRS_Z, TMC2130_SG_THRS_E}

//new settings is possible for vsense = 1, running current value > 31 set vsense to zero and shift both currents by 1 bit right (Z axis only)
#define TMC2130_CURRENTS_H {21, 21, 35, 30}  // default holding currents for all axes
#define TMC2130_CURRENTS_FARM 36             // E 805 mA peak for ECool/farm mode
#define TMC2130_CURRENTS_R {21, 21, 35, 30}  // default running currents for all axes
#define TMC2130_CURRENTS_R_HOME {11, 11, 20, 18}  // homing running currents for all axes

#define TMC2130_STEALTH_Z
#define TMC2130_DEDGE_STEPPING

//#define TMC2130_SERVICE_CODES_M910_M918

//#define TMC2130_DEBUG
//#define TMC2130_DEBUG_WR
//#define TMC2130_DEBUG_RD

/*------------------------------------
 EXTRUDER SETTINGS
 *------------------------------------*/

// Mintemps
#define HEATER_0_MINTEMP 10 //default 10
#define HEATER_1_MINTEMP 5 //default 5
#define HEATER_2_MINTEMP 5 //default 5
#define HEATER_MINTEMP_DELAY 15000                // [ms] ! if changed, check maximal allowed value @ ShortTimer
#if HEATER_MINTEMP_DELAY>USHRT_MAX
#error "Check maximal allowed value @ ShortTimer (see HEATER_MINTEMP_DELAY definition)"
#endif
#define BED_MINTEMP 10 //default 10
#define BED_MINTEMP_DELAY 50000                   // [ms] ! if changed, check maximal allowed value @ ShortTimer
#if BED_MINTEMP_DELAY>USHRT_MAX
#error "Check maximal allowed value @ ShortTimer (see BED_MINTEMP_DELAY definition)"
#endif
#define SUPERPINDA_SUPPORT
#define PINDA_MINTEMP 10
//#define PINDA_TEMP_COMP //Used to enable SuperPINDA toggle menu/function
#define AMBIENT_MINTEMP -30

// Maxtemps
#if defined(E3D_PT100_EXTRUDER_WITH_AMP) || defined(E3D_PT100_EXTRUDER_NO_AMP)
#define HEATER_0_MAXTEMP 410
#else
#define HEATER_0_MAXTEMP 305  //Should be 305C
#endif
#define HEATER_1_MAXTEMP 305  //Should be 305C
#define HEATER_2_MAXTEMP 305  //Should be 305C
#define BED_MAXTEMP 125       //Should be 125C
#define AMBIENT_MAXTEMP 100   //Should be 100C

#if defined(E3D_PT100_EXTRUDER_WITH_AMP) || defined(E3D_PT100_EXTRUDER_NO_AMP)
// Define PID constants for extruder with PT100
#define  DEFAULT_Kp 21.70
#define  DEFAULT_Ki 1.60
#define  DEFAULT_Kd 73.76
#else
// Define PID constants for extruder
//#define  DEFAULT_Kp 40.925
//#define  DEFAULT_Ki 4.875
//#define  DEFAULT_Kd 86.085
#define  DEFAULT_Kp 16.13
#define  DEFAULT_Ki 1.1625
#define  DEFAULT_Kd 56.23
#endif

// Extrude mintemp
#define EXTRUDE_MINTEMP 175

// Extruder cooling fans
#define EXTRUDER_0_AUTO_FAN_PIN   8
#define EXTRUDER_1_AUTO_FAN_PIN   -1
#define EXTRUDER_2_AUTO_FAN_PIN   -1
#define EXTRUDER_AUTO_FAN_TEMPERATURE 50
#define EXTRUDER_AUTO_FAN_SPEED   255  // == full speed
//#define EXTRUDER_ALTFAN_DETECT
#define EXTRUDER_ALTFAN_SPEED_SILENT 128

#define FANCHECK_AUTO_PRINT_FAN_THRS 70 //[RPS] - Used during selftest to identify swapped fans automatically
#define FANCHECK_AUTO_FAIL_THRS 20 //[RPS] - Used during selftest to identify a faulty fan

/*------------------------------------
 LOAD/UNLOAD FILAMENT SETTINGS
 *------------------------------------*/

// Load filament commands
#define LOAD_FILAMENT_0 "M83"
#define LOAD_FILAMENT_1 "G1 E70 F400"
#define LOAD_FILAMENT_2 "G1 E40 F100"

// Unload filament commands
#define UNLOAD_FILAMENT_0 "M83"
#define UNLOAD_FILAMENT_1 "G1 E-80 F7000"

/*------------------------------------
 CHANGE FILAMENT SETTINGS
 *------------------------------------*/

// Filament change configuration
#define FILAMENTCHANGEENABLE
#ifdef FILAMENTCHANGEENABLE
#define FILAMENTCHANGE_XPOS 211
#define FILAMENTCHANGE_YPOS 0
#define FILAMENTCHANGE_ZADD 2
#define FILAMENTCHANGE_FIRSTRETRACT -2
#define FILAMENTCHANGE_FINALRETRACT -80

#define FILAMENTCHANGE_FIRSTFEED 70 //E distance in mm for fast filament loading sequence used used in filament change (M600)
#define FILAMENTCHANGE_FINALFEED 25 //E distance in mm for slow filament loading sequence used used in filament change (M600) and filament load (M701) 
#define FILAMENTCHANGE_RECFEED 5

#define FILAMENTCHANGE_XYFEED 50
#define FILAMENTCHANGE_EFEED_FIRST 20 // feedrate in mm/s for fast filament loading sequence used in filament change (M600)
#define FILAMENTCHANGE_EFEED_FINAL 3.3f // feedrate in mm/s for slow filament loading sequence used in filament change (M600) and filament load (M701) 
//#define FILAMENTCHANGE_RFEED 400
#define FILAMENTCHANGE_RFEED 7000 / 60
#define FILAMENTCHANGE_EXFEED 2
#define FILAMENTCHANGE_ZFEED 15

#endif

/*------------------------------------
 ADDITIONAL FEATURES SETTINGS
 *------------------------------------*/

//#define HEATER_0_USES_THERMISTOR_DIFF_10X_GAIN // NT104GT-2 thermistor is used, diff input with a 44Ohm ref load at TEMP1
#ifdef HEATER_0_USES_THERMISTOR_DIFF_10X_GAIN // NT104GT-2 thermistor is used, diff input with a 44Ohm ref load at TEMP1

#define DIFFERENTIAL_ADC_CHANNEL_IDX 0
#define DIFFERENTIAL_ADC_GAIN_FACTOR 10   // 10x gain
#define DIFFERENTIAL_ADC_RANGE (DIFFERENTIAL_ADC_GAIN_FACTOR*511) // Gain * ( 2^(10-1) - 1) Sign bit offsets range by 511
#define DIFFERENTIAL_ADC_VOLTAGE_DIVIDER_RESISTORS 4700.0 // Ohm  TODO: Calibrate value
#define DIFFERENTIAL_ADC_REFERENCE_RESISTOR 103000.0 // Ohm   TODO: Calibrate value
#define DIFFERENTIAL_ADC_REFERENCE_RESISTOR_RATIO (DIFFERENTIAL_ADC_REFERENCE_RESISTOR/(DIFFERENTIAL_ADC_REFERENCE_RESISTOR + DIFFERENTIAL_ADC_VOLTAGE_DIVIDER_RESISTORS))
// Steinhart-Hart equation coefficients. Note: These coefficients are calculated for one unique thermistor!
#define A_ 0.0007324574939808130000
#define B_ 0.0002225367713550080000
#define C_ 0.0000000444219939579289
/* Steinhart-Hart equation coefficients. Note: These coefficients are calculated from  /
   Semitec's 104NT-4-R025H42G datasheet, and can be used if you are not able to get    /
   accurate data of your thermistor R/T characteristics.                              */
// #define A_ 0.0007980877654663700000
// #define B_ 0.0002132200991990680000

// #define C_ 0.0000000662784840710222
#endif //   HEATER_0_USES_THERMISTOR_DIFF_10X_GAIN


#define HEATER_0_USES_PT1000_DIFF_10X_GAIN 1048 // PT1000 TRD is used, diff input with a 150Ohm ref load at TEMP1
#ifdef HEATER_0_USES_PT1000_DIFF_10X_GAIN // PT1000 TRD is used, diff input with a 150Ohm ref load at TEMP1

#define DIFFERENTIAL_ADC_CHANNEL_IDX 9
#define DIFFERENTIAL_ADC_GAIN_FACTOR 10.0   // 10x gain
#define DIFFERENTIAL_ADC_RANGE 497.0 // ( 2^(10-1) - 1) Sign bit offsets range by 511
#define DIFFERENTIAL_ADC_V 4.985
#define DIFFERENTIAL_ADC_V_REF (DIFFERENTIAL_ADC_V * (DIFFERENTIAL_ADC_REFERENCE_RESISTOR_RATIO))
#define DIFFERENTIAL_ADC_VOLTAGE_DIVIDER_RESISTOR_PRT 4676.17 // Ohm, Calibrated value
#define DIFFERENTIAL_ADC_VOLTAGE_DIVIDER_RESISTOR_REF 4687.155 // Ohm, Calibrated value
#define DIFFERENTIAL_ADC_REFERENCE_RESISTOR 1472.0 // Ohm, Calibrated value
#define DIFFERENTIAL_ADC_REFERENCE_RESISTOR_RATIO (DIFFERENTIAL_ADC_REFERENCE_RESISTOR/(DIFFERENTIAL_ADC_REFERENCE_RESISTOR + DIFFERENTIAL_ADC_VOLTAGE_DIVIDER_RESISTOR_REF))
#define PT1000_R0 996.4 // Ohm at 0'C

// Callendar-Van Dusen equation coefficients. Note: These coefficients are calculated for one unique PRT!
// PRT(t) = PRT(0) * (1 + A*t + B*t^2) --> t = -U_ + SQRT(U^2 - ((1 - PRT(t)/PRT(0))/B_))
#define A_ 0.00362217590085969
#define B_ 0.00000126792831799859
#define U_ ((DIFFERENTIAL_ADC_V / 10) * (A_ / B_))
#define UU_ (U_ * U_)
#define W_ (U_ * PT1000_R0)
#endif //   HEATER_0_USES_PT1000_DIFF_10X_GAIN

// Define Prusa filament runout sensor
#define FILAMENT_RUNOUT_SUPPORT
#ifdef FILAMENT_RUNOUT_SUPPORT
#define FILAMENT_RUNOUT_SENSOR 1
#endif

// temperature runaway
#define TEMP_RUNAWAY_BED_HYSTERESIS 5
#define TEMP_RUNAWAY_BED_TIMEOUT 360

#define TEMP_RUNAWAY_EXTRUDER_HYSTERESIS 15
#define TEMP_RUNAWAY_EXTRUDER_TIMEOUT 45

// model-based temperature check
#define TEMP_MODEL 1          // enable model-based temperature checks
#define TEMP_MODEL_DEBUG 1    // extended runtime logging

#define TEMP_MODEL_P 38.      // heater power (W)

#define TEMP_MODEL_C 12.1     // initial guess for heatblock capacitance (J/K)
#define TEMP_MODEL_Cl 5       // C estimation lower limit
#define TEMP_MODEL_Ch 20      // C estimation upper limit
#define TEMP_MODEL_C_thr 0.01 // C estimation iteration threshold
#define TEMP_MODEL_C_itr 30   // C estimation iteration limit

#define TEMP_MODEL_R 20.5     // initial guess for heatblock resistance (K/W)
#define TEMP_MODEL_Rl 5       // R estimation lower limit
#define TEMP_MODEL_Rh 50      // R estimation upper limit
#define TEMP_MODEL_R_thr 0.01 // R estimation iteration threshold
#define TEMP_MODEL_R_itr 30   // R estimation iteration limit

#define TEMP_MODEL_Ta_corr -7 // Default ambient temperature correction
#define TEMP_MODEL_LAG 2.1    // Temperature transport delay (s)

#define TEMP_MODEL_W 1.2      // Default warning threshold (K/s)
#define TEMP_MODEL_E 1.74     // Default error threshold (K/s)

#define TEMP_MODEL_CAL_Th 230 // Default calibration working temperature (C)
#define TEMP_MODEL_CAL_Tl 50  // Default calibration cooling temperature (C)

/*------------------------------------
 MOTOR CURRENT SETTINGS
 *------------------------------------*/

// Motor Current settings for Einsy/tmc = 0..63
#define MOTOR_CURRENT_PWM_RANGE 63

/*------------------------------------
 BED SETTINGS
 *------------------------------------*/

// Define Mesh Bed Leveling system to enable it
#define MESH_BED_LEVELING
#ifdef MESH_BED_LEVELING

#define MBL_Z_STEP 0.01

// Mesh upsample definition
#define MESH_NUM_X_POINTS 7
#define MESH_NUM_Y_POINTS 7
// Mesh measure definition
#define MESH_MEAS_NUM_X_POINTS 3
#define MESH_MEAS_NUM_Y_POINTS 3

// Maximum bed level correction value
#define BED_ADJUSTMENT_UM_MAX 100
#endif //MESH_BED_LEVELING

// Bed Temperature Control
// Select PID or bang-bang with PIDTEMPBED. If bang-bang, BED_LIMIT_SWITCHING will enable hysteresis
//
// Uncomment this to enable PID on the bed. It uses the same frequency PWM as the extruder.
// If your PID_dT above is the default, and correct for your hardware/configuration, that means 7.689Hz,
// which is fine for driving a square wave into a resistive load and does not significantly impact you FET heating.
// This also works fine on a Fotek SSR-10DA Solid State Relay into a 250W heater.
// If your configuration is significantly different than this and you don't understand the issues involved, you probably
// shouldn't use bed PID until someone else verifies your hardware works.
// If this is enabled, find your own PID constants below.
#define PIDTEMPBED
//
//#define BED_LIMIT_SWITCHING

// This sets the max power delivered to the bed, and replaces the HEATER_BED_DUTY_CYCLE_DIVIDER option.
// all forms of bed control obey this (PID, bang-bang, bang-bang with hysteresis)
// setting this to anything other than 255 enables a form of PWM to the bed just like HEATER_BED_DUTY_CYCLE_DIVIDER did,
// so you shouldn't use it unless you are OK with PWM on your bed.  (see the comment on enabling PIDTEMPBED)
#define MAX_BED_POWER 255 // limits duty cycle to bed; 255=full current

// Bed temperature compensation settings
#define BED_OFFSET 10
#define BED_OFFSET_START 40
#define BED_OFFSET_CENTER 50

#ifdef PIDTEMPBED
//120v 250W silicone heater into 4mm borosilicate (MendelMax 1.5+)
//from FOPDT model - kp=.39 Tp=405 Tdead=66, Tc set to 79.2, aggressive factor of .15 (vs .1, 1, 10)
#if defined(E3D_PT100_BED_WITH_AMP) || defined(E3D_PT100_BED_NO_AMP)
// Define PID constants for extruder with PT100
#define  DEFAULT_bedKp 21.70
#define  DEFAULT_bedKi 1.60
#define  DEFAULT_bedKd 73.76
#else
#define  DEFAULT_bedKp 126.13
#define  DEFAULT_bedKi 4.30
#define  DEFAULT_bedKd 924.76
#endif


// FIND YOUR OWN: "M303 E-1 C8 S90" to run autotune on the bed at 90 degreesC for 8 cycles.
#endif // PIDTEMPBED

//connect message when communication with monitoring broken
//#define FARM_CONNECT_MESSAGE

/*-----------------------------------
 PREHEAT SETTINGS
 *------------------------------------*/

#define FARM_PREHEAT_HOTEND_TEMP 250
#define FARM_PREHEAT_HPB_TEMP 80

#define PLA_PREHEAT_HOTEND_TEMP 215
#define PLA_PREHEAT_HPB_TEMP 60

#define PVB_PREHEAT_HOTEND_TEMP 215
#define PVB_PREHEAT_HPB_TEMP 75

#define ASA_PREHEAT_HOTEND_TEMP 260
#define ASA_PREHEAT_HPB_TEMP 105

#define PC_PREHEAT_HOTEND_TEMP 275
#define PC_PREHEAT_HPB_TEMP 110

#define ABS_PREHEAT_HOTEND_TEMP 255
#define ABS_PREHEAT_HPB_TEMP 100

#define HIPS_PREHEAT_HOTEND_TEMP 220
#define HIPS_PREHEAT_HPB_TEMP 100

#define PP_PREHEAT_HOTEND_TEMP 254
#define PP_PREHEAT_HPB_TEMP 100

#define PET_PREHEAT_HOTEND_TEMP 230
#define PET_PREHEAT_HPB_TEMP 85

#define FLEX_PREHEAT_HOTEND_TEMP 240
#define FLEX_PREHEAT_HPB_TEMP 50

/*------------------------------------
 THERMISTORS SETTINGS
 *------------------------------------*/

//
//--NORMAL IS 4.7kohm PULLUP!-- 1kohm pullup can be used on hotend sensor, using correct resistor and table
//
//// Temperature sensor settings:
// -2 is thermocouple with MAX6675 (only for sensor 0)
// -1 is thermocouple with AD595
// 0 is not used
// 1 is 100k thermistor - best choice for EPCOS 100k (4.7k pullup)
// 2 is 200k thermistor - ATC Semitec 204GT-2 (4.7k pullup)
// 3 is Mendel-parts thermistor (4.7k pullup)
// 4 is 10k thermistor !! do not use it for a hotend. It gives bad resolution at high temp. !!
// 5 is 100K thermistor - ATC Semitec 104GT-2 (Used in ParCan & J-Head) (4.7k pullup)
// 6 is 100k EPCOS - Not as accurate as table 1 (created using a fluke thermocouple) (4.7k pullup)
// 7 is 100k Honeywell thermistor 135-104LAG-J01 (4.7k pullup)
// 71 is 100k Honeywell thermistor 135-104LAF-J01 (4.7k pullup)
// 8 is 100k 0603 SMD Vishay NTCS0603E3104FXT (4.7k pullup)
// 9 is 100k GE Sensing AL03006-58.2K-97-G1 (4.7k pullup)
// 10 is 100k RS thermistor 198-961 (4.7k pullup)
// 11 is 100k beta 3950 1% thermistor (4.7k pullup)
// 12 is 100k 0603 SMD Vishay NTCS0603E3104FXT (4.7k pullup) (calibrated for Makibox hot bed)
// 13 is 100k Hisens 3950  1% up to 300°C for hotend "Simple ONE " & "Hotend "All In ONE"
// 20 is the PT100 circuit found in the Ultimainboard V2.x
// 60 is 100k Maker's Tool Works Kapton Bed Thermistor beta=3950
//
//    1k ohm pullup tables - This is not normal, you would have to have changed out your 4.7k for 1k
//                          (but gives greater accuracy and more stable PID)
// 51 is 100k thermistor - EPCOS (1k pullup)
// 52 is 200k thermistor - ATC Semitec 204GT-2 (1k pullup)
// 55 is 100k thermistor - ATC Semitec 104GT-2 (Used in ParCan & J-Head) (1k pullup)
//
// 1047 is Pt1000 with 4k7 pullup
// 1010 is Pt1000 with 1k pullup (non standard)
// 147 is Pt100 with 4k7 pullup
// 148 is E3D Pt100 with 4k7 pullup and no PT100 Amplifier on a MiniRambo 1.3a
// 247 is Pt100 with 4k7 pullup and PT100 Amplifier
// 110 is Pt100 with 1k pullup (non standard)
// 111 is NT104GT-2 with 4k7 pullup, configured as a whetstone bridge with a 640R as a reference across the TEMP1 port
// 1048 is Pt1000 with 4k7 pullup, configured as a whetstone bridge with a 1500R as a reference across the TEMP1 port


#if defined(E3D_PT100_EXTRUDER_WITH_AMP)
#  define TEMP_SENSOR_0 247
#elif defined(E3D_PT100_EXTRUDER_NO_AMP)
#  define TEMP_SENSOR_0 148
#elif defined(HEATER_0_USES_PT1000_DIFF_10X_GAIN)
#  define TEMP_SENSOR_0 HEATER_0_USES_PT1000_DIFF_10X_GAIN
#else
#  define TEMP_SENSOR_0 5
#endif
#define TEMP_SENSOR_1 0
#define TEMP_SENSOR_2 0
#if defined(E3D_PT100_BED_WITH_AMP)
#  define TEMP_SENSOR_BED 247
#elif defined(E3D_PT100_BED_NO_AMP)
#  define TEMP_SENSOR_BED 148
#else
#  define TEMP_SENSOR_BED 1
#endif
#define TEMP_SENSOR_PINDA 1
#define TEMP_SENSOR_AMBIENT 2000

#define STACK_GUARD_TEST_VALUE 0xA2A2
#define STACK_GUARD_MARGIN     32

#define MAX_BED_TEMP_CALIBRATION 50
#define MAX_HOTEND_TEMP_CALIBRATION 50

#define MAX_E_STEPS_PER_UNIT 250
#define MIN_E_STEPS_PER_UNIT 100

#define Z_BABYSTEP_MIN -3999
#define Z_BABYSTEP_MAX 0

#define PINDA_PREHEAT_X 20
#define PINDA_PREHEAT_Y 60
#define PINDA_PREHEAT_Z 0.15
/*
#define PINDA_PREHEAT_X 70
#define PINDA_PREHEAT_Y -3
#define PINDA_PREHEAT_Z 1*/
#define PINDA_HEAT_T 120 //time in s

#define PINDA_MIN_T 50
#define PINDA_STEP_T 10
#define PINDA_MAX_T 100

#define PING_TIME 60 //time in s
#define PING_TIME_LONG 600 //10 min; used when length of commands buffer > 0 to avoid 0 triggering when dealing with long gcodes
#define PING_ALLERT_PERIOD 60 //time in s

#define NC_TIME 10 //time in s for periodic important status messages sending which needs reponse from monitoring
#define NC_BUTTON_LONG_PRESS 15 //time in s

#define LONG_PRESS_TIME 1000 //time in ms for button long press
#define BUTTON_BLANKING_TIME 200 //time in ms for blanking after button release

#define DEFAULT_PID_TEMP 210

#define MIN_PRINT_FAN_SPEED 50

// How much shall the print head be lifted on power panic?
// Ideally the Z axis will reach a zero phase of the stepper driver on power outage. To simplify this,
// UVLO_Z_AXIS_SHIFT shall be an integer multiply of the stepper driver cycle, that is 4x full step.
// For example, the Prusa i3 MK2 with 16 microsteps per full step has Z stepping of 400 microsteps per mm.
// At 400 microsteps per mm, a full step lifts the Z axis by 0.04mm, and a stepper driver cycle is 0.16mm.
// The following example, 12 * (4 * 16 / 400) = 12 * 0.16mm = 1.92mm.
//#define UVLO_Z_AXIS_SHIFT 1.92
#define UVLO_Z_AXIS_SHIFT 0.64
// When powered off during PP recovery, the Z axis position can still be re-adjusted. In this case
// we just need to shift to the nearest fullstep, but we need a move which is at least
// "dropsegments" steps long. All the above rules still need to apply.
#define UVLO_TINY_Z_AXIS_SHIFT 0.16
// If power panic occured, and the current temperature is higher then target temperature before interrupt minus this offset, print will be recovered automatically.
#define AUTOMATIC_UVLO_BED_TEMP_OFFSET 5 

#define HEATBED_V2

#define M600_TIMEOUT 600  //seconds

#define SUPPORT_VERBOSITY

#define MMU_FILAMENT_COUNT 5

#define MMU_REQUIRED_FW_BUILDNR 83
#define MMU_HWRESET
#define MMU_DEBUG //print communication between MMU2 and printer on serial
#define MMU_HAS_CUTTER

// This is experimental feature requested by our test department.
// There is no known use for ordinary user. If enabled by this macro
// and enabled from printer menu (not enabled by default). It cuts filament
// every time when switching filament from gcode. MMU_HAS_CUTTER needs to be
// defined.

//#define MMU_ALWAYS_CUT
#define MMU_IDLER_SENSOR_ATTEMPTS_NR 21 //max. number of attempts to load filament if first load failed; value for max bowden length and case when loading fails right at the beginning

// Default Arc Interpolation Settings (Now configurable via M214)
#define DEFAULT_N_ARC_CORRECTION       25 // Number of interpolated segments between corrections.
/* A value of 1 or less for N_ARC_CORRECTION will trigger the use of Sin and Cos for every arc, which will improve accuracy at the
   cost of performance*/
#define DEFAULT_MM_PER_ARC_SEGMENT     1.0f // REQUIRED - The enforced maximum length of an arc segment
#define DEFAULT_MIN_MM_PER_ARC_SEGMENT 0.5f //the enforced minimum length of an interpolated segment
   /*  MIN_MM_PER_ARC_SEGMENT Must be smaller than MM_PER_ARC_SEGMENT.  Only has an effect if MIN_ARC_SEGMENTS > 0
       or ARC_SEGMENTS_PER_SEC > 0 .  If both MIN_ARC_SEGMENTS and ARC_SEGMENTS_PER_SEC is defined, the minimum
       calculated segment length is used. */
#define DEFAULT_MIN_ARC_SEGMENTS 20 // The enforced minimum segments in a full circle of the same radius.  Set to 0 to disable
#define DEFAULT_ARC_SEGMENTS_PER_SEC 0 // Use feedrate to choose segment length. Set to 0 to disable

#endif //__CONFIGURATION_PRUSA_H
