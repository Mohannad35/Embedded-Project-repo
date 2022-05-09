 /******************************************************************************
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohannad Ragab
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* Non AUTOSAR files */
#include "Common_Macros.h"

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_PinType;

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,
	PORT_PIN_OUT
}Port_PinDirectionType;

/* Type definition for Port_PinModeType used by the PORT APIs */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    RESISTOR_OFF,
	PULL_UP,
	PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *  3. the direction of pin --> INPUT or OUTPUT
 *  4. the mode of pin
 *  5. the internal resistor --> Disable, Pull up or Pull down
 *  6. the initial value of pin if it's used for DIO
 *  7. Pin direction changeable during runtime --> STD_ON/STD_OFF
 *  8. Pin mode changeable during runtime --> STD_ON/STD_OFF
 */
typedef struct
{
	uint8 					port_num;
	uint8 					pin_num;
	Port_PinDirectionType 	direction;
	Port_PinModeType 		mode;
	Port_InternalResistor 	resistor;
	uint8 					initial_value;
	uint8 					Pin_direction_changeable;
	uint8 					Pin_mode_changeable;
} Port_ConfigChannel;

/* Data Structure required for initializing the Port Driver */
typedef struct Port_ConfigType
{
	const Port_ConfigChannel *Channels[PORT_CONFIGURED_CHANNELS];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/************************************************************************************
* Service Name: Port_SetupGpioPin
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
/* Function for PORT Initialization API */
void Port_Init(const Port_ConfigType* ConfigPtr);
//void Port_SetupGpioPin(const Port_ConfigType *ConfigPtr );

/* Function for set port pin direction */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);

/* Function to Refresh port direction */
void Port_RefreshPortDirection(void);

/* Function to set pin mode */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
