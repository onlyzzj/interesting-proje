#include "lcd12864.h"
#include "delay.h"


void write_com(uchar com)//д����
{
	rs=0;//д����
	delayms(5);
	rw=0;//д����
	en=0;//������д������
	DATAPORT=com;//д��������
	delayms(10);//�ȴ������ȶ�
	en=1;
	delayms(5);
	en=0;
}


void write_data(uchar dat)//д����
{
	rs=1;//д���� 
	delayms(5);
	rw=0;//д����
	en=0;//������д������
	DATAPORT=dat;//д��������
	delayms(10);//�ȴ������ȶ�
	en=1;
	delayms(5);
	en=0;
}


void init_lcd12864(void)//��ʼ��
{
	beiguang=0;	
	PSB = 1;//ѡ����ģʽ
	write_com(0x01);//��ʾ����
	delayms(5); 
	write_com(0x30);//��������
	delayms(5); 
	write_com(0x0c);//��ʾ��,�α��
	delayms(5);
}


void write_string(uchar x,uchar y,char *z)
{
	if(y==0)
	{
		write_com(0x80+x);
	}
	else if(y==1) 
	{
		write_com(0x90+x);	
	}
	else if(y==2) 
	{
		write_com(0x88+x);	
	}
	else if(y==3) 
	{
		write_com(0x98+x);	
	}
	while(*z)
	{
		write_data(*z);
		z++;
	}
}
