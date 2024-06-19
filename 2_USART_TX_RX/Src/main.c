//stm32 chip driver kullanımı
//@ihm3
//USART TX

#include	<stdio.h>
#include 	<stdint.h>
#include 	"stm32f4xx.h"
#include	"usart.h"

#define GPIOCEN		(1U<<2)
#define PIN13		(1U<<13)

char rdata;

int main(void)
{

	init_USART1();

	RCC->AHB1ENR |= GPIOCEN;

	GPIOC->MODER |= (1U<<26);
	GPIOC->MODER &=~ (1U<<27);


	while(1)
	{
		rdata = usart1_read();

		if(rdata == '1')
		{
			GPIOC->ODR |= PIN13;
		}else if(rdata == '0')
		{
			GPIOC->ODR &=~ PIN13;
		}
	}
}
