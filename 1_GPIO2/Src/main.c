//stm32 chip driver kullanımı
//@ihm3
//BSRR Ornek

#include "stm32f4xx.h"


#define GPIOCEN		(1U<<2)
#define PIN13		(1U<<13)


int main(void)
{
	RCC->AHB1ENR |= GPIOCEN;

	GPIOC->MODER |= (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	while(1)
	{
		GPIOC->BSRR = (1U<<13);// 13 numaralı pine yazmak 13.pini set eder(1)
		for(int i=0;10000;i++);

		GPIOC->BSRR = (1U<<29);// 29 numaralı pine yazmak 13.pini reset eder(0)
		for(int i=0;10000;i++);
	}
}
