/******************************************************************************
 * Module:		LED_SW
 * File Name:	LED_SW.h
 * Description:	Header file for the LED_SW module (TM4C123GH6PM (Tiva c))
 * Created on:	May 13, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#ifndef LED_SW_H_
#define LED_SW_H_

#include "std_types.h"

/**************************************** Configuration Instructions ***************************************************/
/* if u change switches positions from PORTA (pin 3, 2) u have to change the name
 * of the handler function GPIOPortA_Handler to the new PORT handler
 */

/* GPIO interrupts in vector table and theier registers */
// GPIO Port A (Vector teble number 16) (BIT  0 in interrupt regs) (PRI0)
// interrupt priority set reg(4n+0) where n = 0 so we need to set Bits 7:5

// GPIO Port B (Vector teble number 17) (BIT  1 in interrupt regs) (PRI0)
// interrupt priority set reg(4n+1) where n = 0 so we need to set Bits 15:13

// GPIO Port C (Vector teble number 18) (BIT  2 in interrupt regs) (PRI0)
// interrupt priority set reg(4n+2) where n = 0 so we need to set Bits 23:21

// GPIO Port D (Vector teble number 19) (BIT  3 in interrupt regs) (PRI0)
// interrupt priority set reg(4n+3) where n = 0 so we need to set Bits 31:29

// GPIO Port E (Vector teble number 20) (BIT  4 in interrupt regs) (PRI1)
// interrupt priority set reg(4n+0) where n = 1 so we need to set Bits 7:5

// GPIO Port F (Vector teble number 46) (BIT 30 in interrupt regs) (PRI7)
// interrupt priority set reg(4n+2) where n = 7 so we need to set Bits 23:21
/***********************************************************************************************************************/
/*******************************************************************************
 *                                   Macros                                    *
 *******************************************************************************/
#define LEDs_number				1
#define SWs_number				3
#define LED_PORT 				GPIO_PORTA_BASE_ADDRESS
#define LED_PORT_MASK 			PORT_A_MASK
#define BUZZER_PORT 			GPIO_PORTA_BASE_ADDRESS
#define BUZZER_PORT_MASK 		PORT_A_MASK
#define SW_PORT 				GPIO_PORTF_BASE_ADDRESS
#define SW_PORT_MASK 			PORT_F_MASK
#define Door_SW_PORT 			GPIO_PORTA_BASE_ADDRESS
#define Door_SW_PORT_MASK 		PORT_A_MASK
#define LED_PIN					4 							// PA4 (REDs)
#define BUZZER_PIN				2 							// PA2
#define SW1_PIN					4							// PF4 (STOP)
#define SW2_PIN					0							// PF0 (RESUME)
#define SW3_PIN					3							// PA3 (Door)
#define SW_INTERRUPT_PRIORITY 	2
#define SW_EN_BIT_NUM 			30							// PORTF (30 for F, 0 for A)
#define SW_EN_OFFSET 			NVIC_EN0_OFFSET 			// PORTA,B,C,D,E,F
#define SW_PRI_OFFSET 			NVIC_PRI7_OFFSET 			// PORTF:PRI7, PORTA,B,C,D:PRI0, PORTE:PRI1
#define SW_PRI_MASK				PRI_MASK_4N_2				// Bits 23:21 (4n+2)
#define SW_PRI_SHIFT			PRI_SHIFT_4N_2				// Bits 23:21 (4n+2)
#define SW_PRI_NUM_MASK			PRI_NUM_MASK_4N_2			// Bits 23:21 (4n+2)
#define Door_SW_EN_BIT_NUM 		0							// PORTA (30 for F, 0 for A)
#define Door_SW_EN_OFFSET 		NVIC_EN0_OFFSET 			// PORTA,B,C,D,E,F
#define Door_SW_PRI_OFFSET 		NVIC_PRI0_OFFSET 			// PORTA:PRI0, PORTA,B,C,D:PRI0, PORTE:PRI1
#define Door_SW_PRI_MASK		PRI_MASK_4N_0				// Bits 7:5 (4n+0)
#define Door_SW_PRI_SHIFT		PRI_SHIFT_4N_0				// Bits 7:5 (4n+0)
#define Door_SW_PRI_NUM_MASK	PRI_NUM_MASK_4N_0			// Bits 7:5 (4n+0)

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/
/* Initialize LED pin */
void Leds_Init(void);

/* Initialize LED pin */
void Buzzer_Init(void);

/* Initialize SW1, SW2 */
void SWs_init(void);

/* Initialize SW1, SW2 */
void Door_SW_init(void);

/* Return SW1 value */
uint8 Read_STOP_SW(void);

/* Return SW2 value */
uint8 Read_START_SW(void);

/* High output on LED pin */
void LED_ON(void);

/* Low output on LED pin */
void LED_OFF(void);

/* Low output on LED pin */
void LED_TOGGLE(void);

/* High output on LED pin */
void BUZZER_ON(void);

/* Low output on LED pin */
void BUZZER_OFF(void);

/* Low output on LED pin */
void BUZZER_TOGGLE(void);

#endif /* LED_SW_H_ */