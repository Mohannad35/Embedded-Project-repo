/******************************************************************************
 * Module:		LED_SW
 * File Name:	LED_SW.c
 * Description:	Source file for the LED_SW TM4C123GH6PM (Tiva c) module
 * Created on:	May 13, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#include "LED_SW.h"

/* Enable PF1, PF2 and PF3 (RED, Blue and Green LEDs) */
void Leds_Init(void)
{
	// 0010 0000 -> 00FE DCBA
	/* Enable clock for PORTF for leds and allow time for clock to start */
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= (1<<LED_PORT_MASK); //0x00000020 in case of PORTF for leds
	delay = SYSCTL_REGCGC2_REG;
	// while ((SYSCTL_REGCGC2_REG & 0x00000014) == 0); /* Wait untill clock is enabled */

    /* Disable Analog on LED pin */
	(*((volatile uint32 *)(LED_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= ~(1<<LED_PIN);
    /* Clear PMCx bits for LED to use it as GPIO pin */
	(*((volatile uint32 *)(LED_PORT + PORT_CTL_REG_OFFSET))) &= ~(0xF<<(LED_PIN*4));//0xFFFF0FFF
    /* Configure LED pin as output pin */
	(*((volatile uint32 *)(LED_PORT + PORT_DIR_REG_OFFSET))) |= (1<<LED_PIN);//0x08
    /* Disable alternative function on LED pin */
	(*((volatile uint32 *)(LED_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= ~(1<<LED_PIN);//0xF7
    /* Enable Digital I/O on LED pin */
	(*((volatile uint32 *)(LED_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= (1<<LED_PIN);//0x08
    /* Clear LED Data pin (turn off led at first) */
	(*((volatile uint32 *)(LED_PORT + PORT_DATA_REG_OFFSET))) &= ~(1<<LED_PIN);//0xF7
}

/* Enable SW1, SW2 and activate external interrupt with falling edge */
void SWs_init(void)
{
	// 0010 0000 -> 00FE DCBA
	/* Enable clock for PORTF for Switchs and allow time for clock to start */
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= (1<<SW_PORT_MASK); //0x00000020 in case of PORTF for Switchs
	delay = SYSCTL_REGCGC2_REG;
	// while ((SYSCTL_REGCGC2_REG & 0x00000014) == 0); /* Wait untill clock is enabled */

/* in case of using PF0 we need to unlock it first */
#if (((SW1_PIN == 0) || (SW2_PIN == 0)) && (SW_PORT == GPIO_PORTF_BASE_ADDRESS))
	GPIO_PORTF_LOCK_REG = 0x4C4F434B; /* Unlock the GPIO_PORTF_CR_REG */
	GPIO_PORTF_CR_REG |= (1 << 0);	  /* Enable changes on PF0 */
#endif
	/* Disable Analog on SW1, SW2 */
	(*((volatile uint32 *)(SW_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= ~((1<<SW1_PIN) & (1<<SW2_PIN));
	/* Clear PMCx bits for SW1, SW2 to use it as GPIO pin */
	(*((volatile uint32 *)(SW_PORT + PORT_CTL_REG_OFFSET))) &= ~((0xF<<(SW1_PIN*4)) || (0xF<<(SW2_PIN*4)));//0xFFF0FFF0
	/* Configure SW1, SW2 as input pin */
	(*((volatile uint32 *)(SW_PORT + PORT_DIR_REG_OFFSET))) &= ~((1<<SW1_PIN) & (1<<SW2_PIN));
	/* Disable alternative function on SW1, SW2 */
	(*((volatile uint32 *)(SW_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= ~((1<<SW1_PIN) & (1<<SW2_PIN));
	/* Enable pull-down on SW1, SW2 */
	(*((volatile uint32 *)(SW_PORT + PORT_PULL_DOWN_REG_OFFSET))) |= ((1<<SW1_PIN) | (1<<SW2_PIN));
	/* Enable Digital I/O on SW1, SW2 */
	(*((volatile uint32 *)(SW_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= ((1<<SW1_PIN) | (1<<SW2_PIN));

	/* SW1, SW2 detect edges */
    (*((volatile uint32 *)(SW_PORT + PORT_IS_OFFSET))) &= ~((1<<SW1_PIN) & (1<<SW2_PIN));
	/* SW1, SW2 will detect a certain edge */
	(*((volatile uint32 *)(SW_PORT + PORT_IBE_OFFSET))) &= ~((1<<SW1_PIN) & (1<<SW2_PIN));
	/* SW1, SW2 will detect a falling edge */
	(*((volatile uint32 *)(SW_PORT + PORT_IEV_OFFSET))) &= ~((1<<SW1_PIN) & (1<<SW2_PIN));
	/* Clear Trigger flag for SW1, SW2 (Interupt Flag) */
	(*((volatile uint32 *)(SW_PORT + PORT_ICR_OFFSET))) |= ((1<<SW1_PIN) | (1<<SW2_PIN));
	/* Enable Interrupt on SW1, SW2 pin */
	(*((volatile uint32 *)(SW_PORT + PORT_IM_OFFSET))) |= ((1<<SW1_PIN) | (1<<SW2_PIN));

    /* Set GPIO PORTF priotiy as 2 by set Bit number 21, 22 and 23 with value 2 */
	(*((volatile uint32 *)(NVIC_BASE_ADDRESS + SW_PRI_OFFSET))) =
		((*((volatile uint32 *)(NVIC_BASE_ADDRESS + SW_PRI_OFFSET))) & SW_PRI_MASK) |
		((SW_INTERRUPT_PRIORITY << SW_PRI_SHIFT) & SW_PRI_NUM_MASK);
	/* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
	(*((volatile uint32 *)(NVIC_BASE_ADDRESS + SW_EN_OFFSET))) |= (1<<SW_EN_BIT_NUM);
	
	// NVIC_PRI7_REG = (NVIC_PRI7_REG & PRI_MASK_4N_2) | ((2<<PRI_SHIFT_4N_2) & PRI_NUM_MASK_4N_2);
	// /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
	// NVIC_EN0_REG |= (1<<30);
}

/* Return SW1 value */
uint8 Read_STOP_SW(void)
{
	return BIT_IS_SET((*((volatile uint32 *)(SW_PORT + PORT_RIS_OFFSET))), SW1_PIN);
}

/* Return SW2 value */
uint8 Read_START_SW(void)
{
	return BIT_IS_SET((*((volatile uint32 *)(SW_PORT + PORT_RIS_OFFSET))), SW2_PIN);
}

/* High output on LED pin */
void LED_ON(void)
{
	(*((volatile uint32 *)(LED_PORT + PORT_DATA_REG_OFFSET)))  |= (1<<LED_PIN);
}

/* Low output on LED pin */
void LED_OFF(void)
{
	(*((volatile uint32 *)(LED_PORT + PORT_DATA_REG_OFFSET)))  &= ~(1<<LED_PIN);
}

