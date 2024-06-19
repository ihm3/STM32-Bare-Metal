
#include "exti.h"

#define GPIOAEN		(1U<<0)
#define SYSCFGEN	(1U<<14)

void PA0_EXTI_init(void)
{
	/*Tum interruptlar disable yapılır*/
	__disable_irq();

	/*GPIAO clock erişimi*/
	RCC->AHB1ENR |=	GPIOAEN;

	GPIOA->MODER &=~ (1U<<0);
	GPIOA->MODER &=~ (1U<<1);

	/*SYSCFG clock erişimi*/
	RCC->APB2ENR |=	SYSCFGEN;

	/*PORT interrup için secılır(PORT A0)*/
	SYSCFG->EXTICR[0] &=~ (1U<<0);
	SYSCFG->EXTICR[0] &=~ (1U<<1);
	SYSCFG->EXTICR[0] &=~ (1U<<2);
	SYSCFG->EXTICR[0] &=~ (1U<<3);

	/*EXTx unmuask edilir(EXT0)*/
	EXTI->IMR |= (1U<<0);

	/*dusen kose interrupt triggerlenir*/
	EXTI->FTSR |= (1U<<0);

	/*NVIC EXTx yetk,ilendirilir(EXT0)*/
	NVIC_EnableIRQ(EXTI0_IRQn);

	/*Tum interruptlar yetkilendirlir*/
	__enable_irq();
}
