//stm32 chip driver kullanımı
//@ihm3
//ADC

#include	<stdio.h>
#include 	<stdint.h>
#include	"usart.h"
#include 	"adc.h"
#include 	"stm32f4xx.h"



uint16_t adcData;

int main(void)
{

	init_USART1();
	PB0_CH8_adc_interrupt_init();
	Start_ADC();

	while(1)
	{

	}
}

void ADC_IRQHandler(void)
{
	//EOC biti kontrol edilir
	if(ADC1->SR & SR_EOC)
	{
		//SR sıfırlanır
		ADC1->SR &=~ SR_EOC;

		//code..
		adcData = ADC1->DR;
		printf("ADC val : %d", adcData);
	}
}
