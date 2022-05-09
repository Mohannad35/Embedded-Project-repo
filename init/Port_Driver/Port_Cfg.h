 /******************************************************************************
 * Module: PORT
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohannad Ragab
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H


/* Number of the configured Dio Channels */
#define PORT_CONFIGURED_CHANNELS            (48U)
#define PORT_CONFIGURED_PORTS				(6U)
#define PORT_CONFIGURED_PINS				(8U)

/* pre-compile option for PORT SET PIN DIRECTION API */
#define PORT_SET_PIN_DIRECTION_API 			(STD_ON)

/* Port numbers */
#define PORT_A (0U)
#define PORT_B (1U)
#define PORT_C (2U)
#define PORT_D (3U)
#define PORT_E (4U)
#define PORT_F (5U)
/* Pin numbers */
#define PIN_0 (0U)
#define PIN_1 (1U)
#define PIN_2 (2U)
#define PIN_3 (3U)
#define PIN_4 (4U)
#define PIN_5 (5U)
#define PIN_6 (6U)
#define PIN_7 (7U)
/* Pin modes */
#define PORT_DIO_MODE 			(0U)
#define PORT_ALT_FUNC_01_MODE 	(1U)
#define PORT_ALT_FUNC_02_MODE 	(2U)
#define PORT_ALT_FUNC_03_MODE 	(3U)
#define PORT_ALT_FUNC_04_MODE 	(4U)
#define PORT_ALT_FUNC_05_MODE 	(5U)
#define PORT_ALT_FUNC_06_MODE 	(6U)
#define PORT_ALT_FUNC_07_MODE 	(7U)
#define PORT_ALT_FUNC_08_MODE 	(8U)
#define PORT_ALT_FUNC_09_MODE 	(9U)
#define PORT_ALT_FUNC_10_MODE 	(10U)
#define PORT_ALT_FUNC_11_MODE 	(11U)
#define PORT_ALT_FUNC_12_MODE 	(12U)
#define PORT_ALT_FUNC_13_MODE 	(13U)
#define PORT_ALT_FUNC_14_MODE 	(14U)
#define PORT_ANALOG_MODE 		(15U)

/* Symbolic names of each Port-Pin in the Microcontroller (MCU SPECIFIC) */
#define PORT_PA0                        (0U)
#define PORT_PA1                        (1U)
#define PORT_PA2                        (2U)
#define PORT_PA3                        (3U)
#define PORT_PA4                        (4U)
#define PORT_PA5                        (5U)
#define PORT_PA6                        (6U)
#define PORT_PA7                        (7U)
#define PORT_PB0                        (8U)
#define PORT_PB1                        (9U)
#define PORT_PB2                        (10U)
#define PORT_PB3                        (11U)
#define PORT_PB4                        (12U)
#define PORT_PB5                        (13U)
#define PORT_PB6                        (14U)
#define PORT_PB7                        (15U)
#define PORT_PC0                        (16U)
#define PORT_PC1                        (17U)
#define PORT_PC2                        (18U)
#define PORT_PC3                        (19U)
#define PORT_PC4                        (20U)
#define PORT_PC5                        (21U)
#define PORT_PC6                        (22U)
#define PORT_PC7                        (23U)
#define PORT_PD0                        (24U)
#define PORT_PD1                        (25U)
#define PORT_PD2                        (26U)
#define PORT_PD3                        (27U)
#define PORT_PD4                        (28U)
#define PORT_PD5                        (29U)
#define PORT_PD6                        (30U)
#define PORT_PD7                        (31U)
#define PORT_PE0                        (32U)
#define PORT_PE1                        (33U)
#define PORT_PE2                        (34U)
#define PORT_PE3                        (35U)
#define PORT_PE4                        (36U)
#define PORT_PE5                        (37U)
#define PORT_PE6                        (38U)
#define PORT_PE7                        (39U)
#define PORT_PF0                        (40U)
#define PORT_PF1                        (41U)
#define PORT_PF2                        (42U)
#define PORT_PF3                        (43U)
#define PORT_PF4                        (44U)
#define PORT_PF5                        (45U)
#define PORT_PF6                        (46U)
#define PORT_PF7                        (47U)

#endif /* PORT_CFG_H */