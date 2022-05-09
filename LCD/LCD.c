 /******************************************************************************
 * Module: LCD
 * File Name: LCD.c
 * Description: Source file for the LCD driver
 * Author: Mohannad Ragab Afifi
 *******************************************************************************/

#include "LCD.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void) {
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);	/* Control pins(E,RS,RW) -> output pins */

#if (DATA_BITS_MODE == 4)					/* Check mode of LCD if 8 or 4 */
#ifdef UPPER_PORT_PINS						/* Check if LCD connected to (0,1,2,3)PINS or (4,5,6,7)PINS */
	LCD_DATA_PORT_DIR |= 0xF0;				/* The highest 4 bits of the data port -> output pins */
#else
	LCD_DATA_PORT_DIR |= 0x0F;				/* The lowest 4 bits of the data port -> output pins */
#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE);			/* Initialize LCD 4-bit mode */
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);	/* Use 2-line LCD + 4-bit Data Mode + 5*7 dot display Mode */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT_DIR = 0xFF;						/* Data port -> output port */
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);	/* Use 2-line LCD + 8-bit Data Mode + 5*7 dot display Mode */
#endif

	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);		/* Clear LCD at the beginning */
}

void LCD_sendCommand(uint8 command) {
	CLEAR_BIT(LCD_CTRL_PORT,RS);		/* Command Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW);		/* Write data (RW=0) */
	_delay_ms(1);						/* Delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E);			/* Enable LCD E=1 */
	_delay_ms(1);						/* delay for processing Tpw - Tdws = 190ns */

#if (DATA_BITS_MODE == 4)				/* 4-bits mode */
	/* In 4 bit mode we send the higher 4 bits of the command first then the lower */
	/* Out the highest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif

	_delay_ms(1);					/* Delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);		/* Disable LCD E=0 */
	_delay_ms(1);					/* Delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E);		/* Enable LCD E=1 */
	_delay_ms(1);					/* Delay for processing Tpw - Tdws = 190ns */

	/* Out the lowest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif
	_delay_ms(1);					/* Delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);		/* Disable LCD E=0 */
	_delay_ms(1);					/* Delay for processing Th = 13ns */

#elif (DATA_BITS_MODE == 8)			/* 8-bits mode */
	LCD_DATA_PORT = command;		/* Out the required command to the data bus D0 --> D7 */
	_delay_ms(1);					/* Delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);		/* Disable LCD E=0 */
	_delay_ms(1);					/* Delay for processing Th = 13ns */
#endif
}

void LCD_displayCharacter(uint8 data) {
	SET_BIT(LCD_CTRL_PORT,RS);		/* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT,RW);	/* Write mode RW=0 */
	_delay_ms(1);					/* Delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E);		/* Enable LCD E=1 */
	_delay_ms(1);					/* Delay for processing Tpw - Tdws = 190ns */

#if (DATA_BITS_MODE == 4)			/* 4-bits mode */
	/* Out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif

	_delay_ms(1);					/* Delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);		/* Disable LCD E=0 */
	_delay_ms(1);					/* Delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E);		/* Enable LCD E=1 */
	_delay_ms(1);					/* Delay for processing Tpw - Tdws = 190ns */

	/* Out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif

	_delay_ms(1);					/* Delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);		/* Disable LCD E=0 */
	_delay_ms(1);					/* Delay for processing Th = 13ns */

#elif (DATA_BITS_MODE == 8)			/* 8-bits mode */
	LCD_DATA_PORT = data;			/* Out the data to the data bus D0 --> D7 */
	_delay_ms(1); 					/* Delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E);		/* Disable LCD E=0 */
	_delay_ms(1);					/* Delay for processing Th = 13ns */
#endif
}

void LCD_displayString(const char *Str) {
	/* The idea is to display the characters of the string one by one */
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8 row,uint8 col) {
	uint8 Address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address = col;
				break;
		case 1:
				Address = col+0x40;
				break;
		case 2:
				Address = col+0x10;
				break;
		case 3:
				Address = col+0x50;
				break;
	}
	/* To write to a specific address in the LCD
	 * We need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str) {
	LCD_goToRowColumn(row,col);		/* Go to to the required LCD position */
	LCD_displayString(Str);			/* Display the string */
}

void LCD_intgerToString(int data) {
   char buff[16];					/* String to hold the ascii result */
   itoa(data,buff,10);				/* 10 for decimal */
   LCD_displayString(buff);
}

void LCD_clearScreen(void) {
	LCD_sendCommand(CLEAR_COMMAND);	/* Clear display */
}
