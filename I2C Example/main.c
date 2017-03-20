/*
 * main.c
 */


#include <stdint.h>
#include <I2C_Init.h>
#include <UART_Init.h>
#include <Timer_Init.h>
#include <TMP100.h>


int main(void)
{

    // Initialize I2C0.
    I2CSetup();
    // Initialize UART0.
    UARTSetup();
    // Set TMP100 sensing resolution.
    SetResolution(0x03, 0x48);
    // Setup the timers for periodic sampling.
    TimerSetup();
	
    // Loop forever doing nothing while waiting for sampling timer interrupt.
    while(1);

}
