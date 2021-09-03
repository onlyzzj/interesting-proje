#include "eeprom.h" 
#include "iic.h"
#include "delay.h" 				 





//在AT24C02指定地址读出1个字节的数据
//BYTE_ADDRESS:开始读数的地址  
//temp:读到的数据
u8 AT24C02_Read_1Byte(u8 BYTE_ADDRESS)
{				  
	u8 temp;	
	IIC_Read_1Byte(AT24C02_ADDRESS,BYTE_ADDRESS,&temp);   
	return temp;
}






//在AT24C02指定地址写入1个字节的数据
//BYTE_ADDRESS:写入数据的目的地址    
//DATA:要写入的数据
void AT24C02_Write_1Byte(u8 BYTE_ADDRESS,u8 DATA)
{				
	IIC_Write_1Byte(AT24C02_ADDRESS,BYTE_ADDRESS,DATA);	
}








//在AT24C02里面的指定地址开始读出n个字节的数据
//BYTE_ADDRESS :开始读出的地址      AT24C02为0~255
//Buffer:数据数组首地址
//n:要读出数据的个数
void AT24C02_Read_nByte(u8 BYTE_ADDRESS,u8 *temp,u8 n)
{
	u8 i;
	for(i=0;i<n;i++)
	{
		*temp++=AT24C02_Read_1Byte(BYTE_ADDRESS++);	
	}
}  









//在AT24C02里面的指定地址开始写入n个字节的数据
//BYTE_ADDRESS :开始写入的地址      AT24C02为0~255
//Buffer:数据数组首地址
//n:要写入数据的个数
void AT24C02_Write_nByte(u8 BYTE_ADDRESS,u8 *temp,u8 n)
{
	u8 i;
	for(i=0;i<n;i++)
	{
		AT24C02_Write_1Byte(BYTE_ADDRESS++,*temp++);
	}
}










//在AT24C02里面的指定地址开始读出长度为16bit的数据
//BYTE_ADDRESS:开始读出的地址 
//temp:读出的数据
//2:要写入数据的字节长度
u16 AT24C02_Read_16Bit(u8 BYTE_ADDRESS)
{  	
	u8 i;
	u16 temp=0;
	for(i=0;i<2;i++)
	{
		temp<<=8;
		temp+=AT24C02_Read_1Byte(BYTE_ADDRESS+2-i-1); 	 				   
	}
	return temp;												    
}






//在AT24C02里面的指定地址开始写入长度为16bit的数据
//BYTE_ADDRESS:开始写入的地址  
//DATA:数据数组首地址
//2:要写入数据的字节长度
void AT24C02_Write_16Bit(u8 BYTE_ADDRESS,u16 DATA)
{  	
	u8 i;
	for(i=0;i<2;i++)
	{
		AT24C02_Write_1Byte(BYTE_ADDRESS+i,(DATA>>(8*i))&0xff);
	}												    
}






//在AT24C02里面的指定地址开始读出长度为32bit的数据
//BYTE_ADDRESS:开始读出的地址 
//temp:读出的数据
//4:要写入数据的字节长度
u32 AT24C02_Read_32Bit(u8 BYTE_ADDRESS)
{  	
	u8 i;
	u32 temp=0;
	for(i=0;i<4;i++)
	{
		temp<<=8;
		temp+=AT24C02_Read_1Byte(BYTE_ADDRESS+4-i-1); 	 				   
	}
	return temp;												    
}







//在AT24C02里面的指定地址开始写入长度为32bit的数据
//BYTE_ADDRESS:开始写入的地址  
//DATA:数据数组首地址
//4:要写入数据的字节长度
void AT24C02_Write_32Bit(u8 BYTE_ADDRESS,u32 DATA)
{  	
	u8 i;
	for(i=0;i<4;i++)
	{
		AT24C02_Write_1Byte(BYTE_ADDRESS+i,(DATA>>(8*i))&0xff);
	}												    
}














//检查AT24C02是否正常
//这里用了2402的最后一个地址(255)来存储标志字.
//返回0:检测失败
//返回1:检测成功
u8 AT24C02_Check(void)
{
	u8 temp;
	temp=AT24C02_Read_1Byte(255);          //避免每次开机都写AT24C02		   
	if(temp==0X55)
	{
		return 1;	
	}	
	else                                   //排除第一次初始化的情况
	{
		AT24C02_Write_1Byte(255,0X55);
		temp=AT24C02_Read_1Byte(255);	  
		if(temp==0X55)
			return 1;
	}
	return 0;											  
}





