/*
 * I2C_Init.c
 *
 *  Created on: Mar 19, 2017
 *      Author: Shitij Avlani
 */


#include <stdint.h>
#include <inc\tm4c123gh6pm.h>
#include <I2C_Init.h>


void I2CSetup (void)
{

    //Activate Clock to GPIO Port B.
    SYSCTL_RCGCGPIO_R |= (1<<1);
    //Activate Clock to I2C0.
    SYSCTL_RCGCI2C_R |= (1<<0);
    //Enable Alternate Function on PB2, PB3.
    GPIO_PORTB_AFSEL_R |= ((1<<2) | (1<<3));
    //Configure PB2, PB3 as I2C0.
    GPIO_PORTB_DEN_R |= ((1<<2) | (1<<3));
    GPIO_PORTB_PCTL_R = ((GPIO_PORTB_PCTL_R & 0xFFFF00FF) + 0x00003300);
    //Disable Analog on PB2, PB3.
    GPIO_PORTB_AMSEL_R &= ~((1<<2) | (1<<3));
    //Enable Open Drain FUnction on PB3.
    GPIO_PORTB_ODR_R |= (1<<3);
    //Initialize I2C Master.
    I2C0_MCR_R = 0x00000010;
    //Set SCL Clock to 400Kbps.
    I2C0_MTPR_R = 1;

}

void I2CWrite (unsigned char addr, unsigned char *data, unsigned int len)
{

    //Set Slave Address.
    I2C0_MSA_R = (addr << 1);
    //Place Tx Data in Data Register.
    I2C0_MDR_R = *data;

    //Single Data Transfer.
    single: if(len == 1)
    {
        //Set Single Send Settings.
        I2C0_MCS_R = I2C_MASTER_CMD_SINGLE_SEND;
        //Wait Until Bus is Free.
        while(I2CMasterBusy);
        //Check for Error.
        if(I2CCheckError)
            goto single;
    }

    //Start sending consecutive data.
    I2C0_MCS_R = I2C_MASTER_CMD_BURST_SEND_START;
    while(I2CMasterBusy);
    len--;
    data++;

    //Continue sending consecutive data.
    while(len > 1)
    {
        I2C0_MDR_R = *data;
        I2C0_MCS_R = I2C_MASTER_CMD_BURST_SEND_CONT;
        while(I2CMasterBusy);
        len--;
        data++;
    }

    //Send last piece of data.
    I2C0_MDR_R = *data;
    I2C0_MCS_R = I2C_MASTER_CMD_BURST_SEND_FINISH;
    while(I2CMasterBusy);

}


void I2CRead (unsigned char addr, unsigned char* data, unsigned int len)
{

    //Assume I2C Recieving will always return data.
    if(len < 1)
        return;

    //Set address to read from
    I2C0_MSA_R = ((addr << 1) | (1<<0));

    //Check to see if pointer is to an array.
    if(len == 1)
    {
        I2C0_MCS_R =  I2C_MASTER_CMD_SINGLE_RECEIVE;
        while(I2CMasterBusy);
        *data = I2C0_MDR_R;
        return;
    }

    //Begin reading consecutive data.
    I2C0_MCS_R = I2C_MASTER_CMD_BURST_RECEIVE_START;
    while(I2CMasterBusy);
    *data = I2C0_MDR_R;
    len--;
    data++;

    //Continue reading consecutive data.
    while(len > 1)
    {
        I2C0_MCS_R = I2C_MASTER_CMD_BURST_RECEIVE_CONT;
        while(I2CMasterBusy);
        *data = I2C0_MDR_R;
        len--;
        data++;
    }
    //Read last character of data.
    I2C0_MCS_R = I2C_MASTER_CMD_BURST_RECEIVE_FINISH;
    while(I2CMasterBusy);
    *data = I2C0_MDR_R;

}

