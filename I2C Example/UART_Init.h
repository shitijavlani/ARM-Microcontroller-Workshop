/*
 * UART_Init.h
 *
 *  Created on: Mar 19, 2017
 *      Author: Shitij Avlani
 */

#ifndef UART_INIT_H_
#define UART_INIT_H_


//Function Prototypes
extern void UARTSetup (void);
extern void printChar (unsigned char data);
extern void printInt (uint16_t n);
extern unsigned char readChar (void);
extern void printFloat (float f);



#endif /* UART_INIT_H_ */
