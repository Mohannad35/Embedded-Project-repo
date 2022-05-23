/******************************************************************************
 * Module:		LED_SW
 * File Name:	LED_SW.c
 * Description:	Source file for the LED_SW TM4C123GH6PM (Tiva c) module
 * Created on:	May 13, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#include "LED_SW.h"
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
/************************************************************************************
* Function Name: Leds_Init
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Initialize Led pin.
************************************************************************************/
void Leds_Init(void)
{
	// 0000 0001 -> 00FE DCBA
	/* Enable clock for Led PORT and allow time for clock to start */
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= (1<<LED_PORT_MASK);
	delay = SYSCTL_REGCGC2_REG;
	
    /* Disable Analog on LED pin */
	(*((volatile uint32 *)(LED_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= ~(1<<LED_PIN);
    /* Clear PMCx bits for LED to use it as GPIO pin */
	(*((volatile uint32 *)(LED_PORT + PORT_CTL_REG_OFFSET))) &= ~(0xF<<(LED_PIN*4));
    /* Configure LED pin as output pin */
	(*((volatile uint32 *)(LED_PORT + PORT_DIR_REG_OFFSET))) |= (1<<LED_PIN);//0x08
    /* Disable alternative function on LED pin */
	(*((volatile uint32 *)(LED_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= ~(1<<LED_PIN);
    /* Enable Digital I/O on LED pin */
	(*((volatile uint32 *)(LED_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= (1<<LED_PIN);
    /* Clear LED Data pin (turn off led at first) */
	(*((volatile uint32 *)(LED_PORT + PORT_DATA_REG_OFFSET))) &= ~(1<<LED_PIN);
}

/************************************************************************************
* Function Name: Buzzer_Init
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Initialize Buzzer pin.
************************************************************************************/
void Buzzer_Init(void)
{
	// 0000 0001 -> 00FE DCBA
	/* Enable clock for Buzzer PORT and allow time for clock to start */
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= (1<<BUZZER_PORT_MASK);
	delay = SYSCTL_REGCGC2_REG;
	
    /* Disable Analog on Buzzer pin */
	(*((volatile uint32 *)(BUZZER_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= ~(1<<BUZZER_PIN);
    /* Clear PMCx bits for Buzzer to use it as GPIO pin */
	(*((volatile uint32 *)(BUZZER_PORT + PORT_CTL_REG_OFFSET))) &= ~(0xF<<(BUZZER_PIN*4));
    /* Configure Buzzer pin as output pin */
	(*((volatile uint32 *)(BUZZER_PORT + PORT_DIR_REG_OFFSET))) |= (1<<BUZZER_PIN);
    /* Disable alternative function on Buzzer pin */
	(*((volatile uint32 *)(BUZZER_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= ~(1<<BUZZER_PIN);
    /* Enable Digital I/O on Buzzer pin */
	(*((volatile uint32 *)(BUZZER_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= (1<<BUZZER_PIN);
    /* Clear Buzzer Data pin (turn off Buzzer at first) */
	(*((volatile uint32 *)(BUZZER_PORT + PORT_DATA_REG_OFFSET))) &= ~(1<<BUZZER_PIN);
}

/************************************************************************************
* Function Name: Door_SW_init
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Initialize Door switch and activate external interrupt with falling edge.
************************************************************************************/
void Door_SW_init(void)
{
	// 0010 0000 -> 00FE DCBA
	/* Enable clock for  Switchs and allow time for clock to start */
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= (1<<Door_SW_PORT_MASK);
	delay = SYSCTL_REGCGC2_REG;

/* in case of using PF0 we need to unlock it first */
#if ((SW3_PIN == 0) && (Door_SW_PORT == GPIO_PORTF_BASE_ADDRESS))
	GPIO_PORTF_LOCK_REG = 0x4C4F434B; /* Unlock the GPIO_PORTF_CR_REG */
	GPIO_PORTF_CR_REG |= (1 << 0);	  /* Enable changes on PF0 */
#endif
	/* Disable Analog on SW3 */
	(*((volatile uint32 *)(Door_SW_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= ~(1<<SW3_PIN);
	/* Clear PMCx bits for SW3 to use it as GPIO pin */
	(*((volatile uint32 *)(Door_SW_PORT + PORT_CTL_REG_OFFSET))) &= ~(0xF<<(SW3_PIN*4));
	/* Configure SW3 as input pin */
	(*((volatile uint32 *)(Door_SW_PORT + PORT_DIR_REG_OFFSET))) &= ~(1<<SW3_PIN);
	/* Disable alternative function on SW3 */
	(*((volatile uint32 *)(Door_SW_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= ~(1<<SW3_PIN);
	/* Enable pull-down on SW3 */
	(*((volatile uint32 *)(Door_SW_PORT + PORT_PULL_UP_REG_OFFSET))) |= (1<<SW3_PIN);
	/* Enable Digital I/O on SW3 */
	(*((volatile uint32 *)(Door_SW_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= (1<<SW3_PIN);

	/* SW3 detect level */
    (*((volatile uint32 *)(Door_SW_PORT + PORT_IS_OFFSET))) |= (1<<SW3_PIN);
	/* SW3 will detect a low level */
	(*((volatile uint32 *)(Door_SW_PORT + PORT_IEV_OFFSET))) &= ~(1<<SW3_PIN);
	/* Enable Interrupt on SW3 pin */
	(*((volatile uint32 *)(Door_SW_PORT + PORT_IM_OFFSET))) |= (1<<SW3_PIN);

	// /* SW3 detect edges */
    // (*((volatile uint32 *)(Door_SW_PORT + PORT_IS_OFFSET))) &= ~(1<<SW3_PIN);
	// /* SW3 will detect a certain edge */
	// (*((volatile uint32 *)(Door_SW_PORT + PORT_IBE_OFFSET))) &= ~(1<<SW3_PIN);
	// /* SW3 will detect a falling edge */
	// (*((volatile uint32 *)(Door_SW_PORT + PORT_IEV_OFFSET))) &= ~(1<<SW3_PIN);
	// /* Clear Trigger flag for SW3 (Interupt Flag) */
	// (*((volatile uint32 *)(Door_SW_PORT + PORT_ICR_OFFSET))) |= (1<<SW3_PIN);
	// /* Enable Interrupt on SW3 pin */
	// (*((volatile uint32 *)(Door_SW_PORT + PORT_IM_OFFSET))) |= (1<<SW3_PIN);

    /* Set GPIO PORTF priotiy as 2 by set Bit number 5, 6 and 7 with value 2 */
	(*((volatile uint32 *)(NVIC_BASE_ADDRESS + Door_SW_PRI_OFFSET))) =
		((*((volatile uint32 *)(NVIC_BASE_ADDRESS + Door_SW_PRI_OFFSET))) & Door_SW_PRI_MASK) |
		((SW_INTERRUPT_PRIORITY << Door_SW_PRI_SHIFT) & Door_SW_PRI_NUM_MASK);
	/* Enable NVIC Interrupt for GPIO PORTA by set bit number 0 in EN0 Register */
	(*((volatile uint32 *)(NVIC_BASE_ADDRESS + Door_SW_EN_OFFSET))) |= (1<<Door_SW_EN_BIT_NUM);
}

/************************************************************************************
* Function Name: SWs_init
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Initialize SW1, SW2 and activate external interrupt with falling edge.
************************************************************************************/
void SWs_init(void)
{
	// 0010 0000 -> 00FE DCBA
	/* Enable clock for  Switchs and allow time for clock to start */
	volatile unsigned long delay = 0;
	SYSCTL_REGCGC2_REG |= (1<<SW_PORT_MASK);
	delay = SYSCTL_REGCGC2_REG;

/* in case of using PF0 we need to unlock it first */
#if (((SW1_PIN == 0) || (SW2_PIN == 0)) && (SW_PORT == GPIO_PORTF_BASE_ADDRESS))
	GPIO_PORTF_LOCK_REG = 0x4C4F434B; /* Unlock the GPIO_PORTF_CR_REG */
	GPIO_PORTF_CR_REG |= (1 << 0);	  /* Enable changes on PF0 */
#endif
	/* Disable Analog on SW1, SW2 */
	(*((volatile uint32 *)(SW_PORT + PORT_ANALOG_MODE_SEL_REG_OFFSET))) &= ~((1<<SW1_PIN) | (1<<SW2_PIN));
	/* Clear PMCx bits for SW1, SW2 to use it as GPIO pin */
	(*((volatile uint32 *)(SW_PORT + PORT_CTL_REG_OFFSET))) &= ~((0xF<<(SW1_PIN*4)) | (0xF<<(SW2_PIN*4)));
	/* Configure SW1, SW2 as input pin */
	(*((volatile uint32 *)(SW_PORT + PORT_DIR_REG_OFFSET))) &= ~((1<<SW1_PIN) | (1<<SW2_PIN));
	/* Disable alternative function on SW1, SW2 */
	(*((volatile uint32 *)(SW_PORT + PORT_ALT_FUNC_REG_OFFSET))) &= ~((1<<SW1_PIN) | (1<<SW2_PIN));
	/* Enable pull-down on SW1, SW2 */
	(*((volatile uint32 *)(SW_PORT + PORT_PULL_UP_REG_OFFSET))) |= ((1<<SW1_PIN) | (1<<SW2_PIN));
	/* Enable Digital I/O on SW1, SW2 */
	(*((volatile uint32 *)(SW_PORT + PORT_DIGITAL_ENABLE_REG_OFFSET))) |= ((1<<SW1_PIN) | (1<<SW2_PIN));

	/* SW1, SW2 detect edges */
    (*((volatile uint32 *)(SW_PORT + PORT_IS_OFFSET))) &= ~((1<<SW1_PIN) | (1<<SW2_PIN));
	/* SW1, SW2 will detect a certain edge */
	(*((volatile uint32 *)(SW_PORT + PORT_IBE_OFFSET))) &= ~((1<<SW1_PIN) | (1<<SW2_PIN));
	/* SW1, SW2 will detect a falling edge */
	(*((volatile uint32 *)(SW_PORT + PORT_IEV_OFFSET))) &= ~((1<<SW1_PIN) | (1<<SW2_PIN));
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
}

/************************************************************************************
* Function Name: Read_STOP_SW
* Parameters (in): None
* Parameters (out): SW1 data value (uint8)
* Return value: SW1 data value (uint8)
* Description: Function to Return SW1 value.
************************************************************************************/
uint8 Read_STOP_SW(void)
{
	return BIT_IS_SET((*((volatile uint32 *)(SW_PORT + PORT_RIS_OFFSET))), SW1_PIN);
}

/************************************************************************************
* Function Name: Read_START_SW
* Parameters (in): None
* Parameters (out): SW2 data value (uint8)
* Return value: SW2 data value (uint8)
* Description: Function to Return SW2 value.
************************************************************************************/
uint8 Read_START_SW(void)
{
	return BIT_IS_SET((*((volatile uint32 *)(SW_PORT + PORT_RIS_OFFSET))), SW2_PIN);
}

/************************************************************************************
* Function Name: LED_ON
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Function to set High output on LED pin.
************************************************************************************/
void LED_ON(void)
{
	SET_BIT((*((volatile uint32 *)(LED_PORT + PORT_DATA_REG_OFFSET))), LED_PIN);
}

/************************************************************************************
* Function Name: LED_OFF
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Function to set Low output on LED pin.
************************************************************************************/
void LED_OFF(void)
{
	CLEAR_BIT((*((volatile uint32 *)(LED_PORT + PORT_DATA_REG_OFFSET))), LED_PIN);
}

/************************************************************************************
* Function Name: LED_OFF
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Function to set Low output on LED pin.
************************************************************************************/
void LED_TOGGLE(void)
{
	TOGGLE_BIT((*((volatile uint32 *)(LED_PORT + PORT_DATA_REG_OFFSET))), LED_PIN);
}

/************************************************************************************
* Function Name: BUZZER_ON
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Function to set High output on BUZZER pin.
************************************************************************************/
void BUZZER_ON(void)
{
	SET_BIT((*((volatile uint32 *)(BUZZER_PORT + PORT_DATA_REG_OFFSET))), BUZZER_PIN);
}

/************************************************************************************
* Function Name: BUZZER_OFF
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Function to set Low output on BUZZER pin.
************************************************************************************/
void BUZZER_OFF(void)
{
	CLEAR_BIT((*((volatile uint32 *)(BUZZER_PORT + PORT_DATA_REG_OFFSET))), BUZZER_PIN);
}

/************************************************************************************
* Function Name: BUZZER_OFF
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Function to set Low output on BUZZER pin.
************************************************************************************/
void BUZZER_TOGGLE(void)
{
	TOGGLE_BIT((*((volatile uint32 *)(BUZZER_PORT + PORT_DATA_REG_OFFSET))), BUZZER_PIN);
}