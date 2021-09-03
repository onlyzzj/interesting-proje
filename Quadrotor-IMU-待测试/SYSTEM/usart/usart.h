#ifndef __USART_H
#define __USART_H
#include "stm32f4xx.h" 

	  	


void USART1_Init(u32 bound);
void USART1_IRQHandler(void);
void USART1_Send(u8 *DataToSend,u8 data_num);
	




#endif


