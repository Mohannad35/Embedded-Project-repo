#ifndef TM4C123GH6PM_REGISTERS
#define TM4C123GH6PM_REGISTERS

/*****************************************************************************
GPIO registers
*****************************************************************************/
/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS 		0x40004000
#define GPIO_PORTB_BASE_ADDRESS 		0x40005000
#define GPIO_PORTC_BASE_ADDRESS 		0x40006000
#define GPIO_PORTD_BASE_ADDRESS 		0x40007000
#define GPIO_PORTE_BASE_ADDRESS 		0x40024000
#define GPIO_PORTF_BASE_ADDRESS 		0x40025000
#define PORT_A_MASK 					0
#define PORT_B_MASK 					1
#define PORT_C_MASK 					2
#define PORT_D_MASK 					3
#define PORT_E_MASK 					4
#define PORT_F_MASK 					5

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET			0x3FC
#define PORT_DIR_REG_OFFSET				0x400
#define PORT_ALT_FUNC_REG_OFFSET		0x420
#define PORT_PULL_UP_REG_OFFSET			0x510
#define PORT_PULL_DOWN_REG_OFFSET		0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET	0x51C
#define PORT_LOCK_REG_OFFSET			0x520
#define PORT_COMMIT_REG_OFFSET			0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET	0x528
#define PORT_CTL_REG_OFFSET				0x52C

/* RCC register which responsible of enabling GPIO port Clock */
#define SYSCTL_REGCGC2_REG        (*((volatile uint32 *)0x400FE108))

/*****************************************************************************
GPIO registers (PORTA)
*****************************************************************************/
#define GPIO_PORTA_DATA_REG       (*((volatile uint32 *)0x400043FC))
#define GPIO_PORTA_DIR_REG        (*((volatile uint32 *)0x40004400))
#define GPIO_PORTA_AFSEL_REG      (*((volatile uint32 *)0x40004420))
#define GPIO_PORTA_PUR_REG        (*((volatile uint32 *)0x40004510))
#define GPIO_PORTA_PDR_REG        (*((volatile uint32 *)0x40004514))
#define GPIO_PORTA_DEN_REG        (*((volatile uint32 *)0x4000451C))
#define GPIO_PORTA_LOCK_REG       (*((volatile uint32 *)0x40004520))
#define GPIO_PORTA_CR_REG         (*((volatile uint32 *)0x40004524))
#define GPIO_PORTA_AMSEL_REG      (*((volatile uint32 *)0x40004528))
#define GPIO_PORTA_PCTL_REG       (*((volatile uint32 *)0x4000452C))

/*****************************************************************************
GPIO registers (PORTB)
*****************************************************************************/
#define GPIO_PORTB_DATA_REG       (*((volatile uint32 *)0x400053FC))
#define GPIO_PORTB_DIR_REG        (*((volatile uint32 *)0x40005400))
#define GPIO_PORTB_AFSEL_REG      (*((volatile uint32 *)0x40005420))
#define GPIO_PORTB_PUR_REG        (*((volatile uint32 *)0x40005510))
#define GPIO_PORTB_PDR_REG        (*((volatile uint32 *)0x40005514))
#define GPIO_PORTB_DEN_REG        (*((volatile uint32 *)0x4000551C))
#define GPIO_PORTB_LOCK_REG       (*((volatile uint32 *)0x40005520))
#define GPIO_PORTB_CR_REG         (*((volatile uint32 *)0x40005524))
#define GPIO_PORTB_AMSEL_REG      (*((volatile uint32 *)0x40005528))
#define GPIO_PORTB_PCTL_REG       (*((volatile uint32 *)0x4000552C))

/*****************************************************************************
GPIO registers (PORTC)
*****************************************************************************/
#define GPIO_PORTC_DATA_REG       (*((volatile uint32 *)0x400063FC))
#define GPIO_PORTC_DIR_REG        (*((volatile uint32 *)0x40006400))
#define GPIO_PORTC_AFSEL_REG      (*((volatile uint32 *)0x40006420))
#define GPIO_PORTC_PUR_REG        (*((volatile uint32 *)0x40006510))
#define GPIO_PORTC_PDR_REG        (*((volatile uint32 *)0x40006514))
#define GPIO_PORTC_DEN_REG        (*((volatile uint32 *)0x4000651C))
#define GPIO_PORTC_LOCK_REG       (*((volatile uint32 *)0x40006520))
#define GPIO_PORTC_CR_REG         (*((volatile uint32 *)0x40006524))
#define GPIO_PORTC_AMSEL_REG      (*((volatile uint32 *)0x40006528))
#define GPIO_PORTC_PCTL_REG       (*((volatile uint32 *)0x4000652C))

