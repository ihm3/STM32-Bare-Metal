#ifndef USART_H_
#define USART_H_

#include 	<stdint.h>

#include 	"stm32f4xx.h"

static void Set_Boudrate(USART_TypeDef* USARTx, uint32_t clk, uint32_t boudrate);
void usart1_putchar(int ch);
uint32_t init_USART1(void);
char usart1_read(void);

#endif /* USART_H_ */
