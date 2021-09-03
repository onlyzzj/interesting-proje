#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h" 




#define LED1_ON 	GPIO_ResetBits(GPIOE, GPIO_Pin_5)     //GPIOE->BSRRH=GPIO_Pin_5//LED1ÁÁ
#define LED1_OFF  GPIO_SetBits(GPIOE, GPIO_Pin_5)       //GPIOE->BSRRL=GPIO_Pin_5//LED1Ãð
#define LED2_ON  	GPIO_ResetBits(GPIOE, GPIO_Pin_6)     //GPIOE->BSRRH=GPIO_Pin_6//LED2ÁÁ
#define LED2_OFF 	GPIO_SetBits(GPIOE, GPIO_Pin_6)       //GPIOE->BSRRL=GPIO_Pin_6//LED2Ãð	



void LED_Init(void);


#endif
