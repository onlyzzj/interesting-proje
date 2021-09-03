#include "common.h"
#include"qudong.h"
#include"xunji.h"

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
	while(1)
	{
		 xunji();
	}
}


void timer0() interrupt 1
{
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	flag1++;
	if(flag1>=1000)
	{
		flag1=0;
	}
	flag2++;
	if(flag2>=1000)
	{
		flag2=0;
	}			
}