/*****************************************************************************
GPIO registers (PORTD)
*****************************************************************************/
#define GPIO_PORTD_DATA_REG       (*((volatile uint32 *)0x400073FC))
#define GPIO_PORTD_DIR_REG        (*((volatile uint32 *)0x40007400))
#define GPIO_PORTD_AFSEL_REG      (*((volatile uint32 *)0x40007420))
#define GPIO_PORTD_PUR_REG        (*((volatile uint32 *)0x40007510))
#define GPIO_PORTD_PDR_REG        (*((volatile uint32 *)0x40007514))
#define GPIO_PORTD_DEN_REG        (*((volatile uint32 *)0x4000751C))
#define GPIO_PORTD_LOCK_REG       (*((volatile uint32 *)0x40007520))
#define GPIO_PORTD_CR_REG         (*((volatile uint32 *)0x40007524))
#define GPIO_PORTD_AMSEL_REG      (*((volatile uint32 *)0x40007528))
#define GPIO_PORTD_PCTL_REG       (*((volatile uint32 *)0x4000752C))

/*****************************************************************************
GPIO registers (PORTE)
*****************************************************************************/
#define GPIO_PORTE_DATA_REG       (*((volatile uint32 *)0x400243FC))
#define GPIO_PORTE_DIR_REG        (*((volatile uint32 *)0x40024400))
#define GPIO_PORTE_AFSEL_REG      (*((volatile uint32 *)0x40024420))
#define GPIO_PORTE_PUR_REG        (*((volatile uint32 *)0x40024510))
#define GPIO_PORTE_PDR_REG        (*((volatile uint32 *)0x40024514))
#define GPIO_PORTE_DEN_REG        (*((volatile uint32 *)0x4002451C))
#define GPIO_PORTE_LOCK_REG       (*((volatile uint32 *)0x40024520))
#define GPIO_PORTE_CR_REG         (*((volatile uint32 *)0x40024524))
#define GPIO_PORTE_AMSEL_REG      (*((volatile uint32 *)0x40024528))
#define GPIO_PORTE_PCTL_REG       (*((volatile uint32 *)0x4002452C))

/*****************************************************************************
GPIO registers (PORTF)
*****************************************************************************/
#define GPIO_PORTF_DATA_REG       (*((volatile uint32 *)0x400253FC))
#define GPIO_PORTF_DIR_REG        (*((volatile uint32 *)0x40025400))
#define GPIO_PORTF_AFSEL_REG      (*((volatile uint32 *)0x40025420))
#define GPIO_PORTF_PUR_REG        (*((volatile uint32 *)0x40025510))
#define GPIO_PORTF_PDR_REG        (*((volatile uint32 *)0x40025514))
#define GPIO_PORTF_DEN_REG        (*((volatile uint32 *)0x4002551C))
#define GPIO_PORTF_LOCK_REG       (*((volatile uint32 *)0x40025520))
#define GPIO_PORTF_CR_REG         (*((volatile uint32 *)0x40025524))
#define GPIO_PORTF_AMSEL_REG      (*((volatile uint32 *)0x40025528))
#define GPIO_PORTF_PCTL_REG       (*((volatile uint32 *)0x4002552C))

/*****************************************************************************
Systick Timer Registers
*****************************************************************************/
#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))

/*****************************************************************************
PLL Registers
*****************************************************************************/
#define SYSCTL_RIS_REG            (*((volatile uint32 *)0x400FE050))
#define SYSCTL_RCC_REG            (*((volatile uint32 *)0x400FE060))
#define SYSCTL_RCC2_REG           (*((volatile uint32 *)0x400FE070))

/*****************************************************************************
NVIC Priority set Registers
*****************************************************************************/
#define NVIC_PRI0_REG             (*((volatile uint32 *)0xE000E400))
#define NVIC_PRI1_REG             (*((volatile uint32 *)0xE000E404))
#define NVIC_PRI2_REG             (*((volatile uint32 *)0xE000E408))
#define NVIC_PRI3_REG             (*((volatile uint32 *)0xE000E40C))

