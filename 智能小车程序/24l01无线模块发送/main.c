#include "common.h"
#include "nRF24L01_TX.h"
#include"delay.h"


void main(void)
{
	P0=0xff;//初始化IO口
	P1=0xff;
	P2=0xff;
	P3=0xff;
	delay_us(100);
	nRF24L01_Init();//NRF24L01初始化
	while(1)
	{
		if(Key1==0)
		{
			delay_ms(10);
			if(Key1==0)
			{		
				nRF24L01_Set_TX_Mode(&TX_Buffer1[0]);//发送数据
				while(Check_Ack());//等待发送完成
				LED1=0;
				delay_ms(10);
			}
		}
		if(Key2==0)
		{
			delay_ms(10);
			if(Key2==0)
			{		
				nRF24L01_Set_TX_Mode(&TX_Buffer2[0]);//发送数据
				while(Check_Ack());//等待发送完成
				LED2=0;
				delay_ms(10);
			}
		}
		if(Key3==0)
		{
			delay_ms(10);
			if(Key3==0)
			{		
				nRF24L01_Set_TX_Mode(&TX_Buffer3[0]);//发送数据
				while(Check_Ack());//等待发送完成
				LED3=0;
				delay_ms(10);
			}
		}
		if(Key4==0)
		{
			delay_ms(10);
			if(Key4==0)
			{		
				nRF24L01_Set_TX_Mode(&TX_Buffer4[0]);//发送数据
				while(Check_Ack());//等待发送完成
				LED4=0;
				delay_ms(10);
			}
		}
//		if(Key5==0)
//		{
//			delay_ms(10);
//			if(Key5==0)
//			{		
//				nRF24L01_Set_TX_Mode(&TX_Buffer5[0]);//发送数据
//				while(Check_Ack());//等待发送完成
//				LED5=0;
//				delay_ms(10);
//			}
//		}
//		if(Key6==0)
//		{
//			delay_ms(10);
//			if(Key6==0)
//			{		
//				nRF24L01_Set_TX_Mode(&TX_Buffer6[0]);//发送数据
//				while(Check_Ack());//等待发送完成
//				LED6=0;
//				delay_ms(10);
//			}
//		}
//		if(Key7==0)
//		{
//			delay_ms(10);
//			if(Key7==0)
//			{		
//				nRF24L01_Set_TX_Mode(&TX_Buffer7[0]);//发送数据
//				while(Check_Ack());//等待发送完成
//				LED7=0;
//				delay_ms(10);
//			}
//		}
//		if(Key8==0)
//		{
//			delay_ms(10);
//			if(Key8==0)
//			{		
//				nRF24L01_Set_TX_Mode(&TX_Buffer8[0]);//发送数据
//				while(Check_Ack());//等待发送完成
//				LED8=0;
//				delay_ms(10);
//			}
//		}
		else
		{
			LED1=1;
			LED2=1;
			LED3=1;
			LED4=1;
			LED5=1;
			LED6=1;
			LED7=1;
			LED8=1;
		}			
	}
}