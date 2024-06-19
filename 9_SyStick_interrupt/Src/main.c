//stm32 chip driver kullanımı
//@ihm3
//ADC
#include	<stdio.h>
#include 	<stdint.h>
#include	"usart.h"
#include 	"adc.h"
#include 	"stm32f4xx.h"
#include	"SyStick.h"


#define GPIOCEN		(1U<<2)
#define PIN13		(1U<<13)


unsigned long sec;

int main(void)
{
	init_USART1();

	Systick_1hz_interrupt();

	RCC->AHB1ENR |= GPIOCEN;

	GPIOC->MODER |=  (1U<<26);
	GPIOC->MODER &=~ (1U<<27);



	while(1)
	{

	}
}


void SysTick_Handler(void)
{
	//code..
	sec++;
	printf("second : %lu", sec);
	GPIOC->ODR ^= PIN13;
}
