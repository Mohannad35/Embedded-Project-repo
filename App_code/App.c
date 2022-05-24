/******************************************************************************
 * Module:		App
 * File Name:	App.c
 * Description:	Source file for App module TM4C123GH6PM (Tiva c)
 * Created on:	May 15, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#include "App.h"
#include "keypad.h"
#include "LCD.h"
#include "LED_SW.h"
#include "systick.h"
#include "std_types.h"
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                          File GLobal Variables                              *
 *******************************************************************************/
/* Global variable to determine the number of systick interrupt (number of seconds) */
volatile uint32 ticks_num = 0;

uint8 key_Value, Beef_weight = 0, Chicken_weight = 0, CookingTime_digit = 0, CookingTime_cur_Pos = 0;
uint16 CookingTime_total[4] = {0}, Total_cooking = 0;

/* initialize with 5 at first so we make 0 when we start counting */
uint8 first_stop_flag = 5, second_stop_flag = 5;
uint8 start_cooking_flag = 5, clear_cooking_flag = 5;

/*******************************************************************************
 *                       Local Functions Definitions                           *
 *******************************************************************************/
/************************************************************************************
* Private Function
* Function Name: string_to_int
* Parameters (in): ch
* Parameters (out): uint16 value
* Return value: uint16 value
* Description: Func to convert numbers from keypad which in form of string to integers.
************************************************************************************/
uint16 string_to_int(uint8 ch)
{
	switch (ch)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	}
	return -1;
}

/*******************************************************************************
 *                 Interrupt Handler Functions Definitions                     *
 *******************************************************************************/
/************************************************************************************
* Function Name: SysTick_Handler
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: SysTick Timer Interrupt Handler ... No need to clear the trigger flag
* 			   (COUNT) bit ... it cleared automatically by the HW.
************************************************************************************/
void SysTick_Handler(void)
{
	ticks_num--; /* increment the number of ticks */
	LCD_displayCounter(ticks_num);
}

/************************************************************************************
* Function Name: GPIOPortF_Handler
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: GPIO PortF Interrupt Handler. (for Stop and start switches)
************************************************************************************/
void GPIOPortF_Handler(void)
{
	if (Read_STOP_SW())
	{
		/* Clear Trigger flag for SW1 (Interupt Flag) */
    	(*((volatile uint32 *)(SW_PORT + PORT_ICR_OFFSET)))   |= (1<<SW1_PIN);

		/* STOP button pressed for 1st time */
		if (first_stop_flag == 0)
		{
			first_stop_flag = 1;
			second_stop_flag = 5;
			SysTick_Disable();
		}
		/* STOP button pressed for 2nd time */
		else if (first_stop_flag == 1)
		{
			first_stop_flag = 5;
			second_stop_flag = 1;
			LED_OFF();
			SysTick_Disable();
			ticks_num = 0;
		}

		if (clear_cooking_flag == 0)
		{
			CookingTime_cur_Pos = 0;
			LCD_displayStringRowColumn(0, 0, "Cooking Time?");
			LCD_displayStringRowColumn(1, 0, "00:00");
		}
	}
	/* START button pressed */
	else if (Read_START_SW())
	{
		/* Clear Trigger flag for SW2 (Interupt Flag) */
    	(*((volatile uint32 *)(SW_PORT + PORT_ICR_OFFSET)))   |= (1<<SW2_PIN);

		if (first_stop_flag == 1)
		{
			second_stop_flag = 5;
			first_stop_flag = 0;
			LED_ON();
			SysTick_Enable();
		}
		if (start_cooking_flag == 0)
		{
			// LED_ON();
			start_cooking_flag = 1;
		}
	}
}

/************************************************************************************
* Function Name: GPIOPortA_Handler
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: GPIO PortA Interrupt Handler. (for Door latch)
************************************************************************************/
void GPIOPortA_Handler(void)
{
	while (BIT_IS_SET((*((volatile uint32 *)(Door_SW_PORT + PORT_RIS_OFFSET))), SW3_PIN))
	{
		LED_TOGGLE();
		for (uint16 i = 0; i < 100; i++)
		{
			Delay_MS(10);
			if (BIT_IS_CLEAR((*((volatile uint32 *)(Door_SW_PORT + PORT_RIS_OFFSET))), SW3_PIN))
			{
				LED_OFF();
				break;
			}
		}
	}
}

/*******************************************************************************
 *                       Global Functions Definitions                          *
 *******************************************************************************/
/************************************************************************************
* Function Name: Delay_MS
* Parameters (in): n
* Parameters (out): None
* Return value: None
* Description: Delay n milliseconds.
************************************************************************************/
void Delay_MS(unsigned long long n)
{
	volatile unsigned long long count = 0;
	while (count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n))
		;
}

