#include "iic.h"
#include "delay.h"
#include "usart.h"	
#include "mpu6050.h"
#include "hmc5883l.h"
#include "ms5611.h"
#include "data_transfer.h"
#include "led.h"









int main()
{
	delay_init(168);
	USART1_Init(500000);
	LED_Init();
	IIC_Init();
	while(MPU6050_Init()!=1);
	while(HMC5883L_Init()!=1);
	MS5611_Init();	
	while(1)
	{ 
//		MPU6050_Data_Read();
//		MPU6050_Data_Compose();
//		HMC5883L_Data_Read();
//		HMC5883L_Data_Compose();
//		Send_Senser(acc.x,acc.y,acc.z,gyro.x,gyro.y,gyro.z,mag.x,mag.y,mag.z);temp[0]<<8|
		MS5611_Get_Temperature(CONVERT_D2_4096);
		MS5611_Get_Pressure(CONVERT_D1_4096);
		Send_Senser2(Pressure,Temperature);
		LED2_ON; 
	}
}

