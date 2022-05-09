 /******************************************************************************
 * Module:		KEYPAD
 * File Name:	KEYPAD.h
 * Description:	Header file for the KEYPAD AVR driver
 * Created on:	Jul 22, 2021
 * Author:		Mohannad Ragab Afifi
 *******************************************************************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                                   Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 4
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA 

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
