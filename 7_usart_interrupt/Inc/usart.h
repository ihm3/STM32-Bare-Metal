/*
 * usart.h
 *
 *  Created on: Oct 31, 2023
 *      Author: mthn_
 */

#ifndef USART_H_
#define USART_H_

#include 	<stdint.h>

#include 	"stm32f4xx.h"


void init_USART1(void);
char usart1_read(void);
void init_USART1_interrupt(void);

#endif /* USART_H_ */
