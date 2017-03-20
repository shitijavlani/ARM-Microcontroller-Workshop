/*
 * TMP100.h
 *
 *  Created on: Mar 19, 2017
 *      Author: Shitij Avlani
 */

#ifndef TMP100_H_
#define TMP100_H_


//Function Prototypes
extern void SetResolution (uint8_t resolution, uint8_t address);
extern float GetTemp (uint8_t address);


#endif /* TMP100_H_ */
