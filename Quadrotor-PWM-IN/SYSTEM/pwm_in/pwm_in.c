#include "pwm_in.h"


u16 Rc_Pwm_In[8];



void TIM3_Init(void)
{
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	
	TIM_TimeBaseStructure.TIM_Period=0Xffff;                     //自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler=84-1;                    //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;    //向上计数模式
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
		
	
	//初始化TIM3输入捕获参数
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;                      //选择输入端IC1映射到TI1上
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;       //映射到TI1上
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;                 //配置输入分频,不分频       
  TIM_ICInitStructure.TIM_ICFilter=0x00;                               //IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter=0x00;
  TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter=0x00;
  TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter=0x00;
  TIM_ICInit(TIM3,&TIM_ICInitStructure);
  
	
	
  TIM_ITConfig(TIM3,TIM_IT_CC1,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_CC2,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_CC3,ENABLE);
	TIM_ITConfig(TIM3,TIM_IT_CC4,ENABLE);



  TIM_Cmd(TIM3, ENABLE);//使能定时器3
}

















void TIM4_Init(void)
{
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period=0Xffff;                     //自动重装载值
	TIM_TimeBaseStructure.TIM_Prescaler=84-1;                 //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	
	//初始化TIM4输入捕获参数
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter=0x00;
  TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter=0x00;
  TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter=0x00;
  TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter=0x00;
  TIM_ICInit(TIM4,&TIM_ICInitStructure);
	
	
  TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);  
 


	TIM_Cmd(TIM4, ENABLE);
}














void TIM3_IRQHandler(void)	
{
	static u16 temp_cnt1,temp_cnt1_2,temp_cnt2,temp_cnt2_2,temp_cnt3,temp_cnt3_2,temp_cnt4,temp_cnt4_2;
	if(TIM_GetITStatus(TIM3,TIM_IT_CC1)) 
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);
		TIM_ClearFlag(TIM3,TIM_FLAG_CC1OF);
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6))
		{
			temp_cnt1=TIM_GetCapture1(TIM3);
		}
		else
		{
			temp_cnt1_2=TIM_GetCapture1(TIM3);
			if(temp_cnt1_2>=temp_cnt1)
				Rc_Pwm_In[0]=temp_cnt1_2-temp_cnt1;
			else
				Rc_Pwm_In[0]=0xffff-temp_cnt1+temp_cnt1_2+1;
		}
	}
	
	
	
	
	if(TIM_GetITStatus(TIM3,TIM_IT_CC2)) 
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC2);
		TIM_ClearFlag(TIM3,TIM_FLAG_CC2OF);
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7))
		{
			temp_cnt2=TIM_GetCapture2(TIM3);
		}
		else
		{
			temp_cnt2_2=TIM_GetCapture2(TIM3);
			if(temp_cnt2_2>=temp_cnt2)
				Rc_Pwm_In[1]=temp_cnt2_2-temp_cnt2;
			else
				Rc_Pwm_In[1]=0xffff-temp_cnt2+temp_cnt2_2+1;
		}
	}
	
	
	
	if(TIM_GetITStatus(TIM3,TIM_IT_CC3)) 
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC3);
		TIM_ClearFlag(TIM3,TIM_FLAG_CC3OF);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0))
		{
			temp_cnt3=TIM_GetCapture3(TIM3);
		}
		else
		{
			temp_cnt3_2=TIM_GetCapture3(TIM3);
			if(temp_cnt3_2>=temp_cnt3)
				Rc_Pwm_In[2]=temp_cnt3_2-temp_cnt3;
			else
				Rc_Pwm_In[2]=0xffff-temp_cnt3+temp_cnt3_2+1;
		}
	}
	
	
	
	
	if(TIM_GetITStatus(TIM3,TIM_IT_CC4)) 
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC4);
		TIM_ClearFlag(TIM3,TIM_FLAG_CC4OF);
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))
		{
			temp_cnt4=TIM_GetCapture4(TIM3);
		}
		else
		{
			temp_cnt4_2=TIM_GetCapture4(TIM3);
			if(temp_cnt4_2>=temp_cnt4)
				Rc_Pwm_In[3]=temp_cnt4_2-temp_cnt4;
			else
				Rc_Pwm_In[3]=0xffff-temp_cnt4+temp_cnt4_2+1;
		}
	}
}

















void TIM4_IRQHandler(void)		
{
	static u16 temp_cnt1,temp_cnt1_2,temp_cnt2,temp_cnt2_2,temp_cnt3,temp_cnt3_2,temp_cnt4,temp_cnt4_2;
	if(TIM_GetITStatus(TIM4,TIM_IT_CC1)) 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_CC1);
		TIM_ClearFlag(TIM4,TIM_FLAG_CC1OF);
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12))
		{
			temp_cnt1=TIM_GetCapture1(TIM4);
		}
		else
		{
			temp_cnt1_2=TIM_GetCapture1(TIM4);
			if(temp_cnt1_2>=temp_cnt1)
				Rc_Pwm_In[4]=temp_cnt1_2-temp_cnt1;
			else
				Rc_Pwm_In[4]=0xffff-temp_cnt1+temp_cnt1_2+1;
		}
	}





	if(TIM_GetITStatus(TIM4,TIM_IT_CC2)) 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_CC2);
		TIM_ClearFlag(TIM4,TIM_FLAG_CC2OF);
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13))
		{
			temp_cnt2=TIM_GetCapture2(TIM4);
		}
		else
		{
			temp_cnt2_2=TIM_GetCapture2(TIM4);
			if(temp_cnt2_2>=temp_cnt2)
				Rc_Pwm_In[5]=temp_cnt2_2-temp_cnt2;
			else
				Rc_Pwm_In[5]=0xffff-temp_cnt2+temp_cnt2_2+1;
		}
	}






	if(TIM_GetITStatus(TIM4,TIM_IT_CC3)) 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_CC3);
		TIM_ClearFlag(TIM4,TIM_FLAG_CC3OF);
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14))
		{
			temp_cnt3=TIM_GetCapture3(TIM4);
		}
		else
		{
			temp_cnt3_2=TIM_GetCapture3(TIM4);
			if(temp_cnt3_2>=temp_cnt3)
				Rc_Pwm_In[6]=temp_cnt3_2-temp_cnt3;
			else
				Rc_Pwm_In[6]=0xffff-temp_cnt3+temp_cnt3_2+1;
		}
	}





	if(TIM_GetITStatus(TIM4,TIM_IT_CC4)) 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_CC4);
		TIM_ClearFlag(TIM4,TIM_FLAG_CC4OF);
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15))
		{
			temp_cnt4=TIM_GetCapture4(TIM4);
		}
		else
		{
			temp_cnt4_2=TIM_GetCapture4(TIM4);
			if(temp_cnt4_2>=temp_cnt4)
				Rc_Pwm_In[7]=temp_cnt4_2-temp_cnt4;
			else
				Rc_Pwm_In[7]=0xffff-temp_cnt4+temp_cnt4_2+1;
		}
	}
}


























void PWM_IN_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD,ENABLE);
	
//TIM3端口复用	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB,&GPIO_InitStructure);



  GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);
  

//TIM4端口复用
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
  GPIO_Init(GPIOD,&GPIO_InitStructure);


  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
	
	
	
	TIM3_Init();
	TIM4_Init();
}


