//stm32 chip driver kullanımı
//@ihm3
//TIMER3
#include	<stdio.h>
#include 	<stdint.h>
#include	"usart.h"
#include 	"adc.h"
#include	"tim.h"
#include 	"stm32f4xx.h"



#define GPIOCEN		(1U<<2)
#define PIN13		(1U<<13)


unsigned long sec;

int main(void)
{
	init_Timer3_1hz();
	init_USART1();
	RCC->AHB1ENR |= GPIOCEN;

	GPIOC->MODER |=  (1U<<26);
	GPIOC->MODER &=~ (1U<<27);


	while(1)
	{

		// timer interrupt flg ı beklenir
		while(!(TIM3->SR & SR_UIF)){}

		// bayrak tekrar sıfırlanır
		TIM3->SR &=~ SR_UIF;
		sec++;
		printf("second : %lu", sec);
		GPIOC->ODR ^= PIN13;
	}
}
