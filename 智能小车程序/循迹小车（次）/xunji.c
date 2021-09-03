#include"xunji.h"	

int flag1=0;
int flag2=0;

void xunji(void)
{	
	   	if((HW1==1)&&(HW2==1)&&(HW3==1)&&(HW4==1))
		{
			zhixian(flag1,500,flag2,500);
		}
		else if((HW1==1)&&(HW2==1)&&(HW3==0)&&(HW4==0))//慢右转
		{
			youzhuan(flag1,500,flag2,200);
		}
		else if((HW1==0)&&(HW2==0)&&(HW3==1)&&(HW4==1))//慢左转
		{
			zuozhuan(flag1,200,flag2,500);
		}
		else if((HW1==0)&&(HW2==0)&&(HW3==0)&&(HW4==1))//快左转
		{    			      
			zuozhuan(flag1,200,flag2,700);
		}
		else if((HW1==1)&&(HW2==0)&&(HW3==0)&&(HW4==0))//快右转
		{
			youzhuan(flag1,700,flag2,200);
		}
}