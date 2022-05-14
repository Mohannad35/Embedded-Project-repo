/******************************************************************************
 * Module: 		LCD
 * File Name: 	LCD.c
 * Description: Source file for the LCD driver (TM4C123GH6PM (Tiva c))
 * Created on:	May 10, 2022
 * Author: 		Mohannad Ragab Afifi
 *******************************************************************************/
#include "LCD.h"

/* Array of 4x4 to define characters which will be printe on specific key pressed */
unsigned char num_symbol[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{
	// 0000 1001 -> 00FE DCBA
	/* Enable clock for PORTA & PORTD and allow time for clock to start */
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= ((1 << LCD_CTRL_PORT_MASK) | (1 << LCD_DATA_PORT_MASK)); // 0x00000009 in case of portA for ctrl and portD for data
	delay = SYSCTL_REGCGC2_REG;
	// while ((SYSCTL_REGCGC2_REG & 0x00000014) == 0); /* Wait untill clock is enabled */

	// RS, RW, E pins configuratuion as output digital pins
	/* Disable Analog on RS, RW, and E */
	(*((volatile uint32 *)(LCD_CTRL_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= ~((1 << E) | (1 << RS) | (1 << RW)); // 0x1F
	/* Clear PMCx bits for RS, RW, and E to use it as GPIO pins */
	(*((volatile uint32 *)(LCD_CTRL_PORT + PORT_CTL_REG_OFFSET))) &= ~(((0xF << (E * 4)) | (0xF << (RS * 4)) | (0xF << (RW * 4)))); // 0x000FFFFF
	/* Configure RS, RW, and E as output pins */
	(*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DIR_REG_OFFSET))) |= ((1 << E) | (1 << RS) | (1 << RW)); // 0xE0
	/* Disable alternative function on RS, RW, and E */
	(*((volatile uint32 *)(LCD_CTRL_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= ~((1 << E) | (1 << RS) | (1 << RW)); // 0x1F
	/* Enable Digital I/O on RS, RW, and E */
	(*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= ((1 << E) | (1 << RS) | (1 << RW)); // 0xE0

#if (DATA_BITS_MODE == 4) /* Check mode of LCD if 8 or 4 */
#ifdef UPPER_PORT_PINS	  /* Check if LCD connected to (0,1,2,3)PINS or (4,5,6,7)PINS */
	// LCD_DATA_PORT_DIR |= 0xF0;				/* The highest 4 bits of the data port -> output pins */

	// Data pins configuratuion as output digital pins (highest 4)
	/* Disable Analog on Data pins (highest 4) */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= 0x0F;
	/* Clear PMCx bits for Data pins (highest 4) to use it as GPIO pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_CTL_REG_OFFSET))) &= 0x0000FFFF;
	/* Configure Data pins (highest 4) as output pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DIR_REG_OFFSET))) |= 0xF0;
	/* Disable alternative function on Data pins (highest 4) */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= 0x0F;
	/* Enable Digital I/O on Data pins (highest 4) */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= 0xF0;

#else
	// LCD_DATA_PORT_DIR |= 0x0F;				/* The lowest 4 bits of the data port -> output pins */

	// Data pins configuratuion as output digital pins (lowest 4)
	/* Disable Analog on Data pins (lowest 4) */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= 0xF0;
	/* Clear PMCx bits for Data pins (lowest 4) to use it as GPIO pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_CTL_REG_OFFSET))) &= 0xFFFF0000;
	/* Configure Data pins (lowest 4) as output pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DIR_REG_OFFSET))) |= 0x0F;
	/* Disable alternative function on Data pins (lowest 4) */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= 0xF0;
	/* Enable Digital I/O on Data pins (lowest 4) */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= 0x0F;

#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE);		 /* Initialize LCD 4-bit mode */
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* Use 2-line LCD + 4-bit Data Mode + 5*7 dot display Mode */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT_DIR = 0xFF; /* Data port -> output port */

	// Data pins configuratuion as output digital pins
	/* Disable Analog on Data pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= 0x00;
	/* Clear PMCx bits for Data pins to use it as GPIO pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_CTL_REG_OFFSET))) &= 0x00000000;
	/* Configure Data pins as output pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DIR_REG_OFFSET))) |= 0xFF;
	/* Disable alternative function on Data pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= 0x00;
	/* Enable Digital I/O on Data pins */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= 0xFF;

	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);								  /* Use 2-line LCD + 8-bit Data Mode + 5*7 dot display Mode */
#endif

	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND); /* Clear LCD at the beginning */
}

void LCD_sendCommand(uint8 command)
{

	/* Clear bits Data pins (lowest 4) in Data regsiter */
	// (*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET)))  &= 0xF0;

	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), RS); /* Command Mode RS=0 */
	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), RW); /* Write data (RW=0) */
	delay_Ms(1);																   /* Delay for processing Tas = 50ns */
	SET_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E);	   /* Enable LCD E=1 */
	delay_Ms(1);																   /* delay for processing Tpw - Tdws = 190ns */

