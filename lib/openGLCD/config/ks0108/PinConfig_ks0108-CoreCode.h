/*
 * ks0108_CoreCode.h - User specific configuration for openGLCD library
 *
 * Use this file to set io pins
 * This pinconfig file used when running in Arduino CoreCode mode
 *
 */

#ifndef GLCD_PIN_CONFIG_H
#define GLCD_PIN_CONFIG_H

/*
 * define name for pin configuration
 */
#define glcd_PinConfigName "ks0108-CoreCode"

/*********************************************************/
/*  Configuration for assigning LCD bits to Arduino Pins */
/*********************************************************/

/*
 * Pins can be assigned using Arduino pin numbers 0-n
 * On AVR processors,
 * Pins can also be assigned using PIN_Pb
 *    where P is port A-L and b is bit 0-7
 *    Example: port D bit 3 is PIN_D3
 *
 */

/* Data pin definitions
 */
#define glcdPinData0 4
#define glcdPinData1 16
#define glcdPinData2 17
#define glcdPinData3 18
#define glcdPinData4 19
#define glcdPinData5 21
#define glcdPinData6 22
#define glcdPinData7 23

/* Arduino pins used for Control
 * default assignment uses the first five analog pins
 */
#define glcdPinCSEL1 25
#define glcdPinCSEL2 26

#if NBR_CHIP_SELECT_PINS > 2
#define glcdPinCSEL3 2
#endif
#if NBR_CHIP_SELECT_PINS > 3
#define glcdPinCSEL4 5
#endif

#define glcdPinRW 27
#define glcdPinDI 32
#define glcdPinEN 33
// Reset  - uncomment the next line if glcd module reset is connected to an Arduino pin
#define glcdPinRES 5 // optional s/w Reset control

// #define glcdPinBL	XX // optional backlight control pin controls BL circuit

#endif // GLCD_PIN_CONFIG_H