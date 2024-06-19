//stm32 chip driver kullanımı
//@ihm3
//TIMER3 toggle PB0

#include	<stdio.h>
#include 	<stdint.h>
#include	"usart.h"
#include 	"adc.h"
#include	"tim.h"
#include 	"stm32f4xx.h"




unsigned long sec;

int main(void)
{

	init_PB0_Timer3_Output();

	while(1)
	{

	}
}
