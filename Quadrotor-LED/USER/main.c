#include "delay.h"
#include "led.h"



int main(void)
{  
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	while(1)
	{
		LED1_ON;
		LED2_OFF;
		delay_ms(500);
		LED1_OFF;
		LED2_ON;
		delay_ms(500);
	}
}
