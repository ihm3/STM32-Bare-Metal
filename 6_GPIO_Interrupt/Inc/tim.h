/*
 * tim.h
 *
 *  Created on: Nov 4, 2023
 *      Author: mthn_
 */

#ifndef TIM_H_
#define TIM_H_


#define SR_UIF		(1U<<0)// timer bayragı
#define SR_CC3IF	(1U<<3)

void init_Timer3_1hz(void);
void init_PB0_Timer3_Output(void);
void Timer2_Input_Capture(void);


#endif /* TIM_H_ */
