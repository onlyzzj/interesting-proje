#include "iic.h"
#include "delay.h"
#include "usart.h"	
#include "mpu6050.h"
#include "hmc5883l.h"
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
	while(1)
	{ 
		MPU6050_Data_Read();
		MPU6050_Data_Compose();
		HMC5883L_Data_Read();
		HMC5883L_Data_Compose();
		Send_Senser(acc.x,acc.y,acc.z,gyro.x,gyro.y,gyro.z,mag.x,mag.y,mag.z);
		LED2_ON;
	}
}

