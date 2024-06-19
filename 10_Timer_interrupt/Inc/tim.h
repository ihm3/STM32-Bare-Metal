/*
 * tim.h
 *
 *  Created on: Nov 4, 2023
 *      Author: mthn_
 */

#ifndef TIM_H_
#define TIM_H_

void init_Timer3_1hz(void);
void init_Timer3_1hz_interrupt(void);

#define SR_UIF	(1U<<0)// timer bayragı

#endif /* TIM_H_ */
