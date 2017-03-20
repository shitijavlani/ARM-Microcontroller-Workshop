/*
 * TMP100.c
 *
 *  Created on: Mar 19, 2017
 *      Author: Shitij Avlani
 */


#include <I2C_Init.h>
#include <stdint.h>
#include <TMP100.h>


void SetResolution (uint8_t resolution, uint8_t address)
{

    //Sets Resolution of the temperature sensor.
    if(resolution > 0x03)
        return;
    unsigned char data [2];
    unsigned char *dataAdd;
    data [0] = 0x01;
    data [1] = (resolution << 5);
    dataAdd = &data[0];
    I2CWrite (address, dataAdd, 2);
    data [0] = 0x00;
    I2CWrite (address, dataAdd, 1);

}


float GetTemp (uint8_t address)
{

    //Read temperature from sensor
    unsigned char data [2];
    unsigned char *dataAdd;
    dataAdd = &data[0];
    data [0] = 0x00;
    I2CWrite(address, dataAdd, 1);
    I2CRead(address, dataAdd, 2);
    return ((((data[0] << 8 ) | (data[1])) >> 4) * 0.0625);

}

