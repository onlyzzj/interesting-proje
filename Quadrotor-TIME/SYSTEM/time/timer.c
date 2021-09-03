#include "timer.h"
#include "led.h"
#include "delay.h"



void TIM2_Init(void)//1ms产生一个中断   1000*84/84M=0.001s
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);            //使能TIM3时钟
	 
  TIM_TimeBaseInitStructure.TIM_Period=5000-1; 	                 //自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=8400-1;                  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);             //初始化TIM3
	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;                  //定时器2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;     //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;            //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                       //允许定时器3更新中断
	TIM_Cmd(TIM2,ENABLE);                                          //使能定时器3
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	
}



//定时器2中断服务函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)) //溢出中断
	{
		LED1_ON;
		delay_ms(500);
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
	}
}
