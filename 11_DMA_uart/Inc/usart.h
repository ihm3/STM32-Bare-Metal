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

#define HISR_TCIF7		(1U<<7)//stream7 transfer bitiş interrupt control biti
#define HIFCR_CTCIF7	(1U<<27)

void init_USART1(void);
char usart1_read(void);
void init_USART1_interrupt(void);
void DMA2_stream7_init(uint32_t src, uint32_t dst, uint32_t len);

#endif /* USART_H_ */
