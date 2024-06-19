

#include 	"adc.h"
#include 	"stm32f4xx.h"


#define GPIOBEN			(1U<<1)
#define ADC1EN			(1U<<8)

#define CH8_First		(1U<<3)// sqr regıstırına (3 adet 3x32 bit) sondan baslıyacak sekılde 5 bit bloklar halinde kanal numarasını yazmak donusum sırasını belirler
#define Seq_Lenght		 0x00  // SQR1 regıstırı ayrıca donusum sayısını yoneten biti içerir 1 kanalda donusum yapılacagı ıcın regıstırı 0 lıyoruz

#define CR2_ADCON		(1U<<0)
#define CR2_SWSTART 	(1U<<30)
#define SR_EOC			(1U<<1)// donusum bittğinde 0 olan bit


void PB0_CH8_adc_init(void)
{
	/*PB0 analog olarak ayarlanır*/
	RCC->AHB1ENR |=	GPIOBEN;

	GPIOB->MODER |= (1U<<0);
	GPIOB->MODER |= (1U<<1);

	/*ADC modul ayarları*/
	//ADC1 clock erişimi
	RCC->APB2ENR |= ADC1EN;

	//adc sequansı ayarlarnır -- kanallar arasında donusum sırası burda belirlenir
	ADC1->SQR3 = CH8_First;

	//adc donusturulecek kanal sayısı SEQ1 de belirlenir
	ADC1->SQR1 = Seq_Lenght;

	//adc modulu yetkılerndirilir
	ADC1->CR2 |= CR2_ADCON;
}


void Start_ADC(void)
{
	//donusumu baslatma
	ADC1->CR2 |= CR2_SWSTART;
}

uint16_t analog_read(void)
{
	//donusum bittğinden emin olunmalı
	while(!(ADC1->SR & SR_EOC)){}

	return (ADC1->DR);
}