#define NVIC_PRI4_REG             (*((volatile uint32 *)0xE000E410))
#define NVIC_PRI5_REG             (*((volatile uint32 *)0xE000E414))
#define NVIC_PRI6_REG             (*((volatile uint32 *)0xE000E418))
#define NVIC_PRI7_REG             (*((volatile uint32 *)0xE000E41C))

#define NVIC_PRI8_REG             (*((volatile uint32 *)0xE000E420))
#define NVIC_PRI9_REG             (*((volatile uint32 *)0xE000E424))
#define NVIC_PRI10_REG            (*((volatile uint32 *)0xE000E428))
#define NVIC_PRI11_REG            (*((volatile uint32 *)0xE000E42C))

#define NVIC_PRI12_REG            (*((volatile uint32 *)0xE000E430))
#define NVIC_PRI13_REG            (*((volatile uint32 *)0xE000E434))
#define NVIC_PRI14_REG            (*((volatile uint32 *)0xE000E438))
#define NVIC_PRI15_REG            (*((volatile uint32 *)0xE000E43C))

#define NVIC_PRI16_REG            (*((volatile uint32 *)0xE000E440))
#define NVIC_PRI17_REG            (*((volatile uint32 *)0xE000E444))
#define NVIC_PRI18_REG            (*((volatile uint32 *)0xE000E448))
#define NVIC_PRI19_REG            (*((volatile uint32 *)0xE000E44C))

#define NVIC_PRI20_REG            (*((volatile uint32 *)0xE000E450))
#define NVIC_PRI21_REG            (*((volatile uint32 *)0xE000E454))
#define NVIC_PRI22_REG            (*((volatile uint32 *)0xE000E458))
#define NVIC_PRI23_REG            (*((volatile uint32 *)0xE000E45C))

#define NVIC_PRI24_REG            (*((volatile uint32 *)0xE000E460))
#define NVIC_PRI25_REG            (*((volatile uint32 *)0xE000E464))
#define NVIC_PRI26_REG            (*((volatile uint32 *)0xE000E468))
#define NVIC_PRI27_REG            (*((volatile uint32 *)0xE000E46C))

#define NVIC_PRI28_REG            (*((volatile uint32 *)0xE000E470))
#define NVIC_PRI29_REG            (*((volatile uint32 *)0xE000E474))
#define NVIC_PRI30_REG            (*((volatile uint32 *)0xE000E478))
#define NVIC_PRI31_REG            (*((volatile uint32 *)0xE000E47C))

#define NVIC_PRI32_REG            (*((volatile uint32 *)0xE000E480))
#define NVIC_PRI33_REG            (*((volatile uint32 *)0xE000E484))
#define NVIC_PRI34_REG            (*((volatile uint32 *)0xE000E488))

/*****************************************************************************
NVIC Enable Registers
*****************************************************************************/
/* Interrupt 0-31 Set Enable */
#define NVIC_EN0_REG 		(*((volatile unsigned long *)0xE000E100))
/* Interrupt 32-63 Set Enable */
#define NVIC_EN1_REG 		(*((volatile unsigned long *)0xE000E104))
/* Interrupt 64-95 Set Enable */
#define NVIC_EN2_REG 		(*((volatile unsigned long *)0xE000E108))
/* Interrupt 96-127 Set Enable */
#define NVIC_EN3_REG 		(*((volatile unsigned long *)0xE000E10c))
/* Interrupt 96-127 Set Enable */
#define NVIC_EN4_REG 		(*((volatile unsigned long *)0xE000E110))

/*****************************************************************************
NVIC Disable Registers
*****************************************************************************/
#define NVIC_DIS0_REG 		(*((volatile unsigned long *)0xE000E180))
#define NVIC_DIS1_REG 		(*((volatile unsigned long *)0xE000E184))
#define NVIC_DIS2_REG 		(*((volatile unsigned long *)0xE000E188))
#define NVIC_DIS3_REG 		(*((volatile unsigned long *)0xE000E18c))
#define NVIC_DIS4_REG 		(*((volatile unsigned long *)0xE000E190))

/*****************************************************************************
GPIO Interrupt Sense    1->Level Sens    0->Edges Sense
*****************************************************************************/
#define GPIO_PORTA_IS_REG 	(*((volatile unsigned long *)0x40004404))
#define GPIO_PORTB_IS_REG 	(*((volatile unsigned long *)0x40005404))
#define GPIO_PORTC_IS_REG 	(*((volatile unsigned long *)0x40006404))
#define GPIO_PORTD_IS_REG 	(*((volatile unsigned long *)0x40007404))
#define GPIO_PORTE_IS_REG 	(*((volatile unsigned long *)0x40024404))
#define GPIO_PORTF_IS_REG 	(*((volatile unsigned long *)0x40025404))

