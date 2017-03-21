/*
 * main.c
 */


#include "stdint.h"
#include "Timer_Init.h"
#include "PWM_Init.h"


int main (void)
{

    // Set up PWM function on LED Pin.
    PWMLedConfig();
    // Initialize timer to periodically increase brightness like a sawtooth function.
    TimerSetup();

    while(1);

}