/************************************************************************************
* Function Name: Init_Task
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task executes once to initialize all the Modules.
************************************************************************************/
void Init_Task(void)
{
	/* Enable clock for PORT A,B,C,D,E,F and allow time for clock to start*/
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= 0x0000003F;
	delay = SYSCTL_REGCGC2_REG;

	/* Initailize the LCD as GPIO Pins */
	LCD_init();
	LCD_clearScreen();
	LCD_displayString("Initializing...");
	/* Initailize the SW1 and SW2 as GPIO Pins */
	SWs_init();
	/* Initailize the SW3 as GPIO Pin */
	Door_SW_init();
	/* Initailize the LEDs as GPIO Pins */
	Leds_Init();
	/* Initailize the Buzzer as GPIO Pin */
	Buzzer_Init();
	/* Initailize the Keypad as GPIO Pins */
	keypad_Init();
	/* Initalize the SysTick Timer to generate an interrupt every 1 second */
	SysTick_Init();
	/* Disable timer till we need it */
	SysTick_Disable();
	Delay_MS(500);
	LCD_clearScreen();
	LCD_displayString("A B C D");
}

/************************************************************************************
* Function Name: Popcorn_Task
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task executes When 'A' button is pressed on the keypad.
************************************************************************************/
void Popcorn_Task(void)
{
	LCD_clearScreen();
	/* Display "Popcorn" on lcd for 2 secs */
	LCD_displayString("Popcorn");
	Delay_MS(2000);
	Counter_Task(60);
}

/************************************************************************************
* Function Name: Beef_Task
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task executes When 'B' button is pressed on the keypad.
************************************************************************************/
void Beef_Task(void)
{
	Beef_weight = 0;
	do
	{
		LCD_clearScreen();
		/* Display “Beef weight?” and wait for keypad input */
		LCD_displayString("Beef weight?");
		Beef_weight = KeyPad_getPressedKey();
		if ((Beef_weight < '1') || (Beef_weight > '9'))
		{
			LCD_clearScreen();
			LCD_displayString("Err");
			Delay_MS(2000);
		}
	} while ((Beef_weight < '1') || (Beef_weight > '9'));
	LCD_clearScreen();
	LCD_displayCharacter(Beef_weight);
	Delay_MS(2000);
	Beef_weight = string_to_int(Beef_weight);
	Counter_Task(30 * Beef_weight); // 0.5 per min
}

/************************************************************************************
* Function Name: Chicken_Task
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task executes When 'C' button is pressed on the keypad.
************************************************************************************/
void Chicken_Task(void)
{
	Chicken_weight = 0;
	do
	{
		LCD_clearScreen();
		/* Display “Chicken weight?” and wait for keypad input */
		LCD_displayString("Chicken weight?");
		Chicken_weight = KeyPad_getPressedKey();
		if ((Chicken_weight < '1') || (Chicken_weight > '9'))
		{
			LCD_clearScreen();
			LCD_displayString("Err");
			Delay_MS(2000);
		}
	} while ((Chicken_weight < '1') || (Chicken_weight > '9'));
	LCD_clearScreen();
	LCD_displayCharacter(Chicken_weight);
	Delay_MS(2000);
	Chicken_weight = string_to_int(Chicken_weight);
	Counter_Task(12 * Chicken_weight); // 0.2 per min
}

