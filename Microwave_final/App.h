/******************************************************************************
 * Module:		App
 * File Name:	App.h
 * Description:	Header file for App module TM4C123GH6PM (Tiva c)
 * Created on:	May 15, 2022
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#ifndef APP_H_
#define APP_H_

#include "Std_Types.h"

/*******************************************************************************
 *                                 Macros                                      *
 *******************************************************************************/
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

/*******************************************************************************
 *                             GLobal Variables                                *
 *******************************************************************************/
extern uint8 key_Value;

/*******************************************************************************
 *                           Functions Prototypes                              *
 *******************************************************************************/
/* Description: Task executes once to initialize all the Modules */
void Init_Task(void);

/* Description: Task executes When 'A' button is pressed on the keypad */
void Popcorn_Task(void);

/* Description: Task executes When 'B' button is pressed on the keypad */
void Beef_Task(void);

/* Description: Task executes When 'C' button is pressed on the keypad */
void Chicken_Task(void);

/* Description: Task executes When 'D' button is pressed on the keypad */
void Cooking_Time_Task(void);

/* Description: Task executes to count down from n_seconds to zero on LCD */
void Counter_Task(uint32 n_seconds);

/* Delay n milliseconds. */
void Delay_MS(unsigned long long n);

#endif /* APP_H_ */
