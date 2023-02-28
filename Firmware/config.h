#ifndef _CONFIG_H
#define _CONFIG_H


#include "Configuration_prusa.h"
#include "pins.h"
#include <avr/io.h>
#include <stdint.h>

#if (defined(VOLT_IR_PIN) && defined(IR_SENSOR))
// TODO: IR_SENSOR_ANALOG currently disabled as being incompatible with the new thermal regulation
// # define IR_SENSOR_ANALOG
#endif

//ADC configuration
#ifndef IR_SENSOR_ANALOG
#define ADC_CHAN_MSK      0b0000001000000100 // TODO: defaultmask0b0000001001011111 -> used AD channels bit mask (0,1,2,3,4,6,9) 
#define ADC_DIDR_MSK      0b0000000001011111 //AD channels DIDR mask (1 ~ disabled digital input) decoupled pin mas from adc channel mask 
#define ADC_CHAN_CNT      10         //number of used channels


#if !defined(HEATER_0_USES_PT1000_DIFF_10X_GAIN)  // HEATER_0_USES_PT1000_DIFF_10X_GAIN
  #if defined(TEMP_0_PIN) && (TEMP_0_PIN > -1) // TEMP_0_PIN
    #if (TEMP_0_PIN & (0x7 << MUX3))  // ADC8+
      #define TEMP_0_CHN ((1 << 5)) + (TEMP_0_PIN & 0x7))
    #else 
      #define TEMP_0_CHN TEMP_0_PIN
    #endif //ADC8+
    #define TEMP_0_IDX 0
  #endif // TEMP_0_PIN

  #if defined(TEMP_1_PIN) && (TEMP_1_PIN > -1) // TEMP_1_PIN
    #if (TEMP_1_PIN & (0x7 << MUX3))  // ADC8+
      #define TEMP_1_CHN ((1 << 5) + (TEMP_1_PIN & 0x7))
    #else 
      #define TEMP_1_CHN TEMP_1_PIN
    #endif //ADC8+
    #define TEMP_1_IDX 1
  #endif // TEMP_1_PIN
#else
  #define TEMP_0_CHN (0x09)
  #define TEMP_0_IDX 0
#endif  // HEATER_0_USES_PT1000_DIFF_10X_GAIN

#if defined(TEMP_2_PIN) && (TEMP_2_PIN > -1) // TEMP_2_PIN
  #if (TEMP_2_PIN & (0x7 << MUX3))  // ADC8+
    #define TEMP_2_CHN ((1 << 5) + (TEMP_2_PIN & 0x7))
  #else 
    #define TEMP_2_CHN TEMP_2_PIN
  #endif //ADC8+
  #define TEMP_2_IDX 2
#endif // TEMP_2_PIN 

#if (defined(TEMP_BED_PIN) && (TEMP_BED_PIN > -1)) // TEMP_BED_PIN //TODO: 2 becomes 10 !? --> = TEMP_BED_PIN + 4    / (1 << 3)
  #if (TEMP_BED_PIN & (0x7 << MUX3))  // ADC8+
    #define TEMP_BED_CHN ((1 << 5)) + (TEMP_BED_PIN & 0x7))
  #else 
    #define TEMP_BED_CHN TEMP_BED_PIN
  #endif //ADC8+
    #define TEMP_BED_IDX 3
#endif // TEMP_BED_PIN

#if defined(TEMP_AMBIENT_PIN) && (TEMP_AMBIENT_PIN > -1) // TEMP_AMBIENT_PIN
  #if (TEMP_AMBIENT_PIN & (0x7 << MUX3))  // ADC8+
    #define TEMP_AMBIENT_CHN ((1 << 5) + (TEMP_AMBIENT_PIN & 0x7))
  #else 
    #define TEMP_AMBIENT_CHN TEMP_AMBIENT_PIN
  #endif //ADC8+
  #define TEMP_AMBIENT_IDX 4
#endif // TEMP_AMBIENT_PIN

#if defined(TEMP_PINDA_PIN) && (TEMP_PINDA_PIN > -1) // TEMP_PINDA_PIN
  #if (TEMP_PINDA_PIN & (0x7 << MUX3))  // ADC8+
    #define TEMP_PINDA_CHN ((1 << 5) + (TEMP_PINDA_PIN & 0x7))
  #else 
    #define TEMP_PINDA_CHN TEMP_PINDA_PIN
  #endif //ADC8+
  #define TEMP_PINDA_IDX 5  
#endif // TEMP_PINDA_PIN

#if defined(VOLT_PWR_PIN) && (VOLT_PWR_PIN > -1) // VOLT_PWR_PIN
  #if (VOLT_PWR_PIN & (0x7 << MUX3))  // ADC8+
    #define VOLT_PWR_CHN ((1 << 5) + (VOLT_PWR_PIN & 0x7))
  #else 
    #define VOLT_PWR_CHN VOLT_PWR_PIN
  #endif //ADC8+
  #define VOLT_PWR_IDX 6
#endif // VOLT_PWR_PIN

#if defined(VOLT_BED_PIN) && (VOLT_BED_PIN > -1) // VOLT_BED_PIN
  #if (VOLT_BED_PIN & (0x7 << MUX3))  // ADC8+
    #define VOLT_BED_CHN ((1 << 5) + (VOLT_BED_PIN & 0x7))
  #else 
    #define VOLT_BED_CHN VOLT_BED_PIN
  #endif //ADC8+
  #define VOLT_BED_IDX 7
#endif // VOLT_BED_PIN

