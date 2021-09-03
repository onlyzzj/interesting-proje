#include "usart.h"	


u8 TxBuffer[256];
u8 TxCounter=0;
u8 count=0; 

 


void USART1_Init(u32 bound)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);   //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  //使能USART1时钟
 

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);  //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;    //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;             //复用功能
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	       //速度50MHz
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;           //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;             //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);                  //初始化PA9，PA10

  //USART1初始化设置
	USART_InitStructure.USART_BaudRate=bound;                                          //波特率设置
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                          //字长为8位数据格式
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                               //一个停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;                                  //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;      //无硬件数据流控制
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	                       //收发模式
  USART_Init(USART1,&USART_InitStructure);                                           //初始化串口1
	
	//Usart1 NVIC配置
  NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;                   //串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;             //抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;		                //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;			                //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                                    //根据指定的参数初始化VIC寄存器
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);     //使能接收中断
  USART_Cmd(USART1,ENABLE);                        //使能串口1 
	USART_ClearITPendingBit(USART1,USART_IT_TXE);
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}


 


void USART1_IRQHandler(void)
{
	u8 com_data;
  //接收中断
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		com_data=USART1->DR;
		USART_SendData(USART1,com_data);///////////////暂时使用
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除接收中断
	}
	//发送中断
	if(USART_GetITStatus(USART1,USART_IT_TXE))
	{	
		USART1->DR=TxBuffer[TxCounter++];         
		if(TxCounter==count)
		{
			USART_ITConfig(USART1,USART_IT_TXE,DISABLE);//关闭TXE（发送中断）中断
		}	
		USART_ClearITPendingBit(USART1,USART_IT_TXE);//清除发送中断		
	}
}



void USART1_Send(u8 *DataToSend,u8 data_num)
{
  u8 i;
	for(i=0;i<data_num;i++)
	{
		TxBuffer[count++]=*(DataToSend+i);
	}
	if(!USART_GetITStatus(USART1,USART_IT_TXE))
	{
		USART_ITConfig(USART1,USART_IT_TXE,ENABLE); //打开发送中断
	}
}


 



