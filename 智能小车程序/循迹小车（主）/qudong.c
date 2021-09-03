#include"qudong.h"

void zhixian(void)//前进
{
	in1=0;
	in2=1;
	in3=1;
	in4=0;	
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