/************************************************************************************
* Function Name: Cooking_Time_Task
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task executes When 'D' button is pressed on the keypad.
************************************************************************************/
void Cooking_Time_Task(void)
{
	/* total time that will be sent to be displayed on the LCD */
	Total_cooking = 0;
	/* Cursor position to be used when entering the input time from keypad to be displayed on the LCD */
	CookingTime_cur_Pos = 0;
	/* the current input digit from the keypad */
	CookingTime_digit = 0;
	/* array to store the input digits (chars) from the keypad to operate on it later */
	CookingTime_total[0] = '0', CookingTime_total[1] = '0', CookingTime_total[2] = '0', CookingTime_total[3] = '0';
	
	LCD_clearScreen();
	/* Display “Cooking Time?” and wait for keypad input */
	LCD_displayStringRowColumn(0, 0, "Cooking Time?");
	LCD_displayStringRowColumn(1, 0, "00:00");
	/* flag that will be set by stop switch interrupt handler to indicate LCD clear */
	clear_cooking_flag = 0;
	/* flag that will be set by start switch interrupt handler to indicate start operating */
	start_cooking_flag = 0;
	do
	{
		/* Check if we done entering the 4 digits so we are waiting for the start switch to be pressed
		 * and also not taking any more input from keypad */
		if (CookingTime_cur_Pos < 4)
		{
			/* get input from keypad */
			CookingTime_digit = KeyPad_getPressedKey();
			/* if the start switch is pressed while waiting for input from the keypad it will return 'E'
			 * so we done entering input and go right to the operating state and countdown what have been entered */
			if (CookingTime_digit != 'E')
			{
				/* check for a non numeric char */
				if ((CookingTime_digit < '0') || (CookingTime_digit > '9'))
				{
					CookingTime_cur_Pos = 0;
					LCD_clearScreen();
					LCD_displayString("Err");
					Delay_MS(2000);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Cooking Time?");
					LCD_displayStringRowColumn(1, 0, "00:00");
				}
				else
				{
					CookingTime_cur_Pos += 1;
					/* store the entered digits so far in their right place for further calculation for total time */
					switch (CookingTime_cur_Pos)
					{
					case 2:
						CookingTime_total[2] = CookingTime_total[3];
						break;
					case 3:
						CookingTime_total[1] = CookingTime_total[2];
						CookingTime_total[2] = CookingTime_total[3];
						break;
					case 4:
						CookingTime_total[0] = CookingTime_total[1];
						CookingTime_total[1] = CookingTime_total[2];
						CookingTime_total[2] = CookingTime_total[3];
						break;
					default:
						break;
					}
					CookingTime_total[3] = CookingTime_digit;
					/* display what have been entered so far on the LCD */
					for (uint8 i = 0, j = 0; j < CookingTime_cur_Pos; i++, j++)
					{
						if (i == 2)
						{
							i += 1;
						}
						LCD_goToRowColumn(1, (4 - i));
						LCD_displayCharacter(CookingTime_total[3 - j]);
					}
					Delay_MS(400);
				}
			}
			if ((CookingTime_total[0] > '2') || (CookingTime_total[2] > '5'))
			{
				if ((CookingTime_total[0] == '3') && ((CookingTime_total[1] > '0')||(CookingTime_total[2] > '0')||(CookingTime_total[3] > '0')))
				{
					/* reset all variables */
					Total_cooking = 0;
					CookingTime_cur_Pos = 0;
					CookingTime_digit = 0;
					CookingTime_total[0] = '0', CookingTime_total[1] = '0', CookingTime_total[2] = '0', CookingTime_total[3] = '0';

					Delay_MS(500);
					LCD_clearScreen();
					LCD_displayString("MAX time Err");
					Delay_MS(2000);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Cooking Time?");
					LCD_displayStringRowColumn(1, 0, "00:00");
				}
			}
			if ((CookingTime_total[2] > '5') && (CookingTime_digit == 'E'))
			{
				/* reset all variables */
				Total_cooking = 0;
				CookingTime_cur_Pos = 0;
				CookingTime_digit = 0;
				CookingTime_total[0] = '0', CookingTime_total[1] = '0', CookingTime_total[2] = '0', CookingTime_total[3] = '0';

				Delay_MS(500);
				LCD_clearScreen();
				LCD_displayString("Input Err");
				Delay_MS(2000);
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Cooking Time?");
				LCD_displayStringRowColumn(1, 0, "00:00");

				start_cooking_flag = 0;
			}
		}
	} while (start_cooking_flag == 0);
	clear_cooking_flag = 5;
	start_cooking_flag = 5;
	// Delay_MS(1000);
	LCD_clearScreen();
	Total_cooking = string_to_int(CookingTime_total[0]) * 600 +
					string_to_int(CookingTime_total[1]) * 60 +
					string_to_int(CookingTime_total[2]) * 10 +
					string_to_int(CookingTime_total[3]) * 1;
	Counter_Task(Total_cooking);
}

/************************************************************************************
* Function Name: Counter_Task
* Parameters (in): n_seconds
* Parameters (out): None
* Return value: None
* Description: Task executes to count down from n_seconds to zero on LCD.
************************************************************************************/
void Counter_Task(uint32 n_seconds)
{
	ticks_num = n_seconds;
	first_stop_flag = 0;
	SysTick_Enable();
	LED_ON();
	LCD_displayCounter(n_seconds);
	while (ticks_num > 0)
	{
		if ((first_stop_flag == 1) && (second_stop_flag == 5))
		{
			LED_TOGGLE();
			Delay_MS(1000);
		}
	}
	SysTick_Disable();
	LED_OFF();
	LCD_clearScreen();
	if (second_stop_flag == 1)
	{
		second_stop_flag = 5;
		first_stop_flag = 5;
		ticks_num = 0;
		LCD_displayString("Stopped!");
		Delay_MS(2000);
		LCD_clearScreen();
		LCD_displayString("A B C D");
	}
	else
	{
		second_stop_flag = 5;
		first_stop_flag = 5;
		ticks_num = 0;
		LCD_displayString("Done!");
		// array of leds blink 3 times for 3 secs
		for (uint8 i = 0; i < 3; i++)
		{
			LED_ON();
			BUZZER_ON();
			Delay_MS(3000);
			LED_OFF();
			BUZZER_OFF();
			Delay_MS(3000);
		}
		LCD_clearScreen();
		LCD_displayString("A B C D");
	}
}
