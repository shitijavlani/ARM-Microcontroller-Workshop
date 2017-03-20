/*
 * Timer_Init.c
 *
 *  Created on: Mar 19, 2017
 *      Author: Shitij Avlani
 */


#include <stdint.h>
#include <inc\tm4c123gh6pm.h>


void TimerSetup (void)
{

    //Send clock to GPTM0.
    SYSCTL_RCGCTIMER_R |= (1<<0);

    //TIMERA0 SETUP (1Hz).
    //Disable the timer.
    TIMER0_CTL_R &= ~(1<<0);
    //Write the GPTMCFG witha a value of 0x00000000.
    TIMER0_CFG_R = 0x00000000;
    //Configure as periodic.
    TIMER0_TAMR_R |= (0X2<<0);
    //Count down timer.
    TIMER0_TAMR_R &= ~(1<<4);
    //Load value to count down from.
    TIMER0_TAILR_R = 0x00F42400;
    //Enable Interrupt when timer reaches 0.
    TIMER0_IMR_R |= (1<<0);
    //Enable interrupt in NVIC.
    NVIC_EN0_R |= (1<<(INT_TIMER0A-16));
    //Enable Timer.
    TIMER0_CTL_R |= (1<<0);

}


void TIMER0A_Handler (void)
{

    // Toggle Red LED.
    GPIO_PORTF_DATA_R ^= 0x02;
    // Reset the raw interrupt status.
    TIMER0_ICR_R |= (1<<0);

}

