/*
 * I2C_Init.h
 *
 *  Created on: Mar 19, 2017
 *      Author: Shitij Avlani
 */

#ifndef I2C_INIT_H_
#define I2C_INIT_H_


#define I2CMasterBusy                       (I2C0_MCS_R & (1<<6) != 0)
#define I2CCheckError                       (I2C0_MCS_R & (1<<1) != 0)

#define I2C_MASTER_CMD_SINGLE_SEND              0x00000007
#define I2C_MASTER_CMD_BURST_SEND_FINISH        0x00000005
#define I2C_MASTER_CMD_BURST_SEND_START         0x00000003
#define I2C_MASTER_CMD_BURST_SEND_CONT          0x00000001
#define I2C_MASTER_CMD_BURST_RECEIVE_START      0x0000000B
#define I2C_MASTER_CMD_BURST_RECEIVE_CONT       0x00000009
#define I2C_MASTER_CMD_SINGLE_RECEIVE           0x00000007
#define I2C_MASTER_CMD_BURST_RECEIVE_FINISH     0x00000005


//Function Prototypes
extern void I2CSetup (void);
extern void I2CWrite (unsigned char addr, unsigned char *data, unsigned int len);
extern void I2CRead (unsigned char addr, unsigned char* data, unsigned int len);


#endif /* I2C_INIT_H_ */
