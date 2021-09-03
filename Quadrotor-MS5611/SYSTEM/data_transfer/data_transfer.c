#include "data_transfer.h"
#include "usart.h"



u8 data_to_send[50];    //·¢ËÍÊý¾Ý»º´æ



void Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z)
{
	u8 i,_cnt=0,sum=0;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=(a_x>>8)&0XFF;
	data_to_send[_cnt++]=a_x&0XFF;
	data_to_send[_cnt++]=(a_y>>8)&0XFF;
	data_to_send[_cnt++]=a_y&0XFF;
	data_to_send[_cnt++]=(a_z>>8)&0XFF;
	data_to_send[_cnt++]=a_z&0XFF; 
	data_to_send[_cnt++]=(g_x>>8)&0XFF;
	data_to_send[_cnt++]=g_x&0XFF;
	data_to_send[_cnt++]=(g_y>>8)&0XFF;
	data_to_send[_cnt++]=g_y&0XFF;
	data_to_send[_cnt++]=(g_z>>8)&0XFF;
	data_to_send[_cnt++]=g_z&0XFF;
	data_to_send[_cnt++]=(m_x>>8)&0XFF;
	data_to_send[_cnt++]=m_x&0XFF;
	data_to_send[_cnt++]=(m_y>>8)&0XFF;
	data_to_send[_cnt++]=m_y&0XFF;
	data_to_send[_cnt++]=(m_z>>8)&0XFF;
	data_to_send[_cnt++]=m_z&0XFF;
	
	data_to_send[3]=_cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum+=data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	USART1_Send(data_to_send,_cnt);
}





void Send_Senser2(s32 bar_alt,u16 csb_alt)
{
	u8 i,_cnt=0,sum=0;
	
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x07;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=(bar_alt>>24)&0XFF;
	data_to_send[_cnt++]=(bar_alt>>16)&0XFF;
	data_to_send[_cnt++]=(bar_alt>>8)&0XFF;
	data_to_send[_cnt++]=bar_alt&0XFF;
	data_to_send[_cnt++]=(csb_alt>>8)&0XFF;
	data_to_send[_cnt++]=csb_alt&0XFF;
	
	data_to_send[3]=_cnt-4;
	
	for(i=0;i<_cnt;i++)
		sum+=data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	USART1_Send(data_to_send,_cnt);
}
