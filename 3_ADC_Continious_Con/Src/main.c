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
	PB0_CH8_adc_init();

	while(1)
	{
		Start_ADC();
		adcData = analog_read();
		printf("ADC val : %d", adcData);
	}
}
