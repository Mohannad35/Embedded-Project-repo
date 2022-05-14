/******************************************************************************
 * Module:		SYSTICK
 * File Name:	systick.h
 * Description:	Header file for the systick driver (TM4C123GH6PM (Tiva c))
 * Created on:	May 10, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "tm4c123gh6pm_registers.h"
#include "std_types.h"

/*******************************************************************************
// the systick handler should be moved from this file to the file where it will be used (main.c or app.c for example)
// also u should call Enable_Interrupts(); if u use systick handler
 *******************************************************************************/

/*******************************************************************************
 *                                   Macros                                    *
 *******************************************************************************/
#define SYSTICK_PRIORITY_MASK        0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY       3
#define SYSTICK_PRIORITY_BITS_POS        29

/* Enable Exceptions ... This Macro enables Exceptions by clearing the F-bit in the FAULTMASK */
#define Enable_Exceptions()    __asm("CPSIE F")

/* Disable Exceptions ... This Macro disables Exceptions by setting the F-bit in the FAULTMASK */
#define Disable_Exceptions()   __asm("CPSID F")

/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    __asm("CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   __asm("CPSID I")

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/
/* SysTick initialization */
void SysTick_Init(void);

/* Disable SysTick timer */
void SysTick_Disable(void);

/* Enable SysTick timer to start over */
void SysTick_Enable(void);

#endif /* SYSTICK_H_ */