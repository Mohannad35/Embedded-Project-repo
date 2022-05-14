/******************************************************************************
 * Module:		LED_SW
 * File Name:	LED_SW.c
 * Description:	Source file for the LED_SW TM4C123GH6PM (Tiva c) module
 * Created on:	May 10, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#include "LED_SW.h"

/* Enable PF1, PF2 and PF3 (RED, Blue and Green LEDs) */
void Leds_Init(void)
{
    GPIO_PORTF_AMSEL_REG &= 0xF1;         /* Disable Analog on PF1, PF2 and PF3 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFF000F;   /* Clear PMCx bits for PF1, PF2 and PF3 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= 0x0E;         /* Configure PF1, PF2 and PF3 as output pin */
    GPIO_PORTF_AFSEL_REG &= 0xF1;         /* Disable alternative function on PF1, PF2 and PF3 */
    GPIO_PORTF_DEN_REG   |= 0x0E;         /* Enable Digital I/O on PF1, PF2 and PF3 */
    GPIO_PORTF_DATA_REG  &= 0xF1;         /* Clear bit 0, 1 and 2 in Data regsiter to turn off the leds */
}

/* Enable PF0, PF4 (SW1, SW2) and activate external interrupt with falling edge */
void SWs_init(void)
{
    GPIO_PORTF_LOCK_REG   = 0x4C4F434B;             /* Unlock the GPIO_PORTF_CR_REG */
	GPIO_PORTF_CR_REG    |= (1<<0);                 /* Enable changes on PF0 */
	GPIO_PORTF_AMSEL_REG &= ~((1<<0) & (1<<4));     /* Disable Analog on PF0, PF4 */
	GPIO_PORTF_PCTL_REG  &= 0xFFF0FFF0;             /* Clear PMCx bits for PF0, PF4 to use it as GPIO pin */
	GPIO_PORTF_DIR_REG   &= ~((1<<0) & (1<<4));     /* Configure PF0, PF4 as input pin */
	GPIO_PORTF_AFSEL_REG &= ~((1<<0) & (1<<4));     /* Disable alternative function on PF0, PF4 */
	GPIO_PORTF_PUR_REG   |= ((1<<0) | (1<<4));      /* Enable pull-up on PF0, PF4 */
	GPIO_PORTF_DEN_REG   |= ((1<<0) | (1<<4));      /* Enable Digital I/O on PF0, PF4 */

    GPIO_PORTF_IS_REG    &= ~((1<<0) & (1<<4));     /* PF0, PF4 detect edges */
	GPIO_PORTF_IBE_REG   &= ~((1<<0) & (1<<4));     /* PF0, PF4 will detect a certain edge */
	GPIO_PORTF_IEV_REG   &= ~((1<<0) & (1<<4));     /* PF0, PF4 will detect a falling edge */
	GPIO_PORTF_ICR_REG   |= ((1<<0) | (1<<4));      /* Clear Trigger flag for PF0, PF4 (Interupt Flag) */
	GPIO_PORTF_IM_REG    |= ((1<<0) | (1<<4));      /* Enable Interrupt on PF0, PF4 pin */

    /* Set GPIO PORTF priotiy as 2 by set Bit number 21, 22 and 23 with value 2 */
	NVIC_PRI7_REG = (NVIC_PRI7_REG & PRI_MASK_4N_2) | ((2<<PRI_SHIFT_4N_2) & PRI_NUM_MASK_4N_2);
	NVIC_EN0_REG |= (1<<30); 				/* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
}
