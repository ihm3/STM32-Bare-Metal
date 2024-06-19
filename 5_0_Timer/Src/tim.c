#include "stm32f4xx.h"

#define TIM3EN		(1U<<1)
#define CR1_CEN		(1U<<0)// timer enable biti

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
