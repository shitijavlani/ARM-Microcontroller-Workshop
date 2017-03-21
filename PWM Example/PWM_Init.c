/*
 * PWM_Init.c
 *
 *  Created on: Mar 21, 2017
 *      Author: Shitij Avlani
 */


#include <stdint.h>
#include <inc/tm4c123gh6pm.h>


//*****************************************************************************
// Configures the required registers to initialize PWM1 Module3.
// PWM Frequency - 1000Hz.
// The GPIO pin PF2 which is connected to the on board LED is configured as the
// PWM ouput pin.
// An initial duty cycle of 0% is set.
//*****************************************************************************
void PWMLedConfig (void)
{

    // Enable clock to PWM Module 1.
    SYSCTL_RCGCPWM_R |= 0x2;
    // Enable clock to Port F.
    SYSCTL_RCGCGPIO_R |= 0x20;

    // Enable Alternate Function on PF2.
    GPIO_PORTF_AFSEL_R |= 0x04;
    // Enable Digital Function on PF2.
    GPIO_PORTF_DEN_R |= 0x04;
    // Select Alternate Function as PWM on PF2.
    GPIO_PORTF_PCTL_R = ((GPIO_PORTF_PCTL_R & 0xFFFFF0FF) + 0x00000500);
    // Disable Analog Function on PF2.
    GPIO_PORTF_AMSEL_R &= ~0x04;

    // Enable PWM Clock Divider.
    SYSCTL_RCC_R |= 0x100000;
    // Set PWM Clock Divider to 16.
    SYSCTL_RCC_R = SYSCTL_RCC_R & 0xFFF7FFFF;

    // Disable PWM1.
    PWM1_CTL_R = 0x00000000;
    // Configure in count up/down mode.
    PWM1_3_CTL_R = 0x2;
    // Drive PWM high while counting up and low while counting down.
    PWM1_3_GENA_R = 0xB0;
    // Set the PWM Frequency to 1000Hz; LOAD = 16,000,000/(32*1000).
    PWM1_3_LOAD_R = 0x1F4;
    // Set the initial pulse width of the PWM pin to 0% duty cycle.
    PWM1_3_CMPA_R = 0x1F3;
    // Enable PWM1 Generator 3.
    PWM1_CTL_R = 0x8;
    PWM1_3_CTL_R |= 0x1;
    // Enable PWM output on PF2.
    PWM1_ENABLE_R = 0x40;

}


//*****************************************************************************
// Sets the duty cycle of the LED indicator.
//
// \param i16NewDutyCycle is the value of the new duty cycle to be set.
//*****************************************************************************
void SetPowerLEDDutyCycle (int16_t i16NewDutyCycle)
{

    if((i16NewDutyCycle > 500) || (i16NewDutyCycle < 0))
        return;
    if(i16NewDutyCycle == 0)
        PWM1_3_CMPA_R = 499;
    else
        PWM1_3_CMPA_R = ((500 - i16NewDutyCycle) & 0x0000FFFF);

}
