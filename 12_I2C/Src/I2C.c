#include "I2C.h"

#define GPIOBEN		(1U<<1)
#define I2C1EN		(1U<<21)

#define I2C_100Khz	 			80 //0b 0101 0000
#define SD_MODEMAX_RISE_TIME	17
#define CR1_PE					(1U<<0)

#define SR2_BUSY	(1U<<1)
#define CR1_START	(1U<<8)
#define SR1_SB		(1U<<0)
#define SR1_ADDR	(1U<<1)
#define SR1_TXE		(1U<<7)
#define CR1_ACK		(1U<<10)
#define SR1_STOP	(1U<<9)
#define SR1_RXNE	(1U<<8)
#define SR1_BTF		(1U<<2)


void init_I2C1(void) // PB7 : SDA | PB6 : SCL olarak secildi
{
	// GPIO clock erısımı saglanır
	RCC->AHB1ENR |= GPIOBEN;

	// secılen pınler alternatıf fonksiyona ayarlanır
	GPIOB->MODER &=~ (1U<<12);//PB6
	GPIOB->MODER |=	 (1U<<13);

	GPIOB->MODER &=~ (1U<<12);//PB7
	GPIOB->MODER |=	 (1U<<13);

	//AF04 e gore ayarlanır
	GPIOB->AFR[0] &=~ (1U<<24);// 0
	GPIOB->AFR[0] &=~ (1U<<25);// 0
	GPIOB->AFR[0] |=  (1U<<26);// 1
	GPIOB->AFR[0] &=~ (1U<<27);// 0

	GPIOB->AFR[0] &=~ (1U<<28);// 0
	GPIOB->AFR[0] &=~ (1U<<29);// 0
	GPIOB->AFR[0] |=  (1U<<30);// 1
	GPIOB->AFR[0] &=~ (1U<<31);// 0

	// pinler output open drain olarak ayarlanır
	GPIOB->OTYPER |= (1U<<6);
	GPIOB->OTYPER |= (1U<<7);

	// pinler Pullup olarak yetkilendirilir
	GPIOB->PUPDR  |=	(1U<<12);//PB6 pullup
	GPIOB->PUPDR  &=~	(1U<<13);//PB6 pullup

	GPIOB->PUPDR  |=	(1U<<14);//PB7 pullup
	GPIOB->PUPDR  &=~	(1U<<15);//PB7 pullup

	// I2C modul clock erısımı saglanır
	RCC->APB1ENR  |=	I2C1EN;

	//I2C reset mode alınır
	I2C1->CR1 	  |= (1U<<15);

	//I2C reset moddan cıkarılır
	I2C1->CR1 	  &=~ (1U<<15);

	//I2C_CR2 de FREQ bloguna binary olarak istenilen frekans (Mhz olarak) yazılır
	I2C1->CR2	  |=  (1U<<4);//16 MHZ

	//I2C clok hız secımı(100khz secıldı--standart mod)
	I2C1->CCR	  =	   I2C_100Khz;

	//I2C rise time ayarlanır
	I2C1->TRISE	  =	   SD_MODEMAX_RISE_TIME;

	//I2C modul yetkilendirilir
	I2C1->CR1 	  |= (1U<<15);
}

void I2C1_reaByte(char AddrSlave, char AddrMemory, char* data)
{
	volatile int tmp;

	//bus bos olana kadar bekler
	while (I2C1->SR2 & SR2_BUSY){}

	//I2C baslatma
	I2C1->CR1 |= CR1_START;

	//baslatma bayragı setlenene kadar beklenir
	while (!(I2C1->SR1 & SR1_SB)){}

	//slave adresi yazılır(data reg e )
	I2C1->DR = AddrSlave << 1;

	// adres bayragı 1 olması beklenir
	while (!(I2C1->SR1 & SR1_ADDR)){}

	//adress bayragı 0 lanır : okundugu zaman bayrak sıfırlanır
	tmp = I2C1->SR2;

	//bellek adresi gonderilir
	I2C1->DR = AddrMemory;

	// data reg i 0 lanması beklenir
	while (!(I2C1->SR1 & SR1_TXE)){}

	//I2C tekrar baslatılır
	I2C1->CR1 |= CR1_START;

	//baslatma bayragı setlenene kadar beklenir
	while (!(I2C1->SR1 & SR1_SB)){}

	//slave adresi okunur(data reg)
	I2C1->DR = AddrSlave << 1 | 1;

	// adres bayragı 1 olması beklenir
	while (!(I2C1->SR1 & SR1_ADDR)){}

	// ACK dısable edilir
	I2C1->CR1 &=~ CR1_ACK;

	//adress bayragı 0 lanır : okundugu zaman bayrak sıfırlanır
	tmp = I2C1->SR2;

	//data gelince STOP biti generate edilir
	I2C1->CR1 |= SR1_STOP;

	//recive data bayragı beklenir
	while (!(I2C1->SR1 & SR1_RXNE)){}

	// data reg i okunur
	*data++ = I2C1->DR;
}

