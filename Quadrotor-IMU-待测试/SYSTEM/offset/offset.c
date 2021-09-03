#include "offset.h"
 
 
 Xmax=0.37
 Xmin=-0.57
Ymax=0.44
Ymin=-0.49
x_temp=1;
y_temp=(Xmax-Xmin)/(Ymax-Ymin);
MagX=(Xmax-Xmin)/2-Xmax;   
MagY=(Ymax-Ymin)/2-Ymax;



void SYSTICK_INIT(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);                //时钟使能

	TIM_TimeBaseStructure.TIM_Period=0xffff;                           //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler=84-1;                          //设置用来作为TIMx时钟频率除数的预分频值  1Mhz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;              //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;          //TIM向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);                     //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_Cmd(TIM4, ENABLE);
}


float GET_NOWTIME(void)//返回当前systick计数器值,32位
{
	float temp=0 ;
	static uint32_t now=0; // 采样周期计数 单位 us

 	now=TIM4->CNT;//读高16位时间
   	TIM4->CNT=0;
	temp=(float)now/2000000.0f;          //换算成s，再除以2得出采样周期的一半

	return temp;
}