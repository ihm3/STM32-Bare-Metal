//kutuphane olmadan ARM proglama(Kendi Driverimizi yazıyoruz)
//Designed by @ihm3


//PORT : C
//PIN  : 13


#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET) //AHP1 bus baslangic adresi

#define GPIOC_OFFSET 			(0x0800U)
#define GPIOC_BASE				(AHB1PERIPH_BASE + GPIOC_OFFSET)// GPIO C baslangic adresi

#define RCC_OFFSET 				(0x3800U)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET 			( 0x00UL)
#define GPIOC_MODE_R			(*(volatile unsigned int *)(GPIOC_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET 			(0x14UL)
#define GPIOC_OD_R				(*(volatile unsigned int *)(GPIOC_BASE + OD_R_OFFSET))

#define GPIOCEN 				(1U<<2) //0b0000 0000 0000 0000 0000 0000 0000 0100

#define PIN13					(1U<<13)
#define LED_PIN 			 	PIN13


/*
 * (1U<<26) // Sadece bit 26 : 1 olur
 * &=~(1u<<27) //Sadece bit 27 : 0 olur
 */


int main (void)
{
	/*1. GPIOC için clock erişimi saglanır*/
	RCC_AHB1EN_R |= GPIOCEN;
	/*2.PC13 output olorak tanımlanır*/
	GPIOC_MODE_R |= (1U<<26); // Sadece bit 26 : 1 olur
	GPIOC_MODE_R &=~(1u<<27); //Sadece bit 27 : 0 olur


	while(1)
	{
		/*3. PC13 1(high) olarak tanımlanır*/
		GPIOC_OD_R ^= LED_PIN;
		for(int i=0;i<100000;i++){}
	}
}
