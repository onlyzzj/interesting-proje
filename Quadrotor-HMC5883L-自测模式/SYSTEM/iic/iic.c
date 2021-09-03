#include "iic.h"
#include "delay.h"



void IIC_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


//IIC起始信号
u8 IIC_Start(void)
{
	SDA_H;
	SCL_H;
	delay_us(1);//延时5us
	if(!SDA_read) return 0;	//SDA线为低电平则总线忙,退出
	SDA_L;
	delay_us(1);//延时5us
	if(SDA_read)  return 0;	//SDA线为高电平则总线出错,退出
	SDA_L;
	delay_us(1);//延时5us
	return 1;	
}


//IIC停止信号
void IIC_Stop(void)
{
	SCL_L;
	delay_us(1);//延时5us
	SDA_L;
	delay_us(1);//延时5us
	SCL_H;
	delay_us(1);//延时5us
	SDA_H;
	delay_us(1);//延时5us
}



//IIC应答信号
void IIC_Ask(void)
{
	SCL_L;
	delay_us(1);//延时5us
	SDA_L;
	delay_us(1);//延时5us
	SCL_H;
	delay_us(1);//延时5us
	SCL_L;
	delay_us(1);//延时5us
}



//IIC非应答信号
void IIC_NoAsk(void)
{
	SCL_L;
	delay_us(1);//延时5us
	SDA_H;
	delay_us(1);//延时5us
	SCL_H;
	delay_us(1);//延时5us
	SCL_L;
	delay_us(1);//延时5us
}




u8 IIC_WaitAsk(void) 	 //返回为:=0无ASK,=1有ASK
{
	SCL_L;
	delay_us(1);//延时5us
	SDA_H;			
	delay_us(1);//延时5us
	SCL_H;
	delay_us(1);//延时5us
	if(SDA_read)
	{
		SCL_L;
		delay_us(1);//延时5us
		return 0;
	}
	SCL_L;
	delay_us(1);//延时5us
	return 1;
}



//向IIC总线发送一个字节数据
void IIC_SendByte(u8 SendByte)         //数据从高位到低位//
{
	u8 i=8;
	while(i--)
	{
		SCL_L;
		delay_us(1);//延时5us
		if(SendByte&0x80)
			SDA_H;  
		else 
			SDA_L;   
		SendByte<<=1;
		delay_us(1);//延时5us
		SCL_H;
		delay_us(1);//延时5us
	}
	SCL_L;
}  




//从IIC总线接收一个字节数据
u8 IIC_ReadByte(void)            //数据从高位到低位//
{ 
	u8 i=8;
	u8 ReceiveByte=0;
	SDA_H;				
	while(i--)
	{
		ReceiveByte<<=1;      
		SCL_L;
		delay_us(1);//延时5us
		SCL_H;
		delay_us(1);//延时5us	
		if(SDA_read)
		{
			ReceiveByte|=0x01;
		}
	}
	SCL_L;
	return ReceiveByte;
} 




//向IIC设备写入一个字节数据
u8 IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
	if(!IIC_Start())return 0;
	IIC_SendByte(SlaveAddress+0);   
	if(!IIC_WaitAsk())
	{
		IIC_Stop();
		return 0;
	}
	IIC_SendByte(REG_Address);       
	IIC_WaitAsk();	
	IIC_SendByte(REG_data);
	IIC_WaitAsk();   
	IIC_Stop(); 
	return 1;
}




//从IIC设备读取一个字节数据
u8 IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 *REG_data)
{  
	if(!IIC_Start())return 0;
	IIC_SendByte(SlaveAddress+0); 
	if(!IIC_WaitAsk())
	{
		IIC_Stop();
		return 0;
	}
	IIC_SendByte(REG_Address);     
	IIC_WaitAsk();
	IIC_Start();
	IIC_SendByte(SlaveAddress+1);
	IIC_WaitAsk();
	*REG_data=IIC_ReadByte();
	IIC_NoAsk();
	IIC_Stop();
	return 1;
}	




//向IIC设备写入n个字节数据
u8 IIC_Write_nByte(u8 SlaveAddress,u8 REG_Address,u8 len,u8 *buf)
{	
	if(!IIC_Start())return 0;
	IIC_SendByte(SlaveAddress+0); 
	if(!IIC_WaitAsk())
	{
		IIC_Stop();
		return 0;
	}
	IIC_SendByte(REG_Address); 
	IIC_WaitAsk();
	while(len--) 
	{
		IIC_SendByte(*buf++); 
		IIC_WaitAsk();
	}
	IIC_Stop();
	return 1;
}




//从IIC设备读取n个字节数据
u8 IIC_Read_nByte(u8 SlaveAddress,u8 REG_Address,u8 len,u8 *buf)
{	
	if(!IIC_Start())return 0;
	IIC_SendByte(SlaveAddress+0); 
	if(!IIC_WaitAsk())
	{
		IIC_Stop();
		return 0;
	}
	IIC_SendByte(REG_Address); 
	IIC_WaitAsk();
	IIC_Start();
	IIC_SendByte(SlaveAddress+1); 
	IIC_WaitAsk();
	while(len) 
	{
		if(len==1)
		{
			*buf=IIC_ReadByte();
			IIC_NoAsk();
		}
		else
		{
			*buf=IIC_ReadByte();
			IIC_Ask();
		}
		buf++;
		len--;
	}
	IIC_Stop();
	return 1;
}





