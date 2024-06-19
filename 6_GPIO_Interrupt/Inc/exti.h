/*
 * exti.h
 *
 *  Created on: Nov 4, 2023
 *      Author: mthn_
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f4xx.h"

#define LINE0 	(1U<<0)

void PA0_EXTI_init(void);

#endif /* EXTI_H_ */
