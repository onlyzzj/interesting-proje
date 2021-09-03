#include "ms5611.h"
#include "iic.h"
#include "delay.h"



u16 C[7];
double dT,Temperature,Temperature2,Pressure,OFF,SENS,OFF2,SENS2;




void MS5611_Reset(void)
{
	IIC_Start();
	IIC_SendByte(MS5611_ADDRESS+0);   
  IIC_WaitAsk();
	IIC_SendByte(MS5611_RESET);
	IIC_WaitAsk();   
	IIC_Stop(); 
}




void MS5611_PROM_Read(void)          //读取PROM
{
	u8 i,temp1[2];
	for(i=0;i<=6;i++)
	{
		IIC_Read_nByte(MS5611_ADDRESS,PROM_READ_1+(i*2),2,temp1);
		C[i]=temp1[0]<<8|temp1[1];
	}
}




void MS5611_ADC_Conversion(u8 command) //数模转换
{
	IIC_Start();
	IIC_SendByte(MS5611_ADDRESS+0); 
	IIC_WaitAsk();
	IIC_SendByte(command); 
	IIC_WaitAsk();
	IIC_Stop();
	delay_ms(10);   //数模转换时间：     4096--要延时>>9.04ms      2048--要延时>>4.54ms       1024--要延时>>2.28ms      512--要延时>>1.17ms         256--要延时>>0.60ms
}




u32 MS5611_ADC_Read(void)         //读取ADC
{	
	u32 num;
	u8 temp2[3];
	IIC_Start();
	IIC_SendByte(MS5611_ADDRESS+0); 
	IIC_WaitAsk();
	IIC_SendByte(ADC_READ); 
	IIC_WaitAsk();
	IIC_Start();
	IIC_SendByte(MS5611_ADDRESS+1); 
	IIC_WaitAsk();
	
	temp2[0]=IIC_ReadByte();
	IIC_Ask();
	temp2[1]=IIC_ReadByte();
	IIC_Ask();
	temp2[2]=IIC_ReadByte();
	IIC_NoAsk();
	IIC_Stop();
	num=temp2[0]<<16|temp2[1]<<8|temp2[2];
	return num;
}



void MS5611_Get_Temperature(u8 D2_OSR_Temperature)                   //算出温度值的100倍，2007表示20.07°C
{ 
	u32 D2;
	MS5611_ADC_Conversion(D2_OSR_Temperature);
	D2=MS5611_ADC_Read();	
	dT=D2-(((u32)C[5])*256);
	Temperature=2000+dT*((u32)C[6])/8388608.0;	                     
}





void MS5611_Get_Pressure(u8 D1_OSR_Pressure)                         //算出气压值的100倍，100009表示1000.09mbar
{
	u32 D1;
	MS5611_ADC_Conversion(D1_OSR_Pressure);
	D1=MS5611_ADC_Read();	
	OFF=((u32)C[2])*65536+((u32)C[4])*dT/128.0;
	SENS=((u32)C[1])*32768+((u32)C[3])*dT/256.0;

	//二阶温度补偿
	if(Temperature<2000)                                               //与20°C比较
	{
		Temperature2=(dT*dT)/2147483648.0;                               //2147483648 or 0x80000000
		OFF2=5*(Temperature-2000)*(Temperature-2000)/2.0;
		SENS2=5*(Temperature-2000)*(Temperature-2000)/4.0;
		if(Temperature<-1500)                                            //与-15°C比较
		{
			OFF2=OFF2+7*(Temperature+1500)*(Temperature+1500);
			SENS2=SENS+11*(Temperature+1500)*(Temperature+1500)/2.0;
		}
	}
	else
	{
		Temperature2=0;
		OFF2=0;
		SENS2=0;
	}	
		Temperature=Temperature-Temperature2;
		OFF=OFF-OFF2;
		SENS=SENS-SENS2;	
		Pressure=(D1*SENS/2097152.0-OFF)/32768.0;
}



void MS5611_Init(void)
{
	MS5611_Reset();
	delay_ms(5);              //此处必须要有延时
	MS5611_PROM_Read();
} 

