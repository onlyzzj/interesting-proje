#include"qudong.h"


void zuoqianjin(void)//左前进
{
	in3=1;
	in4=0;	
} 

void zuohoutui(void)//左后退	
{
	in3=0;
	in4=1;
} 

void youqianjin(void)//右前进
{
	in1=0;
	in2=1;	
} 

void youhoutui(void)//右后退	
{
	in1=1;
	in2=0;
} 


void zuo_speed(uint x,uint y)
{
	if(x<=y)
		EN1=1;
	else
		EN1=0;
}

void you_speed(uint x,uint y)
{
	if(x<=y)
		EN2=1;
	else
		EN2=0;
}

void zhixian(uint x1,uint y1,uint x2,uint y2)//前进
{
	zuoqianjin();
	youqianjin();
	zuo_speed(x1,y1);
	you_speed(x2,y2);	
} 

void zuozhuan(uint x1,uint y1,uint x2,uint y2)//左转
{
	zuoqianjin();
	youqianjin();
	zuo_speed(x1,y1);
	you_speed(x2,y2);
}
void youzhuan(uint x1,uint y1,uint x2,uint y2)//右转
{
	zuoqianjin();
	youqianjin();
	zuo_speed(x1,y1);
	you_speed(x2,y2);
} 


