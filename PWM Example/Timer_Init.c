/*
 * Timer_Init.c
 *
 *  Created on: Mar 21, 2017
 *      Author: Shitij Avlani
 */


#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "PWM_Init.h"


int16_t g_i16LEDDutyCycle = 0;


void TimerSetup (void)
{

    //Send clock to GPTM0.
    SYSCTL_RCGCTIMER_R |= 0x1;

    //TIMERA0 SETUP (25Hz).
    //Disable the timer.
    TIMER0_CTL_R &= ~0x1;
    //Write the GPTMCFG witha a value of 0x00000000.
    TIMER0_CFG_R = 0x00000000;
    //Configure as periodic.
    TIMER0_TAMR_R |= 0x2;
    //Count down timer.
    TIMER0_TAMR_R &= ~0x10;
    //Load value to count down from.
    TIMER0_TAILR_R = 0x9C400;
    //Enable Interrupt when timer reaches 0.
    TIMER0_IMR_R |= 0x1;
    //Enable interrupt in NVIC.
    NVIC_EN0_R |= (1<<(INT_TIMER0A-16));
    //Enable Timer.
    TIMER0_CTL_R |= 0x1;

}


void TIMER0A_Handler (void)
{

    SetPowerLEDDutyCycle (g_i16LEDDutyCycle);
    g_i16LEDDutyCycle += 10;
    g_i16LEDDutyCycle = (g_i16LEDDutyCycle > 500)? 0: g_i16LEDDutyCycle;
    TIMER0_ICR_R |= (1<<0);

}
