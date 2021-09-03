#include "led.h" 



void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
  GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	LED1_OFF;//LED1Ãð
	LED2_OFF;//LED2Ãð	
}






