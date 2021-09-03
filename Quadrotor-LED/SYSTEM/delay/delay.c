#include "delay.h"



static u8  fac_us=0;//us延时倍乘数			   
static u16 fac_ms=0;//ms延时倍乘数


//初始化延迟函数
void delay_init(u8 SYSCLK)                                   //SYSCLK:系统时钟
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);      //SYSTICK的时钟固定为HCLK时钟的1/8  =21
	fac_us=SYSCLK/8;                                           //代表每个us需要的systick时钟数     =21000
	fac_ms=(u16)fac_us*1000;                                   //代表每个ms需要的systick时钟数   
}								    


 

//延时nus
//注意:nus的值,不要大于(2^24-1)/21=798915us
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01;          //开始倒数 
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL=0X00;       //清空计数器	 
}



//延时nms
//注意:nms的值,不要大于(2^24-1)/21000=798ms 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
} 

			 



























