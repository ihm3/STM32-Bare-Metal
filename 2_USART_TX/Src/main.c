//stm32 chip driver kullanımı
//@ihm3
//USART TX

#include	<stdio.h>
#include 	<stdint.h>
#include 	"stm32f4xx.h"

#define GPIOAEN		(1U<<0)
#define UART1EN		(1U<<13)

#define FREQ		16000000
#define AHB2_CLK	FREQ
#define BOUDRATE 	115200

static void Set_Boudrate(USART_TypeDef* USARTx, uint32_t clk, uint32_t boudrate);
uint32_t init_USART1_TX(void);
void usart1_putchar(int ch);


int __io_putchar(int chr)//printf kullanımı için
{
	usart1_putchar(chr);
	return chr;
}


int main(void)
{
	init_USART1_TX();

	while(1)
	{
		//usart1_putchar('M');
		printf("merhaba Dünya....@ihm3\n\r");
	}
}



void usart1_putchar(int ch)
{
	/*Transmit data registerı bos olup olmadığı kontrol edilmeli*/
	while(!(USART1->SR & (1U<<7))){}

	/*DATA transmit data registerına yazılır*/
	USART1->DR = (ch & 0xFF);
}

uint32_t init_USART1_TX(void)//USART 1 kullanılacak : PA9
{
	/**************USART PIN AYARLARI******************/
	//1-GPIO clock erısımı yetkilendirilir
	RCC->AHB1ENR = GPIOAEN;

	//2-PA9 alternate function moduna ayarlanmalı
	GPIOA->MODER |=  (1U<<19);
	GPIOA->MODER &=~ (1U<<18);

	//3-PA9 alternate function tipi ayarlanmalı(AF07) GPIOA_AFRH : 0111
	GPIOA->AFR[1] |=  (1U<<4);
	GPIOA->AFR[1] |=  (1U<<5);
	GPIOA->AFR[1] |=  (1U<<6);
	GPIOA->AFR[1] &=~ (1U<<7);

	/**************USART MODULE AYARLARI**************/
	//1- USART modulu clock erısımı yetkilendirilir
	RCC->APB2ENR |=   (1U<<4);

	//2- BOUD RATE ayarlanır
	Set_Boudrate(USART1, AHB2_CLK, BOUDRATE);

	//3- Transfer yonu secılır(TX)
	USART1->CR1 = 	(1U<<3);// TE biti harici tum bitler 0 olur(diğer bitler 0 da defoult değerler)

	//4- USART modulu yetkilendirilir

	USART1->CR1 |=  UART1EN;//sadece UE(13.bit) 1 yapılır

	return 0;
}



static void Set_Boudrate(USART_TypeDef* USARTx, uint32_t clk, uint32_t boudrate)
{
	USARTx->BRR = ((clk + (boudrate/2U)) / boudrate);//BRR registerında boudrate ayarı
}
