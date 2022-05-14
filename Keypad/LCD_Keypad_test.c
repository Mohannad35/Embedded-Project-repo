/******************************************************************************
 * Module:		LCD_Keypad_test
 * File Name:	LCD_Keypad_test.c
 * Description:	Source file for testing LCD keybad connection TM4C123GH6PM (Tiva c)
 * Created on:	May 10, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/

#include "LCD.h"
#include "keypad.h"
#include "tm4c123gh6pm_registers.h" /* include register definition file of TM4C123GH6PM */

/* keypad pins */
/*
R1 PE0
R2 PE1
R3 PE2
R4 PE3
C1 PC4
C2 PC5
C3 PC6
C4 PC7
*/
/* LCD pins */
/*
RS	PA5
RW	PA6
E	PA7
D	PD0
D	PD1
D	PD2
D	PD3
*/

/* Main function calls LCD and keypad initialization functions */
int main()
{
	keypad_Init(); // Initialize keypad and TM4C123 GPIO pins
	LCD_init();
	LCD_clearScreen();
	LCD_displayString("Welcome");
	LCD_displayStringRowColumn(1, 0,"00:01");
	// leds init
//	GPIO_PORTF_AMSEL_REG &= 0xF1;         /* Disable Analog on PF1, PF2 and PF3 */
//    GPIO_PORTF_PCTL_REG  &= 0xFFFF000F;   /* Clear PMCx bits for PF1, PF2 and PF3 to use it as GPIO pin */
//    GPIO_PORTF_DIR_REG   |= 0x0E;         /* Configure PF1, PF2 and PF3 as output pin */
//    GPIO_PORTF_AFSEL_REG &= 0xF1;         /* Disable alternative function on PF1, PF2 and PF3 */
//    GPIO_PORTF_DEN_REG   |= 0x0E;         /* Enable Digital I/O on PF1, PF2 and PF3 */
//    GPIO_PORTF_DATA_REG  &= 0xF1;         /* Clear bit 0, 1 and 2 in Data regsiter to turn off the leds */
	while (1)
	{
		// GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disbale the others */
		char value = KeyPad_getPressedKey(); // get the key pressed value
                if (value != 0)
                {
					LCD_clearScreen();
					LCD_displayString("Keypad Value:");
					LCD_goToRowColumn(1, 0);
					LCD_displayCharacter(value);
                  // GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disbale the others */
                }
		delayMs(400);				  // delay of one second
	}
}
