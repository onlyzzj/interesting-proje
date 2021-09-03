#include"qudong.h"

void zhixian(void)//前进
{
	in1=0;
	in2=1;
	in3=1;
	in4=0;	
} 
void stop(void)//停止
{
	in1=0;
	in2=0;
	in3=0;
	in4=0;
}
void houtui(void)//后退	
{
	in1=1;
	in2=0;
	in3=0;
	in4=1;
} 
void kuaizuozhuan(void)//快速左转
{
	in1=1;
	in2=0;
	in3=1;
	in4=0;
}
void kuaiyouzhuan(void)//快速右转
{
	in1=0;
	in2=1;
	in3=0;
	in4=1;
} 
void manzuozhuan(void)//慢左转
{
	in1=0;
	in2=0;
	in3=1;
	in4=0;
}
void manyouzhuan(void)//慢右转
{
	in1=0;
	in2=1;
	in3=0;
	in4=0;
}


void qudong(void)
{						 
	delay_us(1000);
	nRF24L01_Init();
	while(1)
	{
		nRF24L01_Set_RX_Mode();
		delay_ms(100);
		if(nRF24L01_RX_Data())
		{
			if(RX_Buffer[0]==0xfe)
			{
			   zhixian();
			} 
			if(RX_Buffer[0]==0xfb)
			{
				houtui();	
			}
			if(RX_Buffer[0]==0xfd)
			{
				manzuozhuan();
			}
			if(RX_Buffer[0]==0xf7)
			{
				manyouzhuan();	
			}
			if(RX_Buffer[0]==0xef)
			{
				kuaiyouzhuan();
			} 
			if(RX_Buffer[0]==0xdf)
			{
				stop();	
			}
			if(RX_Buffer[0]==0xbf)
			{
				kuaizuozhuan();
			}
		}
		else
		{
			in1=0;
			in2=0;
			in3=0;
			in4=0;
		}
	}
}
