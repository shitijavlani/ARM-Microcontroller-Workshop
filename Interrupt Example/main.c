/*
 * main.c
 */


#include <stdint.h>
#include <inc\tm4c123gh6pm.h>
#include <Timer_Init.h>


int main (void)
{

    // Enable Clock to GPIO Port F.
    SYSCTL_RCGCGPIO_R = 0x20;
    // Set direction of PF1 as Ouput.
    GPIO_PORTF_DIR_R = 0x02;
    // Enable Digital Function on PF1.
    GPIO_PORTF_DEN_R = 0x02;

    // Set up the timer.
    TimerSetup();

    // Do nothing when waiting for interrupt.
    while(1);

}
