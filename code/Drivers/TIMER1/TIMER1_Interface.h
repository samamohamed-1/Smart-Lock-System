/*
 * TIMER1_int.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef TIMER1_TIMER1_INTERFACE_H_
#define TIMER1_TIMER1_INTERFACE_H_



void M_TIMER1_voidPwm1Init(void);
void M_TIMER1_voidPwm1SetTop(void);
void M_TIMER1_voidPwm1SetDutyCycle(u16 Copy_u8DutyCycle);
void M_TIMER1_voidPwm1Start(void);
void M_TIMER1_voidPwm1Stop(void);

#endif /* TIMER1_TIMER1_INTERFACE_H_ */
