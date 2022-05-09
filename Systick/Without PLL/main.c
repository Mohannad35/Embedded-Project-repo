#include "tm4c123gh6pm_registers.h"

#define SYSTICK_PRIORITY_MASK        0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY       3
#define SYSTICK_PRIORITY_BITS_POS        29

#define NUMBER_TICKS_PER_ONE_SECOND      1
#define NUMBER_TICKS_PER_TWO_SECOND      2
#define NUMBER_TICKS_PER_THREE_SECOND    3

#define SVC_PRIORITY_MASK        0x1FFFFFFF
#define SVC_PRIORITY                 0
#define SVC_PRIORITY_BITS_POS        29

/* Enable Exceptions ... This Macro enables Exceptions by clearing the F-bit in the FAULTMASK */
#define Enable_Exceptions()    __asm("CPSIE F")

/* Disable Exceptions ... This Macro disables Exceptions by setting the F-bit in the FAULTMASK */
#define Disable_Exceptions()   __asm("CPSID F")

/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    __asm("CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   __asm("CPSID I")

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("WFI")

/* Trigger SVC Exception ... This Macro use the SVC instruction to make SW Interrupt */
#define Trigger_SVC_Exception() __asm("SVC #0")

volatile unsigned char ticks_num = 0;

/* SysTick Timer ISR ... No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
void SysTick_Handler(void)
{
    ticks_num++; /* increment the number of ticks */
    
    if(ticks_num == NUMBER_TICKS_PER_ONE_SECOND)
    {
        GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x02; /* Turn on the Red LED and disbale the others */
    }
    else if(ticks_num == NUMBER_TICKS_PER_TWO_SECOND)
    {
        GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x04; /* Turn on the Blue LED and disbale the others */
    }
    else if(ticks_num == NUMBER_TICKS_PER_THREE_SECOND)
    {
        GPIO_PORTF_DATA_REG = (GPIO_PORTF_DATA_REG & 0xF1) | 0x08; /* Turn on the Green LED and disbale the others */
        ticks_num = 0; /* reset the variable value */
    }
}

/* Enable PF1, PF2 and PF3 (RED, Blue and Green LEDs) */
void Leds_Init(void)
{
    GPIO_PORTF_AMSEL_REG &= 0xF1;         /* Disable Analog on PF1, PF2 and PF3 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFF000F;   /* Clear PMCx bits for PF1, PF2 and PF3 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= 0x0E;         /* Configure PF1, PF2 and PF3 as output pin */
    GPIO_PORTF_AFSEL_REG &= 0xF1;         /* Disable alternative function on PF1, PF2 and PF3 */
    GPIO_PORTF_DEN_REG   |= 0x0E;         /* Enable Digital I/O on PF1, PF2 and PF3 */
    GPIO_PORTF_DATA_REG  &= 0xF1;         /* Clear bit 0, 1 and 2 in Data regsiter to turn off the leds */
}

/* Enable the SystTick Timer to run using the System Clock with Frequency 16Mhz and generate interrupt every 1 second */
void SysTick_Init(void)
{
    SYSTICK_CTRL_REG    = 0;               /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 15999999;        /* Set the Reload value with 15999999 to count 1 Second */
    SYSTICK_CURRENT_REG = 0;               /* Clear the Current Register value */
    /* Configure the SysTick Control Register 
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1) */
    SYSTICK_CTRL_REG   |= 0x07;
    /* Assign priority level 3 to the SysTick Interrupt */
    NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
}

/* Set PRIV Bit(Bit 0) in the CONTROL register to switch to Unprivileged access level */
void Switch_To_Unpriviledged(void)
{
    __asm("MOV R0, #1");      /* Set the Ro register value to 1 */
    __asm("MSR CONTROL, R0"); /* Set the PRIV Bit(Bit 0) to 1 ... This will switch to Unprivileged access level */
}

/* SVC Exception Handler */
void SVC_Handler(void)
{
    unsigned char SVC_Num = 0;
    __asm("LDR R0, [SP, #24]");  /* Extract the stacked LR register value which vectoring to this handler */
    __asm("LDRB R0, [R0, #-2]"); /* Extract the SVC number value it is exist in the first byte of address LR-2 */
    __asm("STR R0, [SP]");       /* Load the R0 value to SVC_Num variable as SP is pointing to SVC_Num location in the stack memory */
    
    switch(SVC_Num)
    {
        case 0:
            __asm("MOV R3, #0");      /* Load the R3 register with value 0 */
            __asm("MSR CONTROL, R3"); /* Clear the PRIV Bit(Bit 0) ... This will switch to Privileged access level */
            break;
        case 1:
        case 2:
        case 3:  
        case 255:  
            break;
        default:
            break;
    }
}

/* Initialize and Setup SVC Exception Priority */
void SVC_Init(void)
{
    /* Assign priority level 0 to the SVC Interrupt */
    NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) | (SVC_PRIORITY << SVC_PRIORITY_BITS_POS);
}

int main(void)
{
    /* Enable clock for PORTF and allow time for clock to start*/ 
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x00000020;
    delay = SYSCTL_REGCGC2_REG;
    
    /* Enable Interrupts and Exceptions */
    Enable_Interrupts();
    Enable_Exceptions();
    
    /* Initailize the LEDs as GPIO Pins */
    Leds_Init();
    
    /* Initialize the SCV Exception */
    SVC_Init();
    
    /* Switch to Unpriviledged access level */
    Switch_To_Unpriviledged();
    
    /* Triiger SVC Exception to go back to Priviledged access level through the SVC handler */
    Trigger_SVC_Exception();
    
    /* Initalize the SysTick Timer to generate an interrupt every 1 second */
    SysTick_Init();
    
    while(1){}
    
    return 0;
}