#if (DATA_BITS_MODE == 4) /* 4-bits mode */
						  /* In 4 bit mode we send the higher 4 bits of the command first then the lower */
						  /* Out the highest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = ((*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) & 0x0F) | (command & 0xF0);
#else
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = ((*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) & 0xF0) | ((command & 0xF0) >> 4);
#endif

	delay_Ms(1);																  /* Delay for processing Tdsw = 100ns */
	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E); /* Disable LCD E=0 */
	delay_Ms(1);																  /* Delay for processing Th = 13ns */
	SET_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E);	  /* Enable LCD E=1 */
	delay_Ms(1);																  /* Delay for processing Tpw - Tdws = 190ns */

	/* Out the lowest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = ((*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) & 0x0F) | ((command & 0x0F) << 4);
#else
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = ((*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) & 0xF0) | (command & 0x0F);
#endif
	delay_Ms(1);																  /* Delay for processing Tdsw = 100ns */
	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E); /* Disable LCD E=0 */
	delay_Ms(1);																  /* Delay for processing Th = 13ns */

#elif (DATA_BITS_MODE == 8) /* 8-bits mode */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = command;	  /* Out the required command to the data bus D0 --> D7 */
	_delay_ms(1);																  /* Delay for processing Tdsw = 100ns */
	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E); /* Disable LCD E=0 */
	_delay_ms(1);																  /* Delay for processing Th = 13ns */
#endif
}

void LCD_displayCharacter(uint8 data)
{
	SET_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), RS);   /* Data Mode RS=1 */
	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), RW); /* Write mode RW=0 */
	delay_Ms(1);																   /* Delay for processing Tas = 50ns */
	SET_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E);	   /* Enable LCD E=1 */
	delay_Ms(1);																   /* Delay for processing Tpw - Tdws = 190ns */

#if (DATA_BITS_MODE == 4) /* 4-bits mode */
						  /* Out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = ((*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) & 0x0F) | (data & 0xF0);
#else
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = ((*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) & 0xF0) | ((data & 0xF0) >> 4);
#endif

	delay_Ms(1);																  /* Delay for processing Tdsw = 100ns */
	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E); /* Disable LCD E=0 */
	delay_Ms(1);																  /* Delay for processing Th = 13ns */
	SET_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E);	  /* Enable LCD E=1 */
	delay_Ms(1);																  /* Delay for processing Tpw - Tdws = 190ns */

	/* Out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = ((*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) & 0x0F) | ((data & 0x0F) << 4);
#else
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = ((*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) & 0xF0) | (data & 0x0F);
#endif

	delay_Ms(1);																  /* Delay for processing Tdsw = 100ns */
	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E); /* Disable LCD E=0 */
	delay_Ms(1);																  /* Delay for processing Th = 13ns */

#elif (DATA_BITS_MODE == 8) /* 8-bits mode */
	(*((volatile uint32 *)(LCD_DATA_PORT + PORT_DATA_REG_OFFSET))) = data;		  /* Out the data to the data bus D0 --> D7 */
	_delay_ms(1);																  /* Delay for processing Tdsw = 100ns */
	CLEAR_BIT((*((volatile uint32 *)(LCD_CTRL_PORT + PORT_DATA_REG_OFFSET))), E); /* Disable LCD E=0 */
	_delay_ms(1);																  /* Delay for processing Th = 13ns */
#endif
}

void LCD_displayString(const char *Str)
{
	/* The idea is to display the characters of the string one by one */
	uint8 i = 0;
	while (Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8 row, uint8 col)
{
	uint8 Address;

	/* first of all calculate the required address */
	switch (row)
	{
	case 0:
		Address = col;
		break;
	case 1:
		Address = col + 0x40;
		break;
	case 2:
		Address = col + 0x10;
		break;
	case 3:
		Address = col + 0x50;
		break;
	}
	/* To write to a specific address in the LCD
	 * We need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *Str)
{
	LCD_goToRowColumn(row, col); /* Go to to the required LCD position */
	LCD_displayString(Str);		 /* Display the string */
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); /* Clear display */
}

void LCD_displayCounter(uint32 n_second)
{
	// 		  0				    0 		  :		    0			     0
	// mins_second_digit mins_first_digit : secs_second_digit secs_first_digit
	uint32 mins = n_second / 60;
	uint32 secs = n_second % 60;
	uint32 mins_first_digit = mins % 10;
	uint32 mins_second_digit = mins / 10;
	uint32 secs_first_digit = secs % 10;
	uint32 secs_second_digit = secs / 10;
	// LCD_goToRowColumn(0, 0);
	LCD_clearScreen();
	LCD_displayCharacter(num_symbol[mins_second_digit]);
	LCD_displayCharacter(num_symbol[mins_first_digit]);
	LCD_displayCharacter(':');
	LCD_displayCharacter(num_symbol[secs_second_digit]);
	LCD_displayCharacter(num_symbol[secs_first_digit]);
}

void delay_Ms(uint32 n)
{
	uint32 i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3180; j++)
		{
		} /* do nothing for 1 ms */
}