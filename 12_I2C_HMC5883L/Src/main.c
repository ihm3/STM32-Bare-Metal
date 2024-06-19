//stm32 chip driver kullanımı
//@ihm3
//USART interupt

#include	<stdio.h>
#include 	<stdint.h>
#include 	"stm32f4xx.h"
#include	"usart.h"
#include	"I2C.h"

#define HMC5883L_ADDR   (0x1E)
#define HMC5883L_CR_A	 0x00
#define HMC5883L_CR_B	 0x01
#define HMC5883L_MR 	 0x02
#define HMC5883L_DATA	 0x03

#define CRA_CNFIG		 0x70
#define CRB_CNFIG		 0x80
#define MR_CMFIG		 0x00

char data[6];

int16_t x,y,z;

int main(void)
{

	init_I2C1();

	char wr_data[1];

	wr_data[0] = CRA_CNFIG;
	I2C1_WriteBytes(HMC5883L_ADDR, HMC5883L_CR_A, 1, wr_data);

	wr_data[0] = CRB_CNFIG;
	I2C1_WriteBytes(HMC5883L_ADDR, HMC5883L_CR_B, 1, wr_data);

	wr_data[0] = MR_CMFIG;
	I2C1_WriteBytes(HMC5883L_ADDR, HMC5883L_MR,   1, wr_data);


	while(1)
	{
		I2C1_ReadBytes(HMC5883L_ADDR, HMC5883L_DATA, 6, data);

		x = data[0]<<8 | data[1];
		y = data[2]<<8 | data[3];
		z = data[4]<<8 | data[5];
	}
}



