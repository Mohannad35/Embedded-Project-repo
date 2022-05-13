// kepad

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

/* Defines the size of rows and columns of keypad */
#define  RowsSize  4
#define  ColsSize  4

/* Array of 4x4 to define characters which will be printe on specific key pressed */
unsigned  char symbol[RowsSize][ColsSize] = {{ '1', '2',  '3', 'A'},
                                             { '4', '5',  '6', 'B'},
                                             { '7', '8',  '9', 'C'},
                                             { '*', '0',  '#', 'D'}};

/* prototypes of Keypad functions */
void delay_ms(int n);	  /* mili second delay function */
void delay_us(int n);	  /* micro second delay function */
void keypad_Init(void);	  /* Keypad initialization */
char keypad_getkey(void); /*Scan and detect key pressed */
void delayMs(int n);
void delayUs(int n);

/* Main function calls LCD and keypad initialization functions */
int main()
{
	keypad_Init(); // Initialize keypad and TM4C123 GPIO pins
	while (1)
	{
          
         // GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disbale the others */
		char value = keypad_getkey(); // get the key pressed value
                if (value != 0)
                {
                  // GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disbale the others */
                }
		delayMs(10);				  // delay of one second
	}
}

/* Keypad_Init() configures PORTC and PORTE to scan keypad keys */
void keypad_Init(void)
{
	// 0001 0100 -> 00FE DCBA
	/* Enable clock for PORTC & PORTE and allow time for clock to start - portf for leds */ 
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x00000034;
    delay = SYSCTL_REGCGC2_REG;
	// while ((SYSCTL_REGCGC2_REG & 0x00000014) == 0); /* Wait untill clock is enabled */

	// rows E out
	GPIO_PORTE_AMSEL_REG &= 0xF0;         /* Disable Analog on PE0, PE1, PE2 and PE3 */
    GPIO_PORTE_PCTL_REG  &= 0xFFFF0000;   /* Clear PMCx bits for PE0, PE1, PE2 and PE3 to use it as GPIO pins */
    GPIO_PORTE_DIR_REG   |= 0x0F;         /* Configure PE0, PE1, PE2 and PE3 as output pins */
    GPIO_PORTE_AFSEL_REG &= 0xF0;         /* Disable alternative function on PE0, PE1, PE2 and PE3 */
    GPIO_PORTE_DEN_REG   |= 0x0F;         /* Enable Digital I/O on PE0, PE1, PE2 and PE3 */
    // GPIO_PORTE_DATA_REG  &= 0xF0;         /* Clear bit 0, 1, 2 and 3 in Data regsiter */

	// columns C in
	GPIO_PORTC_AMSEL_REG &= 0x0F;         /* Disable Analog on PC4, PC5, PC6 and PC7 */
    GPIO_PORTC_PCTL_REG  &= 0x0000FFFF;   /* Clear PMCx bits for PC4, PC5, PC6 and PC7 to use it as GPIO pins */
    GPIO_PORTC_DIR_REG   &= 0x0F;         /* Configure PC4, PC5, PC6 and PC7 as input pins */
    GPIO_PORTC_AFSEL_REG &= 0x0F;         /* Disable alternative function on PC4, PC5, PC6 and PC7 */
    GPIO_PORTC_DEN_REG   |= 0xF0;         /* Enable Digital I/O on PC4, PC5, PC6 and PC7 */
    GPIO_PORTC_PDR_REG   |= 0xF0;         /* Enable pull down registers on PC4, PC5, PC6 and PC7 */
	// GPIO_PORTC_PUR_REG   |= 0xF0;         /* Enable pull up registers on PC4, PC5, PC6 and PC7 */

	// leds init
	GPIO_PORTF_AMSEL_REG &= 0xF1;         /* Disable Analog on PF1, PF2 and PF3 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFF000F;   /* Clear PMCx bits for PF1, PF2 and PF3 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= 0x0E;         /* Configure PF1, PF2 and PF3 as output pin */
    GPIO_PORTF_AFSEL_REG &= 0xF1;         /* Disable alternative function on PF1, PF2 and PF3 */
    GPIO_PORTF_DEN_REG   |= 0x0E;         /* Enable Digital I/O on PF1, PF2 and PF3 */
    GPIO_PORTF_DATA_REG  &= 0xF1;         /* Clear bit 0, 1 and 2 in Data regsiter to turn off the leds */
}

/* keypad_getkey() function returns the value of key pressed by the user by traversing columns
and rows respectivley */
char keypad_getkey(void)
{
	while (1)
	{
		for (short j = 0; j < 4; j++)
		{
			// Apply 3.3 v (Digital Output) on keypad rows on-by-one
			GPIO_PORTE_DATA_REG = (0x01 << j);
			for (short i = 0; i < 4; i++)
			{
				// Digital read for any key pressed on keypad
				if ((GPIO_PORTC_DATA_REG & 0xF0) == (0x10 << i))
				{
					// row test with rbg leds
					if (i == 0)
						GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disbale the others */
					if (i == 1)
						GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04; /* Turn on the Blue LED and disbale the others */
					if (i == 2)
						GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08; /* Turn on the Green LED and disbale the others */
					if (i == 3)
						GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x06; /* Turn on the LED and disbale the others */
					// columns test with rbg leds
					// if (j == 0)
					// 	GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disbale the others */
					// if (j == 1)
					// 	GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04; /* Turn on the Blue LED and disbale the others */
					// if (j == 2)
					// 	GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08; /* Turn on the Green LED and disbale the others */
					// if (j == 3)
					// 	GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x06; /* Turn on the LED and disbale the others */
					return symbol[j][i];
				}
			}
		}
		delayMs(10);
	}
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3180; j++)
		{
		} /* do nothing for 1 ms */
}

/* delay n microseconds (16 MHz CPU clock) */
void delayUs(int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3; j++)
		{
		} /* do nothing for 1 us */
}