#include "common.h"
#include"xunji.h"
#include"key.h"

int flag1=0;
int flag2=0;

void init_timer0(void)//定时器0初始化
{
	TMOD=0x01;//定时器0工作于方式1
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	TR0=1;
	ET0=1;
	EA=1;
}

void main()
{
	init_timer0();
	EN1=0;
	EN2=0;
	in1=0;
	in2=1;
	in3=1;
	in4=0;
	while(1)
	{
	 	zuo_speed_high();
		zuo_speed_low();
		you_speed_high();
		you_speed_low();
		xunji();
	}
}


void timer0() interrupt 1
{
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	flag1++;
	if(flag1>=100)
	{
		flag1=0;
	}
	if(flag1>=x)
	{
		EN1=1;
	}
	else
	{
		EN1=0;
	}
	flag2++;
	if(flag2>=100)
	{
		flag2=0;
	}
	if(flag2>=y)
	{
		EN2=1;
	}
	else
	{
		EN2=0;
	}
			
}



