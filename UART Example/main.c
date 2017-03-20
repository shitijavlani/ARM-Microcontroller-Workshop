/*
 * main.c
 */


#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <UART_Init.h>


#define UARTAvailable   (UART0_FR_R & (1<<4))


int main (void)
{

    // UART Echo //

    // Initialize UART0
    UART_Init();

    // Run forever.
    while(1)
        // If data is available on Rx line.
        if(UARTAvailable == 0)
            // Read and put it on Tx line.
            printChar(readChar());


}
