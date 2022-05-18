/******************************************************************************
 * Module:		KEYPAD
 * File Name:	Keypad.c
 * Description:	Source file for the KEYPAD TM4C123GH6PM (Tiva c) driver
 * Created on:	May 10, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#include "keypad.h"
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "App.h"

/*******************************************************************************
 *                          File GLobal Variables                              *
 *******************************************************************************/
/* Array of 4x4 to define characters which will be printe on specific key pressed */
unsigned char symbol[N_row][N_col] = {{'1', '2', '3', 'A'},
									  {'4', '5', '6', 'B'},
									  {'7', '8', '9', 'C'},
									  {'*', '0', '#', 'D'}};

/*******************************************************************************
 *                       Local Functions Definitions                           *
 *******************************************************************************/
/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(uint32 n)
{
	uint32 i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3180; j++)
		{
		} /* do nothing for 1 ms */
}

/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/
/************************************************************************************
* Function Name: keypad_Init
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Initialize keypad Module.
************************************************************************************/
void keypad_Init(void)
{
	// 0001 0100 -> 00FE DCBA
	/* Enable clock for PORTC & PORTE and allow time for clock to start - portf for leds */
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= ((1<<KEYPAD_ROW_PORT_MASK) | (1<<KEYPAD_COL_PORT_MASK)); //0x00000014 in case of portE for row and portC for column
	delay = SYSCTL_REGCGC2_REG;
	// while ((SYSCTL_REGCGC2_REG & 0x00000014) == 0); /* Wait untill clock is enabled */

#ifdef ROW_UPPER_PORT_PINS						/* Check if Row pins connected to (0,1,2,3)PINS or (4,5,6,7)PINS */
	// Row pins configuratuion as output digital pins (highest 4)
	/* Disable Analog on Row pins (highest 4) */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= 0x0F;
	/* Clear PMCx bits for Row pins (highest 4) to use it as GPIO pins */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_CTL_REG_OFFSET))) &= 0x0000FFFF;
	/* Configure Row pins (highest 4) as output pins */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_DIR_REG_OFFSET))) |= 0xF0;
	/* Disable alternative function on Row pins (highest 4) */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= 0x0F;
	/* Enable Digital I/O on Row pins (highest 4) */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= 0xF0;
#else
	// Row pins configuratuion as output digital pins (lowest 4)
	/* Disable Analog on Row pins (lowest 4) */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= 0xF0;
	/* Clear PMCx bits for Row pins (lowest 4) to use it as GPIO pins */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_CTL_REG_OFFSET))) &= 0xFFFF0000;
	/* Configure Row pins (lowest 4) as output pins */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_DIR_REG_OFFSET))) |= 0x0F;
	/* Disable alternative function on Row pins (lowest 4) */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= 0xF0;
	/* Enable Digital I/O on Row pins (lowest 4) */
	(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= 0x0F;
#endif
#ifdef COL_UPPER_PORT_PINS						/* Check if column pins connected to (0,1,2,3)PINS or (4,5,6,7)PINS */
	// column pins configuratuion as input digital pins (highest 4)
	/* Disable Analog on column pins (highest 4) */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= 0x0F;
	/* Clear PMCx bits for column pins (highest 4) to use it as GPIO pins */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_CTL_REG_OFFSET))) &= 0x0000FFFF;
	/* Configure column pins (highest 4) as input pins */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_DIR_REG_OFFSET))) &= 0x0F;
	/* Disable alternative function on column pins (highest 4) */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= 0x0F;
	/* Enable Digital I/O on column pins (highest 4) */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= 0xF0;
	/* Enable pull down resistors on column pins (highest 4) */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_PULL_DOWN_REG_OFFSET))) |= 0xF0;
#else
	// column pins configuratuion as input digital pins (lowest 4)
	/* Disable Analog on column pins (lowest 4) */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= 0xF0;
	/* Clear PMCx bits for column pins (lowest 4) to use it as GPIO pins */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_CTL_REG_OFFSET))) &= 0xFFFF0000;
	/* Configure column pins (lowest 4) as input pins */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_DIR_REG_OFFSET))) &= 0xF0;
	/* Disable alternative function on column pins (lowest 4) */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= 0xF0;
	/* Enable Digital I/O on column pins (lowest 4) */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= 0x0F;
	/* Enable pull down resistors on column pins (lowest 4) */
	(*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_PULL_DOWN_REG_OFFSET))) |= 0x0F;
#endif
}

/************************************************************************************
* Function Name: KeyPad_getPressedKey
* Parameters (in): None
* Parameters (out): symbol[j][i] (uint8)
* Return value: symbol[j][i] (uint8)
* Description: Function responsible for getting the pressed keypad key.
************************************************************************************/
uint8 KeyPad_getPressedKey(void)
{
	while (1)
	{
		for (uint16 j = 0; j < 4; j++)
		{
			// Apply 3.3 v (Digital Output) on keypad rows on-by-one
			(*((volatile uint32 *)(KEYPAD_ROW_PORT + PORT_DATA_REG_OFFSET))) = (0x01 << j);
			// GPIO_PORTE_DATA_REG = (0x01 << j);
			for (uint16 i = 0; i < 4; i++)
			{
				// Digital read for any key pressed on keypad -- GPIO_PORTC_DATA_REG
				if (((*((volatile uint32 *)(KEYPAD_COL_PORT + PORT_DATA_REG_OFFSET))) & 0xF0) == (0x10 << i))
				{
					return symbol[j][i];
				}
			}
		}
		if (start_cooking_flag == 1)
		{
			return 'E';
		}
		delayMs(10);
	}
}
