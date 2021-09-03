#ifndef _PWM_OUT_H_
#define _PWM_OUT_H_
#include "stm32f4xx.h" 


#define MOTOR_Max 1000
#define MOTOR_Min 0
#define MOTOR_Num 4   //电机数目


#define INIT_DUTY 4000
#define PWM_RADIO 4


void PWM_Out_Init(void);
void TIM1_Init(void);
void MOTOR_Run(s16 pwm[MOTOR_Num]);
void MOTOR_Stop(void);


#endif
