#include "stm32f4xx.h"

#define GPIOBEN		(1U<<1)
#define GPIOAEN		(1U<<0)

#define TIM2EN		(1U<<0)

#define TIM3EN		(1U<<1)
#define CR1_CEN		(1U<<0)// timer enable biti
#define TOGGLE_CH	(1U<<4 | 1U<<5)
#define CC3EN		(1U<<8)

#define CCER_CC3S	(1U<<0)

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


void init_PB0_Timer3_Output(void)
{
	//pb0 alternatif modda acılır
	RCC->AHB1ENR |= GPIOBEN;

	GPIOB->MODER &=~ (1U<<0);
	GPIOB->MODER |=  (1U<<1);

	GPIOB->AFR[0] |=	(1U<<1);


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

	//output compare toggle mode setlenir
	TIM3->CCMR2 = TOGGLE_CH;

	//compare mode yetkilendirilir (TIM3_CH3)(PB0)
	TIM3->CCER |= CC3EN;

	//counter 0 lanır
	TIM3->CNT = 0;

	// timer yetkilendirilir
	TIM3->CR1 |= CR1_CEN;
}

void Timer2_Input_Capture(void)// PA2 TIM2 CH3 input capture olarak kullanılacak
{
	//PA8 Aletnate function modunda acılır AF01
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER  &=~ 	(1U<<4);
	GPIOA->MODER  |=  	(1U<<5);

	GPIOA->AFR[0] |=	(1U<<8);

	//tim2 clock erişimi
	RCC->APB1ENR  |=	TIM2EN;

	//prescaler ayarlarlanır
	TIM2->PSC     = 	16000-1; // 16 000 000 / 16 000

	//TIM2 CH3 input mod
	TIM2->CCMR2   =		CCER_CC3S;

	//CH3 capture modu yükselen kenar (rising edge capture mode)
	TIM2->CCER 	  = 	CC3EN;

	//TIM2 yetkilendirilir
	TIM2->CR1 |= CR1_CEN;
}
