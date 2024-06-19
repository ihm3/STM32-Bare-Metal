//stm32 chip driver kullanımı
//@ihm3
//GPIO interrupt  --PA0 as input

/*
 *	Daha once toggle ettigimiz PB0 capture moduna alacagımız pine bağlanmalı
 */

#include	<stdio.h>
#include 	<stdint.h>
#include	"usart.h"
#include 	"adc.h"
#include	"tim.h"
#include 	"exti.h"
#include 	"stm32f4xx.h"


#define GPIOCEN		(1U<<2)
#define PIN13		(1U<<13)


int main(void)
{
	init_USART1();
	PA0_EXTI_init();

	RCC->AHB1ENR |= GPIOCEN;

	GPIOC->MODER |=  (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	while(1)
	{

	}
}

static void callback_exti(void)
{
	GPIOC->ODR ^= PIN13;
	printf("button pressed\n\r");
}


void EEXTI0_IRQHANDLER(void)
{
	if((EXTI->PR & LINE0) != 0)
	{
		//PR bayragı sıfırlanır
		EXTI->PR |=LINE0;
		//code..
		callback_exti();
	}
}
