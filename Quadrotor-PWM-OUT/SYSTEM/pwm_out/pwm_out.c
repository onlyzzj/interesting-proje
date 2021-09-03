#include "pwm_out.h"

 
void TIM1_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	     //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;    //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=10000-1;                     //自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler=42-1;                  //定时器分频
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;               //重复寄存器，用于自动更新pwm占空比
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);               //初始化定时器1
	
	
	
	

	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;                 //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;     //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;         //输出极性:TIM输出比较极性低
	TIM_OCInitStructure.TIM_Pulse=INIT_DUTY;                             //设置待装入捕获比较寄存器的脉冲值
	//下面几个参数是高级定时器才会用到，通用定时器不用配置
  TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_Low;          //设置互补端输出极性
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;     //使能互补端输出
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;          //死区后输出状态
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;      //死区后互补端输出状态


  //PWM1模式配置：通道1
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);                 //使能TIM14在CCR1上的预装载寄存器
	//PWM1模式配置：通道2
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Enable);
	//PWM1模式配置：通道3
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Enable);
	//PWM1模式配置：通道4
	TIM_OC4Init(TIM1,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);


                
 
	TIM_CtrlPWMOutputs(TIM1,ENABLE);                                 //高级定时器必须要写
  TIM_ARRPreloadConfig(TIM1,ENABLE); 
	TIM_Cmd(TIM1,ENABLE);
}
 




void PWM_Out_Init(void)
{		 					 	
	GPIO_InitTypeDef GPIO_InitStructure;
		  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE); 	
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;           
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;                    //复用功能
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;	            //速度100MHz
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;                  //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;                    //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); 
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1);
	
	TIM1_Init();	
}  







//PWM写入电机
void MOTOR_Run(s16 pwm[MOTOR_Num])
{		
	u8 i;
	for(i=0;i<MOTOR_Num;i++)
	{
		if(pwm[i]>MOTOR_Max)  
			pwm[i]=MOTOR_Max;		
		else if(pwm[i]<MOTOR_Min)  
			pwm[i]=MOTOR_Min;
	}
	TIM1->CCR1=INIT_DUTY+pwm[0]*PWM_RADIO;
	TIM1->CCR2=INIT_DUTY+pwm[1]*PWM_RADIO;
	TIM1->CCR3=INIT_DUTY+pwm[2]*PWM_RADIO;
	TIM1->CCR4=INIT_DUTY+pwm[3]*PWM_RADIO;
}



void MOTOR_Stop(void)
{
	TIM1->CCR1=INIT_DUTY;
	TIM1->CCR2=INIT_DUTY;
	TIM1->CCR3=6000;
//	TIM1->CCR4=INIT_DUTY;
	TIM1->CCR4=9999;
}
