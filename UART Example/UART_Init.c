/*
 * UART_Init.c
 *
 *  Created on: Mar 19, 2017
 *      Author: Shitij Avlani
 */


#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <UART_Init.h>


void UART_Init (void)
{


    //Activate UART0 Clock.
    SYSCTL_RCGCUART_R |= (1<<0);
    //Activate PortA Clock.
    SYSCTL_RCGCGPIO_R |= (1<<0);

    //Disable UART0.
    UART0_CTL_R &= ~(0x00000001);
    //IBRD = int(16,000,000/(16*38,400)) = int(26.04167)
    UART0_IBRD_R = 26;
    //FBRD = round(0.04167 * 64 + 0.5) = 3
    UART0_FBRD_R = 3;
    //8 Data Bits, 0 Parity Bits, 1 Stop Bit, Enable FIFOs.
    UART0_LCRH_R = ((1<<6) | (1<<5) | (1<<4));
    //Enable UART0.
    UART0_CTL_R |= (0x00000001);

    //Enable Alternate Function on PA0, PA1.
    GPIO_PORTA_AFSEL_R |= ((1<<0) | (1<<1));
    //Configure PA0, PA1 as UART0.
    GPIO_PORTA_DEN_R |= ((1<<0) | (1<<1));
    GPIO_PORTA_PCTL_R = ((GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011);
    //Disable Analog on PA0, PA1.
    GPIO_PORTA_AMSEL_R &= ~((1<<0) | (1<<1));


}


void printChar (unsigned char data)
{

    // Wait till Tx FIFO is full
    while((UART0_FR_R & (1<<5)) != 0);
    // Copy data to transmit FIFO.
    UART0_DR_R = data;

}

unsigned char readChar (void)
{

    // Read from receive FIFO.
    return((unsigned char)(UART0_DR_R&0xFF));

}

