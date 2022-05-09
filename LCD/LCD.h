 /******************************************************************************
 * Module: LCD
 * File Name: LCD.h
 * Description: Header file for the LCD driver
 * Author: Mohannad Ragab Afifi
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "common_macros.h"
#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* Data bits mode configuration (4 or 8) */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port (if want to use lower 4 bits undef UPPER_PORT_PINS) */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

//#undef UPPER_PORT_PINS		/* Use lower 4 bits in the data port*/

/* LCD HW Pins [Needs modification] */
#define RS PC2						/* Register select: select command register or data register */
#define RW PC1						/* Read mode RW = 1, write mode RW = 0 */
#define E  PC3
#define LCD_CTRL_PORT PORTC
#define LCD_CTRL_PORT_DIR DDRC

#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C						/* Display on, cursor off */
#define CURSOR_ON 0x0E						/* Display on, cursor blinking */
#define SET_CURSOR_LOCATION 0x80

#define SHIFT_CURSOR_TO_LEFT 0x04
#define SHIFT_CURSOR_TO_RIGHT 0x06
#define SHIFT_DISPLAY_RIGHT 0x05
#define SHIFT_DISPLAY_LEFT 0x07
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(int data);

#endif /* LCD_H_ */
