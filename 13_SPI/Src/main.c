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
	const char* message = "@ihm3..";

	init_USART1();
	DMA2_stream7_init(message, (uint32_t)&USART1->DR, 7);

	RCC->AHB1ENR |= GPIOCEN;

	GPIOC->MODER |= (1U<<26);
	GPIOC->MODER &=~ (1U<<27);



	while(1)
	{


	}
}


void DMA2_Stream7_IRQHandler()
{
	if(DMA2->HISR & HISR_TCIF7)//istenilen interrupt control edilir
	{
		//flg 0 lanır
		DMA2->HIFCR |= HIFCR_CTCIF7;

		//code..
		GPIOC->ODR	|= PIN13;
	}
}

