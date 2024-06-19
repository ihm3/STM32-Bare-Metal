#include "usart.h"

#define GPIOAEN		(1U<<0)
#define UART1EN		(1U<<13)

#define FREQ		16000000
#define AHB2_CLK	FREQ
#define BOUDRATE 	115200

#define CR1_RXNEIE	(1U<<5)

//DMA defines
#define DMA2EN		(1U<<22)
#define CHSEL4		(1U<<27)// 3 bit halinnde binary olarak kanal numarı yazılır
#define DMA_MEM_INC	(1U<<10)
#define DMA_DIR		(1U<<6)//[7:6] 01 memory to periph
#define CR_TCIE		(1U<<4)
#define DMA_CR_EN	(1U<<0)

#define USART_CR3_DMAT (1U<<7)



static void Set_Boudrate(USART_TypeDef* USARTx, uint32_t clk, uint32_t boudrate);
void usart1_putchar(int ch);

int __io_putchar(int chr)//printf kullanımı için
{
	usart1_putchar(chr);
	return chr;
}

char usart1_read(void)
{
	while(!(USART1->SR & (1U<<5))){}
	return USART1->DR;
}

void usart1_putchar(int ch)
{
	/*Transmit data registerı bos olup olmadığı kontrol edilmeli*/
	while(!(USART1->SR & (1U<<7))){}

	/*DATA transmit data registerına yazılır*/
	USART1->DR = (ch & 0xFF);
}

void DMA2_stream7_init(uint32_t src, uint32_t dst, uint32_t len)//stream7 ch4
{
	//DMA clock erişimi
	RCC->AHB1ENR |= DMA2EN;

	//dma istenilen stream disable edilir
	DMA2_Stream7->CR &=~ DMA_CR_EN;

	//DMA Stream disable olana kadar beklenir
	while(DMA2_Stream7->CR & DMA_CR_EN){}

	//istenilen stream intreupptları resetlenir
	DMA2->HIFCR |= (1U<<22);// 1 yazmak biti clear lar
	DMA2->HIFCR |= (1U<<24);
	DMA2->HIFCR |= (1U<<25);
	DMA2->HIFCR |= (1U<<26);
	DMA2->HIFCR |= (1U<<27);

	// destination buffer setlernir
	DMA2_Stream7->PAR = dst;

	//source buffer setlenir
	DMA2_Stream7->M0AR = src;

	//lenght ayarlanır
	DMA2_Stream7->NDTR = len;

	//istenilen stream/ch secilir
	DMA2_Stream7->CR = CHSEL4;

	//bellek artışı enable edilir
	DMA2_Stream7->CR |= DMA_MEM_INC;

	//transfer yonu secılır
	DMA2_Stream7->CR |= DMA_DIR;

	//DMA transfer interrupt flg yetkilendirilir
	DMA2_Stream7->CR |= CR_TCIE;

	// direct mode yetkilendirlir ve FIFO disable edilir
	DMA2_Stream7->FCR = 0x00;// direct mode 0 da enable olur fifo 0 da disable olur bundan dolayı tum reg 0 lanır

	//istenilen stream/ch yetkilendirilir
	DMA2_Stream7->CR |= DMA_CR_EN;

	//uart1 tx bellek erişimi DMA için yetkilendirilir
	USART1->CR3 |= USART_CR3_DMAT;

	//nvic interruptı yetkılendirilir
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}

void init_USART1(void)//USART 1 kullanılacak : PA9&PA10
{
	/**************USART PIN AYARLARI******************/
	//1-GPIO clock erısımı yetkilendirilir
	RCC->AHB1ENR = GPIOAEN;

	//2-PA9 alternate function moduna ayarlanmalı
	GPIOA->MODER &=~ (1U<<18);
	GPIOA->MODER |=  (1U<<19);

	//PA10 alternate function moduna ayarlanmalı
	GPIOA->MODER &=~ (1U<<20);
	GPIOA->MODER |=  (1U<<21);

	//3-PA9 alternate function tipi ayarlanmalı(AF07) GPIOA_AFRH : 0111
	GPIOA->AFR[1] |=  (1U<<4);
	GPIOA->AFR[1] |=  (1U<<5);
	GPIOA->AFR[1] |=  (1U<<6);
	GPIOA->AFR[1] &=~ (1U<<7);

	//PA10 alternate function tipi ayarlanmalı(AF07) GPIOA_AFRH : 0111
	GPIOA->AFR[1] |=  (1U<<8);
	GPIOA->AFR[1] |=  (1U<<9);
	GPIOA->AFR[1] |=  (1U<<10);
	GPIOA->AFR[1] &=~ (1U<<11);

	/**************USART MODULE AYARLARI**************/
	//1- USART modulu clock erısımı yetkilendirilir
	RCC->APB2ENR |=   (1U<<4);

	//2- BOUD RATE ayarlanır
	Set_Boudrate(USART1, AHB2_CLK, BOUDRATE);

	//3- Transfer yonu secılır(TX)
	USART1->CR1 = ((1U<<3) | (1U<<2));// TE&RE biti harici tum bitler 0 olur(diğer bitler 0 da defoult değerler)


	//5- USART modulu yetkilendirilir
	USART1->CR1 |=  UART1EN;//sadece UE(13.bit) 1 yapılır

}

void init_USART1_interrupt(void)//USART 1 kullanılacak : PA9&PA10
{
	/**************USART PIN AYARLARI******************/
	//1-GPIO clock erısımı yetkilendirilir
	RCC->AHB1ENR = GPIOAEN;

	//2-PA9 alternate function moduna ayarlanmalı
	GPIOA->MODER &=~ (1U<<18);
	GPIOA->MODER |=  (1U<<19);

	//PA10 alternate function moduna ayarlanmalı
	GPIOA->MODER &=~ (1U<<20);
	GPIOA->MODER |=  (1U<<21);

	//3-PA9 alternate function tipi ayarlanmalı(AF07) GPIOA_AFRH : 0111
	GPIOA->AFR[1] |=  (1U<<4);
	GPIOA->AFR[1] |=  (1U<<5);
	GPIOA->AFR[1] |=  (1U<<6);
	GPIOA->AFR[1] &=~ (1U<<7);

	//PA10 alternate function tipi ayarlanmalı(AF07) GPIOA_AFRH : 0111
	GPIOA->AFR[1] |=  (1U<<8);
	GPIOA->AFR[1] |=  (1U<<9);
	GPIOA->AFR[1] |=  (1U<<10);
	GPIOA->AFR[1] &=~ (1U<<11);

	/**************USART MODULE AYARLARI**************/
	//1- USART modulu clock erısımı yetkilendirilir
	RCC->APB2ENR |=   (1U<<4);

	//2- BOUD RATE ayarlanır
	Set_Boudrate(USART1, AHB2_CLK, BOUDRATE);

	//3- Transfer yonu secılır(TX)
	USART1->CR1 = ((1U<<3) | (1U<<2));// TE&RE biti harici tum bitler 0 olur(diğer bitler 0 da defoult değerler)

	//RX interrupt biti setlenir
	USART1->CR1	|=	 CR1_RXNEIE;

	//NVIC te uart1 interruptı yetkilendirlir
	NVIC_EnableIRQ(USART1_IRQn);

	//5- USART modulu yetkilendirilir
	USART1->CR1 |=  UART1EN;//sadece UE(13.bit) 1 yapılır

}

static void Set_Boudrate(USART_TypeDef* USARTx, uint32_t clk, uint32_t boudrate)
{
	USARTx->BRR = ((clk + (boudrate/2U)) / boudrate);//BRR registerında boudrate ayarı
}
