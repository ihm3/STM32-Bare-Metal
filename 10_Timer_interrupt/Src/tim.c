#include "stm32f4xx.h"

#define TIM3EN		(1U<<1)
#define CR1_CEN		(1U<<0)// timer enable biti
#define DIER_UIR	(1U<<0)// update interrupt yetki biti

void init_Timer3_1hz(void)
{
	//timer3 clock erişi saglanır
	RCC->APB1ENR |= TIM3EN;

	//prescaler secılır
	TIM3->PSC = 1600 - 1; //0 dan saymaya basladıgı ıcın 1 eksigi alınır
	/*
	 * 			      (PRESCELAR)  	(Autoreload)
	 *	 16 000 000 /    1 600     =   10 000
	 */

	//auto reload degeri ayarlanır
	TIM3->ARR = 10000 - 1;

	//counter 0 lanır
	TIM3->CNT = 0;

	// timer yetkilendirilir
	TIM3->CR1 |= CR1_CEN;
}

void init_Timer3_1hz_interrupt(void)
{
	//timer3 clock erişi saglanır
	RCC->APB1ENR |= TIM3EN;

	//prescaler secılır
	TIM3->PSC = 1600 - 1; //0 dan saymaya basladıgı ıcın 1 eksigi alınır
	/*
	 * 			      (PRESCELAR)  	(Autoreload)
	 *	 16 000 000 /    1 600     =   10 000
	 */

	//auto reload degeri ayarlanır
	TIM3->ARR = 10000 - 1;

	//counter 0 lanır
	TIM3->CNT = 0;

	// timer yetkilendirilir
	TIM3->CR1 |= CR1_CEN;

	//timer interrrupt biti setlenir
	TIM3->DIER |= DIER_UIR;

	//NVIC de timer int yetkilendirilir
	NVIC_EnableIRQ(TIM3_IRQn);
}
