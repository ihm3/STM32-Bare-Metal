
#include "SPI.h"

#define GPIOAEN	(1U<<0)
#define SPI1EN	(1U<<12)

#define CR1_CPOL		(1U<<0)
#define CR1_CPHA		(1U<<1)
#define CR1_RXONLY		(1U<<10)
#define CR1_LSBFIRST	(1U<<7)
#define CR1_MASTER		(1U<<2)
#define CR1_DFF			(1U<<11)
#define CR1_SSM			(1U<<9)
#define CR1_SSI			(1U<<8)
#define CR1_SPE			(1U<<6)

#define SR_TXE			(1U<<1)
#define SR_BUSY			(1U<<7)
#define SR_RXNE			(1U<<0)

/*
 *
 * 		PA9 --- SS
 * 		PA6 --- MISO
 * 		PA7 --- MOSI
 * 		PA5 --- CLK
 *
 */



void init_SPI1(void)
{
	// pinler için port clok erişimi
	RCC->AHB1ENR |= GPIOAEN;

	// cs harici pinler alternatif modda acılır
	GPIOA->MODER &=~ (1U<<10);//PA5
	GPIOA->MODER |=  (1U<<11);

	GPIOA->MODER &=~ (1U<<12);//PA6
	GPIOA->MODER |=  (1U<<13);

	GPIOA->MODER &=~ (1U<<14);//PA7
	GPIOA->MODER |=  (1U<<15);

	//CS pini output modda acılır
	GPIOA->MODER |=  (1U<<18);
	GPIOA->MODER &=~ (1U<<19);//PA9

	//Alternate Functiın tipi ayarlanır : AF05
	GPIOB->AFR[0] |=  (1U<<20);// 1   --PA5
	GPIOB->AFR[0] &=~ (1U<<21);// 0
	GPIOB->AFR[0] |=  (1U<<22);// 1
	GPIOB->AFR[0] &=~ (1U<<23);// 0

	GPIOB->AFR[0] |=  (1U<<24);// 1   --PA6
	GPIOB->AFR[0] &=~ (1U<<25);// 0
	GPIOB->AFR[0] |=  (1U<<26);// 1
	GPIOB->AFR[0] &=~ (1U<<27);// 0

	GPIOB->AFR[0] |=  (1U<<28);// 0   --PA7
	GPIOB->AFR[0] &=~ (1U<<29);// 0
	GPIOB->AFR[0] |=  (1U<<30);// 1
	GPIOB->AFR[0] &=~ (1U<<31);// 0
}

void config_SPI1(void)
{
	//SPI modulu clock erişimi
	RCC->APB2ENR |= SPI1EN;

	//SPI clock ayarı (br blogu 001 olunca FREQ/4)
	SPI1->CR1 |=  (1U<<3);
	SPI1->CR1 &=~ (1U<<4);
	SPI1->CR1 &=~ (1U<<5);

	//CPOL : 1 CPHA : 1
	SPI1->CR1 |=  CR1_CPOL;
	SPI1->CR1 |=  CR1_CPHA;

	// full duplex mod ayarlanır -- sadece RX
	SPI1->CR1 |= CR1_RXONLY;

	//MSB ilk olacak sekılde ayarlanır
	SPI1->CR1 &=~ CR1_LSBFIRST;//LSBFIRST biti 0 olunca MSBFIRST olur

	//MASTER mode ayarlanır
	SPI1->CR1 |= CR1_MASTER;

	//8 bit data moduna alınır
	SPI1->CR1 &=~ CR1_DFF;

	//Sowftware slave yonetim  SSM : 1 SSI : 1
	SPI1->CR1 |= CR1_SSM;
	SPI1->CR1 |= CR1_SSI;

	// SPI modulue enable edilir
	SPI1->CR1 |= CR1_SPE;
}

void send_SPI1(uint8_t *data, uint32_t size)
{
	uint32_t m = 0;
	uint8_t tmp;

	while(m < size)
	{
		// TXE set olana kadar beklenir
		while(!(SPI1->SR & SR_TXE)){}

		//data regine veri yazılır
		SPI1->DR = data[m];

		m++;
	}

	// TXE set olana kadar beklenir
	while(!(SPI1->SR & SR_TXE)){}

	//busy flg set olana kadar beklenir
	while(!(SPI1->SR & SR_BUSY)){}

	// OVR flg ı clearlanır
	tmp = SPI1->DR;
	tmp = SPI1->SR;
}

void read_SPI1(uint8_t *data, uint32_t size)
{
	while(size)
	{
		//fake data gonderilir
		SPI1->DR = 0;

		//RXNE bayragı beklenir
		while(!(SPI1->SR & SR_RXNE)){}

		//DATA reginden veri okunur
		*data++ = SPI1->DR;
		size--;
	}
}

void enable_CS1(FunctionalState status)
{
	switch(status)
	{
	case ENABLE :
		GPIOA->ODR &=~ (1U<<9);// CS : 0 --> enable    PA9
		break;
	case DISABLE :
		GPIOA->ODR |=  (1U<<9);// CS : 1 --> disable   PA9
		break;
	}
}


