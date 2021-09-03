#ifndef _PWM_IN_H_
#define _PWM_IN_H_
#include "stm32f4xx.h"



void TIM3_Init(void);
void TIM4_Init(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void PWM_IN_Init(void);

extern u16 Rc_Pwm_In[8];



#endif
