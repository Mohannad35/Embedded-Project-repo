#include "systick.h"
#include "LCD.h"
#include "keypad.h"
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "LED_SW.h"

/* Global variable to determine the number of systick interrupt (number of seconds) */
volatile uint32 ticks_num = 0;

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762
void Delay_MS(unsigned long long n)
{
	volatile unsigned long long count = 0;
	while (count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n))
		;
}

/* SysTick Timer ISR ... No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
void SysTick_Handler(void)
{
	ticks_num--; /* increment the number of ticks */
	LCD_displayCounter(ticks_num);
}

/* GPIO PORTF External Interrupt - ISR */
void GPIOPortF_Handler(void)
{
	if (BIT_IS_SET(GPIO_PORTF_ICR_REG, 0))
	{
		GPIO_PORTF_DATA_REG  |= (1<<1);       /* Red LED ON*/
    	GPIO_PORTF_ICR_REG   |= (1<<0);       /* Clear Trigger flag for PF4 (Interupt Flag) */
	}
	else if (BIT_IS_SET(GPIO_PORTF_ICR_REG, 4))
	{
		GPIO_PORTF_DATA_REG  |= (1<<2);       /* Blue LED ON*/
    	GPIO_PORTF_ICR_REG   |= (1<<4);       /* Clear Trigger flag for PF4 (Interupt Flag) */
	}
	
    
}

/* Count down from n_seconds to 00:00 */
void App_Counter(uint32 n_seconds)
{
	ticks_num = n_seconds;
	SysTick_Enable();
	while (ticks_num > 0)
		;
	SysTick_Disable();
	// ticks_num = 0;
	// array of leds blink 3 times for 3 secs
}

/* Simple func to convert numbers from keypad which in form of string to integers */
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

// switch (cook_time_flag)
// 					{
// 					// 10*60 60 : 10 1               600 60 : 10 1
// 					case 1:
// 						Cooking_Time_total += (string_to_int(Cooking_Time_digit) * 600);
// 						break;
// 					case 2:
// 						Cooking_Time_total += (string_to_int(Cooking_Time_digit) * 60);
// 						break;
// 					case 3:
// 						Cooking_Time_total += (string_to_int(Cooking_Time_digit) * 10);
// 						break;
// 					case 4:
// 						Cooking_Time_total += (string_to_int(Cooking_Time_digit) * 1);
// 						break;
// 					}

int main()
{
	/* Enable clock for PORT A,B,C,D,E,F and allow time for clock to start*/
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= 0x0000003F;
	delay = SYSCTL_REGCGC2_REG;

	/* Initailize the LEDs as GPIO Pins */
	Leds_Init();
	/* Initailize the SW1 and SW2 as GPIO Pins */
	SWs_init();
	/* Initailize the Keypad as GPIO Pins */
	keypad_Init();
	/* Initailize the LCD as GPIO Pins */
	LCD_init();
	LCD_clearScreen();
	LCD_displayString("Welcome");
	/* Initalize the SysTick Timer to generate an interrupt every 1 second */
	SysTick_Init();
	/* Disable timer till we need it */
	SysTick_Disable();
	uint8 key_Value, Beef_weight = 0, Chicken_weight = 0, Cooking_Time_digit = 0, cook_time_flag = 0;
	uint16 Cooking_Time_total[4] = {0}, Total_cooking = 0;
	while (1)
	{
		key_Value = KeyPad_getPressedKey(); // get the key pressed value
		if (key_Value != 0)
		{
			LCD_clearScreen();
			/* Display input on lcd for 2 secs */
			LCD_displayCharacter(key_Value);
			Delay_MS(2000);
		}
		switch (key_Value)
		{
		case 'A':
			LCD_clearScreen();
			/* Display "Popcorn" on lcd for 2 secs */
			LCD_displayString("Popcorn");
			Delay_MS(2000);
			App_Counter(60);
			break;
		case 'B':
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
			App_Counter(30 * Beef_weight); // 0.5 per min
			LCD_clearScreen();
			break;
		case 'C':
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
			App_Counter(12 * Chicken_weight); // 0.2 per min
			LCD_clearScreen();
			break;
		case 'D':
			LCD_clearScreen();
			cook_time_flag = 0;
			/* Display “Cooking Time?” and wait for keypad input */
			LCD_displayStringRowColumn(0, 0, "Cooking Time?");
			LCD_displayStringRowColumn(1, 0, "00:00");
			do
			{
				Cooking_Time_digit = KeyPad_getPressedKey();
				if ((Cooking_Time_digit < '1') || (Cooking_Time_digit > '9'))
				{
					cook_time_flag = 0;
					LCD_clearScreen();
					LCD_displayString("Err");
					Delay_MS(2000);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0, "Cooking Time?");
					LCD_displayStringRowColumn(1, 0, "00:00");
				}
				else
				{
					cook_time_flag += 1;
					Cooking_Time_total[cook_time_flag - 1] = Cooking_Time_digit;
					for (uint8 i = 0, j = 0; j < cook_time_flag; i++, j++)
					{
						if (i == 2)
						{
							i += 1;
						}
						LCD_goToRowColumn(1, (4 - i));
						LCD_displayCharacter(Cooking_Time_total[cook_time_flag - j - 1]);
					}
					Delay_MS(400);
				}
			} while (cook_time_flag < 4);
			Delay_MS(1000);
			LCD_clearScreen();
			Total_cooking = string_to_int(Cooking_Time_total[0]) * 600 +
							string_to_int(Cooking_Time_total[1]) * 60 +
							string_to_int(Cooking_Time_total[2]) * 10 +
							string_to_int(Cooking_Time_total[3]) * 1;
			App_Counter(Total_cooking);
			LCD_clearScreen();
			break;
		}
	}

	return 0;
}
