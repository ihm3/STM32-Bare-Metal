//stm32 chip driver kullanımı
//@ihm3
//INPUT Ornek

#include "stm32f4xx.h"

#define GPIOAEN		(1U<<0)
#define GPIOCEN		(1U<<2)



int main(void)
{
	RCC->CSR     |= (1<<31);

	RCC->AHB1ENR |= GPIOCEN;
	RCC->AHB1ENR |= GPIOAEN;

	GPIOC->MODER |=  (1U<<26);//PC13 OUTPUT
	GPIOC->MODER &=~ (1U<<27);

	GPIOA->MODER &=~ (1U<<0);//PA0 INPUT
	GPIOA->MODER &=~ (1U<<1);

	while(1)
	{
		if((GPIOA->IDR & (1U<<0)))
		{
			GPIOC->BSRR = (1U<<29);
		}else
		{
			GPIOC->BSRR = (1U<<13);
		}
	}
}
