#include "App.h"
#include "keypad.h"
#include "LCD.h"

int main()
{
	Init_Task();
	while (1)
	{
		key_Value = KeyPad_getPressedKey(); // get the key pressed value
		if ((key_Value == 'A') || (key_Value == 'B') || (key_Value == 'C') || (key_Value == 'D'))
		{
			LCD_clearScreen();
			/* Display input on lcd for 2 secs */
			LCD_displayCharacter(key_Value);
			Delay_MS(1500);
			switch (key_Value)
			{
			case 'A':
				Popcorn_Task();
				break;
			case 'B':
				Beef_Task();
				break;
			case 'C':
				Chicken_Task();
				break;
			case 'D':
				Cooking_Time_Task();
				break;
			}
		}
	}

	return 0;
}
