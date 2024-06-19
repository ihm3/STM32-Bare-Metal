/*
 * SPI.h
 *
 *  Created on: Nov 5, 2023
 *      Author: mthn_
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include "stdint.h"
#include "stdio.h"

void init_SPI1(void);
void config_SPI1(void);
void send_SPI1(uint8_t *data, uint32_t size);
void read_SPI1(uint8_t *data, uint32_t size);
void enable_CS1(FunctionalState status);



#endif /* SPI_H_ */
