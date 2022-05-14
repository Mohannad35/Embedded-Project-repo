/******************************************************************************
 * Module:		LED_SW
 * File Name:	LED_SW.h
 * Description:	Header file for the LED_SW module (TM4C123GH6PM (Tiva c))
 * Created on:	May 10, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#ifndef LED_SW_H_
#define LED_SW_H_

#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                                   Macros                                    *
 *******************************************************************************/

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/
/* Enable PF1, PF2 and PF3 (RED, Blue and Green LEDs) */
void Leds_Init(void);

/* Enable PF0, PF4 (SW1, SW2) */
void SWs_init(void);


#endif /* LED_SW_H_ */