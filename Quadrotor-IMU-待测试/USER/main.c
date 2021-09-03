#include "iic.h"
#include "delay.h"
#include "usart.h"	
#include "mpu6050.h"
#include "hmc5883l.h"
#include "data_transfer.h"
#include "led.h"
#include "math.h"
#include "imu.h"






int main()
{
	delay_init(168);
	USART1_Init(500000);
	LED_Init();
	IIC_Init();
	while(MPU6050_Init()!=1);
	while(HMC5883L_Init()!=1);
	IMU_Init();
	while(1)
	{ 
		MPU6050_Data_Read();
		MPU6050_Data_Compose();
		HMC5883L_Data_Read();
		HMC5883L_Data_Compose();
		MPU6050_Gyro_Angle(gyro.x,gyro.y,gyro.z);
		MPU6050_Gyro_Radian(Gyro_angle_x,Gyro_angle_y,Gyro_angle_z);
		Data_Change();
		IMU_Update(a_x,a_y,a_z,Gyro_radian_x,Gyro_radian_y,Gyro_radian_z,m_x,m_y,m_z);
		Send_Status(Roll,Pitch,Yaw,0,0,0);
		LED2_ON; 
	}
}




