//stm32 chip driver kullanımı
//@ihm3
//TIMER1 capture toggle

/*
 *	Daha once toggle ettigimiz PB0 capture moduna alacagımız pine bağlanmalı
 */

#include	<stdio.h>
#include 	<stdint.h>
#include	"usart.h"
#include 	"adc.h"
#include	"tim.h"
#include 	"stm32f4xx.h"

/*
 *	Hardware PB0 :PA2
 */


int sec = 0;

int main(void)
{
	init_PB0_Timer3_Output();
	Timer2_Input_Capture();

	while(1)
	{
		// yukselis beklenir
		while(!(TIM2->SR & SR_CC3IF)){}

		//yakalanan kenar okunur(sayılır)
		sec = TIM2->CCR3;
	}
}
