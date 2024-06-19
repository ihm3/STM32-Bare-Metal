//ARM CHIP Driver yazımı
//@ihm3

//PORT : C
//PIN  : 13

#include <stdint.h>



#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET) //AHP1 bus baslangic adresi(AHP1 bus start addrs)

#define GPIOC_OFFSET 			(0x0800U)
#define GPIOC_BASE				(AHB1PERIPH_BASE + GPIOC_OFFSET)// GPIO C baslangic adresi(GPIOC Start addrs)

#define RCC_OFFSET 				(0x3800U)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOCEN 				(1U<<2) //0b0000 0000 0000 0000 0000 0000 0000 0100

#define PIN13					(1U<<13)
#define LED_PIN 			 	PIN13


typedef struct
{
	volatile uint32_t MODER;// mode register struct sekilinde tanımlandı //moder register
	volatile uint32_t DUMMY[4];//ODR registrına kadar olan regıstırlarla işimiz olmadığı için kapladığı byte kadar  FAKE tanımlama yapıyoruz
	volatile uint32_t ODR;//ODR regıster
}GPIO_TypeDef;


typedef struct
{
	volatile uint32_t DUMMY[12];//Fake
	volatile uint32_t AHB1ENR;
}RCC_TypeDef;


#define RCC				((RCC_TypeDef*) RCC_BASE)// RCC adında
#define GPIOC			((GPIO_TypeDef*) GPIOC_BASE)



int main (void)
{
	/*1.GPIOC clock erişimi // ENABLE clock access to GPIOC*/
	//RCC_AHB1EN_R |= GPIOCEN;
	RCC->AHB1ENR |= GPIOCEN;


	/*2.PC13 output olarak tanımlanır //Set PC13 as output*/
	//GPIOC_MODE_R |= (1U<<26); // Sadece bit 26 : 1 olur
	//GPIOC_MODE_R &=~(1u<<27); //Sadece bit 27 : 0 olur
	GPIOC->MODER |= (1U<<26);
	GPIOC->MODER &=~(1u<<27);


	while(1)
	{
		/*3.PC13 acık konumuna getirilir(1--HIGH) set PC13 high*/
		//GPIOC_OD_R ^= LED_PIN;

		GPIOC->ODR ^= LED_PIN;

		for(int i=0;i<100000;i++){}
	}
}

