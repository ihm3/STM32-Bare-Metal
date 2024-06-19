/*
 * I2C.h
 *
 *  Created on: Nov 5, 2023
 *      Author: mthn_
 */

#ifndef I2C_H_
#define I2C_H_
#include "stm32f4xx.h"
#include "stdint.h"

void init_I2C1(void); // PB7 : SDA | PB6 : SCL olarak secildi
void I2C1_reaByte(char AddrSlave, char AddrMemory, char* data);
void I2C1_ReadBytes(char AddrSlave, char AddrMemory, int len,  char* data);
void I2C1_WriteBytes(char AddrSlave, char AddrMemory, int len,  char* data);


#endif /* I2C_H_ */
