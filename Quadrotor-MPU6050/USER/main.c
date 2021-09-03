#include "iic.h"
#include "delay.h"
#include "usart.h"	
#include "mpu6050.h"
#include "data_transfer.h"
#include "led.h" 

int main()
{
	delay_init(168);
	USART1_Init(500000);
	LED_Init();
	IIC_Init();
	while( MPU6050_Init()!=1);
	while(1)
	{ 
		MPU6050_Data_Read();
		MPU6050_Data_Compose();
		Send_Senser(acc.x,acc.y,acc.z,gyro.x,gyro.y,gyro.z,0,0,0);
		LED2_ON;
	}
}