#if defined(VOLT_IR_PIN) && (VOLT_IR_PIN > -1) // VOLT_IR_PIN
  #if (VOLT_IR_PIN &(0x7 << MUX3))  // ADC8+
    #define VOLT_IR_CHN ((1 << 5) + (VOLT_IR_PIN & 0x7))
  #else 
    #define VOLT_IR_CHN VOLT_IR_PIN
  #endif //ADC8+
  #define VOLT_IR_IDX 8
#endif // VOLT_IR_PIN

#else //!IR_SENSOR_ANALOG
#define ADC_CHAN_MSK      0b0000001101011111 //used AD channels bit mask (0,1,2,3,4,6,8,9)
#define ADC_DIDR_MSK      0b0000001001011111 //AD channels DIDR mask (1 ~ disabled digital input)
#define ADC_CHAN_CNT      8         //number of used channels)
#endif //!IR_SENSOR_ANALOG
#define ADC_OVRSAMPL      16        //oversampling multiplier
#define ADC_CALLBACK      adc_callback //callback function ()

//SWI2C configuration
//#define SWI2C_SDA         20 //SDA on P3
//#define SWI2C_SCL         21 //SCL on P3
#define SWI2C_A8
#define SWI2C_DEL         20 //2us clock delay
#define SWI2C_TMO         2048 //2048 cycles timeout

//PAT9125 configuration
//#define PAT9125_SWSPI // software SPI mode (incomplete)
#ifdef SWI2C_SCL
#define PAT9125_SWI2C   // software I2C mode
#else
#define PAT9125_I2C     // hardware I2C mode
#endif

#define PAT9125_I2C_ADDR  0x75  //ID=LO
//#define PAT9125_I2C_ADDR  0x79  //ID=HI
//#define PAT9125_I2C_ADDR  0x73  //ID=NC
#define PAT9125_XRES      0
#define PAT9125_YRES      240                   // maximum resolution (5*X cpi)
#define PAT9124_YRES_MM   (5*PAT9125_YRES/25.4) // counts per mm

//SM4 configuration
#define SM4_DEFDELAY      500       //default step delay [us]

//TMC2130 - Trinamic stepper driver
//pinout - hardcoded
//spi:
#define TMC2130_SPI_RATE       0 // fosc/4 = 4MHz
#define TMC2130_SPCR           SPI_SPCR(TMC2130_SPI_RATE, 1, 1, 1, 0)
#define TMC2130_SPSR           SPI_SPSR(TMC2130_SPI_RATE)

//LANG - Multi-language support
//#define LANG_MODE              0 // primary language only
#define LANG_MODE              0 // sec. language support

#define LANG_SIZE_RESERVED     0x3000 // reserved space for secondary language (12288 bytes).
                                      // 0x3D00 Maximum 15616 bytes as it depends on xflash_layout.h
                                      // 16 Languages max. per group including stock 

#if (LANG_SIZE_RESERVED % 256)
  #error "LANG_SIZE_RESERVED should be a multiple of a page size"
#endif

//Community language support
#define COMMUNITY_LANG_GROUP 1

#if (COMMUNITY_LANG_GROUP == 1)
#define COMMUNITY_LANG_GROUP1_NL // Community Dutch language
#define COMMUNITY_LANG_GROUP1_RO // Community Romanian language
#define COMMUNITY_LANG_GROUP1_HU // Community Hungarian language
#define COMMUNITY_LANG_GROUP1_HR // Community Croatian language
#define COMMUNITY_LANG_GROUP1_SK // Community Slovak language
#define COMMUNITY_LANG_GROUP1_SV // Community Swedish language
#define COMMUNITY_LANG_GROUP1_NO // Community Norwegian language
//#define COMMUNITY_LANG_GROUP1_DA // Community Danish language
//#define COMMUNITY_LANG_GROUP1_SL // Community Slovanian language
//#define COMMUNITY_LANG_GROUP1_LB // Community Luxembourgish language
#endif //COMMUNITY_LANG_GROUP 1

#if (COMMUNITY_LANG_GROUP == 2)
#define COMMUNITY_LANG_GROUP2_LT // Community Lithuanian language
//#define COMMUNITY_LANG_GROUP1_QR // Community new language //..use this as a template and replace 'QR'
#endif //COMMUNITY_LANG_GROUP 2

#if (COMMUNITY_LANG_GROUP >=1 )
#define COMMUNITY_LANGUAGE_SUPPORT
#endif

// Sanity checks for correct configuration of XFLASH_DUMP options
#if defined(XFLASH_DUMP) && !defined(XFLASH)
#error "XFLASH_DUMP requires XFLASH support"
#endif
#if (defined(MENU_DUMP) || defined(EMERGENCY_DUMP)) && !defined(XFLASH_DUMP)
#error "MENU_DUMP and EMERGENCY_DUMP require XFLASH_DUMP"
#endif

// Support for serial dumps is mutually exclusive with XFLASH_DUMP features
#if defined(EMERGENCY_DUMP) && defined(EMERGENCY_SERIAL_DUMP)
#error "EMERGENCY_DUMP and EMERGENCY_SERIAL_DUMP are mutually exclusive"
#endif
#if defined(MENU_DUMP) && defined(MENU_SERIAL_DUMP)
#error "MENU_DUMP and MENU_SERIAL_DUMP are mutually exclusive"
#endif

// Reduce internal duplication
#if defined(EMERGENCY_DUMP) || defined(EMERGENCY_SERIAL_DUMP)
#define EMERGENCY_HANDLERS
#endif

//FARM_MODE
#if ( LANG_MODE == 0 ) && defined(XFLASH) //Save resources on EINSY and disable FARM_MODE on multi-language version
#define PRUSA_FARM
#endif //PRUSA_FARM only in english on EINSYs
#ifndef XFLASH //enable FARM_MODE on miniRAMBo boards
#define PRUSA_FARM
#endif
#endif //_CONFIG_H
