/*
 * UART_Init.c
 *
 *  Created on: Mar 19, 2017
 *      Author: Shitij Avlani
 */


#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <UART_Init.h>


void UARTSetup (void)
{

    //Activate UART0 Clock.
    SYSCTL_RCGCUART_R |= (1<<0);
    //Activate Port A Clock.
    SYSCTL_RCGCGPIO_R |= (1<<0);

    //Disable UART0.
    UART0_CTL_R &= ~(0x00000001);
    //IBRD = int(16,000,000/(16*115,200)) = int(8.68055)
    UART0_IBRD_R = 8;
    //FBRD = round(0.68055 * 64 + 0.5) = 44
    UART0_FBRD_R = 44;
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

    //Wait if Tx FIFO is full.
    while((UART0_FR_R & (1<<5)) != 0);
    UART0_DR_R = data;

}


void printInt (uint16_t n)
{

    uint16_t new_value [5];
    int8_t x;
    uint8_t flag = 1;
    //Split number into digits.
    for (x = 0; ((x < 5)&&(flag == 1)); x++)
    {
        new_value[x] = n % 10;
        n /= 10;
        if(n == 0)
            flag = 0;
    }
    //Send ASCII equivalent of the digits.
    for ( x -= 1 ; x >= 0; x--)
        printChar (new_value[x] + 48);

}


unsigned char readChar (void)
{

    while((UART0_FR_R & (1<<4)) != 0);
    return((unsigned char)(UART0_DR_R&0xFF));

}


void printFloat (float f)
{

    float temp = f;
    int n = (int)(temp);
    temp -= n;
    //Print '-' if number is negative.
    if( n < 0)
    {
        printChar ('-');
        n *= -1;
    }

    //Print integer part of the number appended by a decimal point.
    printInt (n);
    printChar ('.');

    //Print decimal part upto two significant digits.
    int count;
    for(count = 0; count<2; count++)
    {
        n = (int)(temp * 10);
        printInt (n);
        temp = (temp * 10) - n;
    }

}