/*****************************************************************************
GPIO Interrupt Both Edges    1->Both Edges   0->controlled by the GPIOIEV
*****************************************************************************/
#define GPIO_PORTA_IBE_REG 	(*((volatile unsigned long *)0x40004408))
#define GPIO_PORTB_IBE_REG 	(*((volatile unsigned long *)0x40005408))
#define GPIO_PORTC_IBE_REG 	(*((volatile unsigned long *)0x40006408))
#define GPIO_PORTD_IBE_REG 	(*((volatile unsigned long *)0x40007408))
#define GPIO_PORTE_IBE_REG 	(*((volatile unsigned long *)0x40024408))
#define GPIO_PORTF_IBE_REG 	(*((volatile unsigned long *)0x40025408))

/*****************************************************************************
GPIO Interrupt Event    1->Rising Edge   0->Falling Edge
*****************************************************************************/
#define GPIO_PORTA_IEV_REG 	(*((volatile unsigned long *)0x4000440C))
#define GPIO_PORTB_IEV_REG 	(*((volatile unsigned long *)0x4000540C))
#define GPIO_PORTC_IEV_REG 	(*((volatile unsigned long *)0x4000640C))
#define GPIO_PORTD_IEV_REG 	(*((volatile unsigned long *)0x4000740C))
#define GPIO_PORTE_IEV_REG 	(*((volatile unsigned long *)0x4002440C))
#define GPIO_PORTF_IEV_REG 	(*((volatile unsigned long *)0x4002540C))

/*****************************************************************************
GPIO Interrupt Mask    1->Allows Interrupts   0->Prevents Interrupts
*****************************************************************************/
#define GPIO_PORTA_IM_REG 	(*((volatile unsigned long *)0x40004410))
#define GPIO_PORTB_IM_REG 	(*((volatile unsigned long *)0x40005410))
#define GPIO_PORTC_IM_REG 	(*((volatile unsigned long *)0x40006410))
#define GPIO_PORTD_IM_REG 	(*((volatile unsigned long *)0x40007410))
#define GPIO_PORTE_IM_REG 	(*((volatile unsigned long *)0x40024410))
#define GPIO_PORTF_IM_REG 	(*((volatile unsigned long *)0x40025410))

/*****************************************************************************
GPIO Raw Interrupt Status 	(Flag set when interrupt occurs)
*****************************************************************************/
#define GPIO_PORTA_RIS_REG 	(*((volatile unsigned long *)0x40004414))
#define GPIO_PORTB_RIS_REG 	(*((volatile unsigned long *)0x40005414))
#define GPIO_PORTC_RIS_REG 	(*((volatile unsigned long *)0x40006414))
#define GPIO_PORTD_RIS_REG 	(*((volatile unsigned long *)0x40007414))
#define GPIO_PORTE_RIS_REG 	(*((volatile unsigned long *)0x40024414))
#define GPIO_PORTF_RIS_REG 	(*((volatile unsigned long *)0x40025414))

/*****************************************************************************
GPIO Interrupt Clear 	(1 -> clear Flag set when interrupt occurs)
*****************************************************************************/
#define GPIO_PORTA_ICR_REG 	(*((volatile unsigned long *)0x4000441c))
#define GPIO_PORTB_ICR_REG 	(*((volatile unsigned long *)0x4000541c))
#define GPIO_PORTC_ICR_REG 	(*((volatile unsigned long *)0x4000641c))
#define GPIO_PORTD_ICR_REG 	(*((volatile unsigned long *)0x4000741c))
#define GPIO_PORTE_ICR_REG 	(*((volatile unsigned long *)0x4002441c))
#define GPIO_PORTF_ICR_REG 	(*((volatile unsigned long *)0x4002541c))

#define NVIC_SYSTEM_PRI1_REG      (*((volatile uint32 *)0xE000ED18))
#define NVIC_SYSTEM_PRI2_REG      (*((volatile uint32 *)0xE000ED1C))
#define NVIC_SYSTEM_PRI3_REG      (*((volatile uint32 *)0xE000ED20))
#define NVIC_SYSTEM_SYSHNDCTRL    (*((volatile uint32 *)0xE000ED24))