void I2C1_ReadBytes(char AddrSlave, char AddrMemory, int len,  char* data)
{
	volatile int tmp;

	//bus bos olana kadar bekler
	while (I2C1->SR2 & SR2_BUSY){}

	//I2C baslatma
	I2C1->CR1 |= CR1_START;

	//baslatma bayragı setlenene kadar beklenir
	while (!(I2C1->SR1 & SR1_SB)){}

	//slave adresi yazılır(data reg e )
	I2C1->DR = AddrSlave << 1;

	// adres bayragı 1 olması beklenir
	while (!(I2C1->SR1 & SR1_ADDR)){}

	//adress bayragı 0 lanır : okundugu zaman bayrak sıfırlanır
	tmp = I2C1->SR2;

	// data reg i 0 lanması beklenir
	while (!(I2C1->SR1 & SR1_TXE)){}

	//I2C tekrar baslatılır
	I2C1->CR1 |= CR1_START;

	//baslatma bayragı setlenene kadar beklenir
	while (!(I2C1->SR1 & SR1_SB)){}

	//slave adresi okunur(data reg)
	I2C1->DR = AddrSlave << 1 | 1;

	// adres bayragı 1 olması beklenir
	while (!(I2C1->SR1 & SR1_ADDR)){}

	//adress bayragı 0 lanır : okundugu zaman bayrak sıfırlanır
	tmp = I2C1->SR2;

	// ACK dısable edilir
	I2C1->CR1 &=~ CR1_ACK;

	while(len > 0U)
	{
		//her byt a ack dicable edilir
		if(len == 1U)
		{
			//ack disable
			I2C1->CR1 &=~ CR1_ACK;

			//data gelince STOP biti generate edilir
			I2C1->CR1 |= SR1_STOP;

			//recive data bayragı beklenir
			while (!(I2C1->SR1 & SR1_RXNE)){}

			// data reg i okunur
			*data++ = I2C1->DR;

			break;
		}else
		{
			//recive data bayragı beklenir
			while (!(I2C1->SR1 & SR1_RXNE)){}

			// data reg i okunur
			*data++ = I2C1->DR;

			len--;
		}
	}
}

void I2C1_WriteBytes(char AddrSlave, char AddrMemory, int len,  char* data)
{
	volatile int tmp;

	//bus bos olana kadar bekler
	while (I2C1->SR2 & SR2_BUSY){}

	//I2C baslatma
	I2C1->CR1 |= CR1_START;

	//baslatma bayragı setlenene kadar beklenir
	while (!(I2C1->SR1 & SR1_SB)){}

	//slave adresi yazılır(data reg e )
	I2C1->DR = AddrSlave << 1;

	// adres bayragı 1 olması beklenir
	while (!(I2C1->SR1 & SR1_ADDR)){}

	//adress bayragı 0 lanır : okundugu zaman bayrak sıfırlanır
	tmp = I2C1->SR2;

	// data reg i 0 lanması beklenir
	while (!(I2C1->SR1 & SR1_TXE)){}

	//bellek adresi gonderilir
	I2C1->DR = AddrMemory;

	for (int i = 0; i < len; i++)
	{
		// data reg i 0 lanması beklenir
		while (!(I2C1->SR1 & SR1_TXE)){}

		//yazılır
		I2C1->DR = *data++;
	}

	//transferin bitmesi beklenir
	while (!(I2C1->SR1 & SR1_BTF)){}

	//ı2c biter
	I2C1->CR1 |= SR1_STOP;
}



