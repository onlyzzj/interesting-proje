#ifndef __DMA_ADC_H
#define __DMA_ADC_H	
#include "stm32f4xx.h" 


extern u16 ADC_Buffer[1];


void ADC1_CH5_Config(void);
void DMA2_CH0_STREAM0_Config(void);
void ADC1_CH5_DMA2_CH0_STREAM0_Init(void);



#endif 
