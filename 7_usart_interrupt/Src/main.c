//stm32 chip driver kullanımı
//@ihm3
//USART interupt

#include	<stdio.h>
#include 	<stdint.h>
#include 	"stm32f4xx.h"
#include	"usart.h"

#define GPIOCEN		(1U<<2)
#define PIN13		(1U<<13)

char rdata;

int main(void)
{
	init_USART1_interrupt();

	RCC->AHB1ENR |= GPIOCEN;

	GPIOC->MODER |= (1U<<26);
	GPIOC->MODER &=~ (1U<<27);



	while(1)
	{


	}
}


void USART1_IRQHandler(void)
{
	//SR da RXNE stlenip setlenmediği kontrol edilir
	if(USART1->SR & (1U<<5))
	{
		rdata = USART1->DR;

		if(rdata == '1')
		{
			GPIOC->ODR |= PIN13;
		}else if(rdata == '0')
		{
			GPIOC->ODR &=~ PIN13;
		}
	}
}

