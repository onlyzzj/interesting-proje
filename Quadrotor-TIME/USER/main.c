#include "timer.h"
#include "led.h" 
#include "delay.h"



int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	delay_init(168);
	LED_Init();	
	TIM2_Init();
	while(1)
	{
		LED1_OFF;
	}
}