/*****************************************************************************
NVIC Priority set Masks
*****************************************************************************/
#define PRI_MASK_4N_3 			0X1FFFFFFF
#define PRI_NUM_MASK_4N_3 		0XE0000000
#define PRI_SHIFT_4N_3 			29
// example:
/** NVIC_PRIn_R = (NVIC_PRIn_R & PRI_MASK_4N_3) | ((x<<PRI_SHIFT_4N_3) & PRI_NUM_MASK_4N_3) **/
/** "PRI_MASK_4N_3" and "PRI_NUM_MASK_4N_3" is used so we access only the 3 priority bits **/
/** x is the priority we want to put in the regigester **/
/** n is the number of the priority regigester **/
/* ****************************************************************************
GPIO Port D 	PRI0
SSI0,RX TX 		PRI1
PWM Gen 1 		PRI2
ADC Seq 1 		PRI3
Timer 0A 		PRI4
Timer 2A 		PRI5
Comp 2 			PRI6
GPIO Port G 	PRI7
Timer 3A 		PRI8
CAN0 			PRI9
Hibernate 		PRI10
uDMA Error 		PRI11
SysTick 		PRI3
*****************************************************************************/

#define PRI_MASK_4N_2 			0XFF1FFFFF
#define PRI_NUM_MASK_4N_2 		0X00E00000
#define PRI_SHIFT_4N_2 			21
// example:
/** NVIC_PRIn_R = (NVIC_PRIn_R & PRI_MASK_4N_2) | ((x<<PRI_SHIFT_4N_2) & PRI_NUM_MASK_4N_2) **/
/** "PRI_MASK_4N_2" and "PRI_NUM_MASK_4N_2" is used so we access only the 3 priority bits **/
/** x is the priority we want to put in the regigester **/
/** n is the number of the priority regigester **/
/* ***************************************************************************
GPIO Port C 	PRI0
UART1,RX TX 	PRI1
PWM Gen 0 		PRI2
ADC Seq 0 		PRI3
Watchdog 		PRI4
Timer 1B 		PRI5
Comp 1 			PRI6
GPIO Port F 	PRI7
SSI1,RX TX 		PRI8
Quad Encoder 1 	PRI9
Ethernet 		PRI10
uDMA Soft Tfr 	PRI11
PendSV 			?????
*****************************************************************************/

#define PRI_MASK_4N_1 			0XFFFF1FFF
#define PRI_NUM_MASK_4N_1 		0X0000E000
#define PRI_SHIFT_4N_1 			13
// example:
/** NVIC_PRIn_R = (NVIC_PRIn_R & PRI_MASK_4N_1) | ((x<<PRI_SHIFT_4N_1) & PRI_NUM_MASK_4N_1) **/
/** "PRI_MASK_4N_1" and "PRI_NUM_MASK_4N_1" is used so we access only the 3 priority bits **/
/** x is the priority we want to put in the regigester **/
/** n is the number of the priority regigester **/
/* ***************************************************************************
GPIO Port B 	PRI0
UART0,RX TX 	PRI1
PWM Fault 		PRI2
Quad Encoder 	PRI3
ADC Seq 3 		PRI4
Timer 1A 		PRI5
Comp 0 			PRI6
Flash Control 	PRI7
UART2,RX TX 	PRI8
I2C1 			PRI9
CAN2 			PRI10
PWM Gen 3 		PRI11
-- 				?????
*****************************************************************************/

#define PRI_MASK_4N_0 			0XFFFFFF1F
#define PRI_NUM_MASK_4N_0 		0X000000E0
#define PRI_SHIFT_4N_0 			5
// example:
/** NVIC_PRIn_R = (NVIC_PRIn_R & PRI_MASK_4N_0) | ((x<<PRI_SHIFT_4N_0) & PRI_NUM_MASK_4N_0) **/
/** "PRI_MASK_4N_0" and "PRI_NUM_MASK_4N_0" is used so we access only the 3 priority bits **/
/** x is the priority we want to put in the regigester **/
/** n is the number of the priority regigester **/
/* ***************************************************************************
GPIO Port A 	PRI0
GPIO Port E 	PRI1
I2C0 			PRI2
PWM Gen 2 		PRI3
ADC Seq 2 		PRI4
Timer 0B 		PRI5
Timer 2B 		PRI6
System Control 	PRI7
GPIO Port H 	PRI8
Timer 0B 		PRI9
CAN1 			PRI10
USB0 			PRI11
Debug 			?????
*****************************************************************************/

#endif
