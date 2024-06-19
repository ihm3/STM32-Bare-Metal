/*
 * adc.h
 *
 *  Created on: Nov 3, 2023
 *      Author: mthn_
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void PB0_CH8_adc_init(void);
void Start_ADC(void);
uint16_t analog_read(void);

#endif /* ADC_H_ */
