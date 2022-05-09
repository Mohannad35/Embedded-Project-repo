/******************************************************************************
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohannad Ragab
 ******************************************************************************/

#include "Port.h"

/*
The default configuration as follow:
1. The port number for each channel = (0,1,2,3,4,5 -> A,B,C,D,E,F in order)
2. The pin number for each channel = (from 0 -> 8)
3. The channel direction = (input)
4. The channel mode = (DIO digital input output pin)
5. The internal resistor = (OFF)
6. The initial value = (STD_LOW)
7. The pin direction changeable during runing time or not = (STD_OFF)
8. The pin mode changeable during runing time or not = (STD_OFF)
*/
/*	{
	Port_number,
	Pin_number,
	Direction,
	Mode,
	Internal_resistor,
	Initial_value,
	Direction_changable,
	Mode_changable
	} */
/* PB structures used with Port_Init API (they are combined in the end of this file in Port_Configuration Line 450) */
const Port_ConfigChannel Port_Configurations_PA0 = {
	PORT_A,
	PIN_0,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PA1 = {
	PORT_A,
	PIN_1,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PA2 = {
	PORT_A,
	PIN_2,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PA3 = {
	PORT_A,
	PIN_3,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PA4 = {
	PORT_A,
	PIN_4,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PA5 = {
	PORT_A,
	PIN_5,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PA6 = {
	PORT_A,
	PIN_6,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PA7 = {
	PORT_A,
	PIN_7,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PB0 = {
	PORT_B,
	PIN_0,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PB1 = {
	PORT_B,
	PIN_1,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PB2 = {
	PORT_B,
	PIN_2,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PB3 = {
	PORT_B,
	PIN_3,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PB4 = {
	PORT_B,
	PIN_4,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PB5 = {
	PORT_B,
	PIN_5,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PB6 = {
	PORT_B,
	PIN_6,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PB7 = {
	PORT_B,
	PIN_7,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PC4 = {
	PORT_C,
	PIN_4,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PC5 = {
	PORT_C,
	PIN_5,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PC6 = {
	PORT_C,
	PIN_6,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PC7 = {
	PORT_C,
	PIN_7,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};


const Port_ConfigChannel Port_Configurations_PD0 = {
	PORT_D,
	PIN_0,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PD1 = {
	PORT_D,
	PIN_1,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PD2 = {
	PORT_D,
	PIN_2,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PD3 = {
	PORT_D,
	PIN_3,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PD4 = {
	PORT_D,
	PIN_4,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PD5 = {
	PORT_D,
	PIN_5,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PD6 = {
	PORT_D,
	PIN_6,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};
/* This pin require unlock the commit register so I didn't configured it (there's NULL_PTR in it's place)*/
//const Port_ConfigChannel Port_Configurations_PD7 = {
//	PORT_D,
//	PIN_7,
//	PORT_PIN_IN,
//	PORT_DIO_MODE,
//	RESISTOR_OFF,
//	STD_LOW,
//	STD_OFF,
//	STD_OFF};

const Port_ConfigChannel Port_Configurations_PE0 = {
	PORT_E,
	PIN_0,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PE1 = {
	PORT_E,
	PIN_1,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PE2 = {
	PORT_E,
	PIN_2,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PE3 = {
	PORT_E,
	PIN_3,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PE4 = {
	PORT_E,
	PIN_4,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PE5 = {
	PORT_E,
	PIN_5,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};
/* This pin require unlock the commit register so I didn't configured it (there's NULL_PTR in it's place)*/
//const Port_ConfigChannel Port_Configurations_PF0 = {
//	PORT_F,
//	PIN_0,
//	PORT_PIN_IN,
//	PORT_DIO_MODE,
//	RESISTOR_OFF,
//	STD_LOW,
//	STD_OFF,
//	STD_OFF};

const Port_ConfigChannel Port_Configurations_PF1 = {
	PORT_F,
	PIN_1,
	PORT_PIN_OUT,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PF2 = {
	PORT_F,
	PIN_2,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PF3 = {
	PORT_F,
	PIN_3,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	RESISTOR_OFF,
	STD_LOW,
	STD_OFF,
	STD_OFF};

const Port_ConfigChannel Port_Configurations_PF4 = {
	PORT_F,
	PIN_4,
	PORT_PIN_IN,
	PORT_DIO_MODE,
	PULL_UP,
	STD_HIGH,
	STD_OFF,
	STD_OFF};

/* Pins with NULL_PTR configuration ethir not exist in the MCU (not used) or pins that can't be configured like JTAG Pins ^_^ */
const Port_ConfigType Port_Configuration = {
	&Port_Configurations_PA0,                 /* PORT_PA0 */
	&Port_Configurations_PA1,                 /* PORT_PA1 */
	&Port_Configurations_PA2,                 /* PORT_PA2 */
	&Port_Configurations_PA3,                 /* PORT_PA3 */
	&Port_Configurations_PA4,                 /* PORT_PA4 */
	&Port_Configurations_PA5,                 /* PORT_PA5 */
	&Port_Configurations_PA6,                 /* PORT_PA6 */
	&Port_Configurations_PA7,                 /* PORT_PA7 */
	&Port_Configurations_PB0,                 /* PORT_PB0 */
	&Port_Configurations_PB1,                 /* PORT_PB1 */
	&Port_Configurations_PB2,                 /* PORT_PB2 */
	&Port_Configurations_PB3,                 /* PORT_PB3 */
	&Port_Configurations_PB4,                 /* PORT_PB4 */
	&Port_Configurations_PB5,                 /* PORT_PB5 */
	&Port_Configurations_PB6,                 /* PORT_PB6 */
	&Port_Configurations_PB7,                 /* PORT_PB7 */
	NULL_PTR,                                 /* PORT_PC0 JTAG */
	NULL_PTR,                                 /* PORT_PC1 JTAG */
	NULL_PTR,                                 /* PORT_PC2 JTAG */
	NULL_PTR,                                 /* PORT_PC3 JTAG */
	&Port_Configurations_PC4,                 /* PORT_PC4 */
	&Port_Configurations_PC5,                 /* PORT_PC5 */
	&Port_Configurations_PC6,                 /* PORT_PC6 */
	&Port_Configurations_PC7,                 /* PORT_PC7 */
	&Port_Configurations_PD0,                 /* PORT_PD0 */
	&Port_Configurations_PD1,                 /* PORT_PD1 */
	&Port_Configurations_PD2,                 /* PORT_PD2 */
	&Port_Configurations_PD3,                 /* PORT_PD3 */
	&Port_Configurations_PD4,                 /* PORT_PD4 */
	&Port_Configurations_PD5,                 /* PORT_PD5 */
	&Port_Configurations_PD6,                 /* PORT_PD6 */
	NULL_PTR,                                 /* PORT_PD7 require unlock commit register */
	&Port_Configurations_PE0,                 /* PORT_PE0 */
	&Port_Configurations_PE1,                 /* PORT_PE1 */
	&Port_Configurations_PE2,                 /* PORT_PE2 */
	&Port_Configurations_PE3,                 /* PORT_PE3 */
	&Port_Configurations_PE4,                 /* PORT_PE4 */
	&Port_Configurations_PE5,                 /* PORT_PE5 */
	NULL_PTR,                                 /* PORT_PE6 doesn't exist */
	NULL_PTR,                                 /* PORT_PE7 doesn't exist */
	NULL_PTR,                                 /* PORT_PF0 require unlock commit register */
	&Port_Configurations_PF1,                 /* PORT_PF1 LED Pin */
	&Port_Configurations_PF2,                 /* PORT_PF2 */
	&Port_Configurations_PF3,                 /* PORT_PF3 */
	&Port_Configurations_PF4,                 /* PORT_PF4 Switch Pin*/
	NULL_PTR,                                 /* PORT_PF5 doesn't exist */
	NULL_PTR,                                 /* PORT_PF6 doesn't exist */
	NULL_PTR,                                 /* PORT_PF7 doesn't exist */
};
