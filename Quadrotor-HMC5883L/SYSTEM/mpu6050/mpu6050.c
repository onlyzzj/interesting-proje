#include "mpu6050.h"
#include "iic.h"
#include "delay.h"



u8 MPU6050_Buffer[14];
struct _acc  acc;	
struct _gyro gyro;



u8 MPU6050_Init(void)
{
	u8 i;
	IIC_Read_1Byte(MPU6050_ADDRESS,WHO_AM_I,&i);                //检查MPU6050是否正常
	if(i!=0x68)         
	{
		return 0;		
	}	
	IIC_Write_1Byte(MPU6050_ADDRESS,PWR_MGMT_1,0x00);	         //电源管理，典型值：0x00，正常模式
	delay_ms(5);
	IIC_Write_1Byte(MPU6050_ADDRESS,SMPLRT_DIV,0x00);	         //陀螺仪采样率，典型值：0x00，1KHZ
	delay_ms(5);            
	IIC_Write_1Byte(MPU6050_ADDRESS,CONFIG,0x03);   	           //低通滤波频率，42HZ
	delay_ms(5);
	IIC_Write_1Byte(MPU6050_ADDRESS,GYRO_CONFIG,0x18);	         //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	delay_ms(5);
	IIC_Write_1Byte(MPU6050_ADDRESS,ACCEL_CONFIG,0x10);         //加速计自检、测量范围及高通滤波频率，典型值：0x10(不自检，8G)
	delay_ms(5);
	IIC_Write_1Byte(MPU6050_ADDRESS,USER_CTRL,0x40);    				 //不让MPU6050 控制AUXI2C
	delay_ms(5);
	IIC_Write_1Byte(MPU6050_ADDRESS,INT_PIN_CFG,0x42);   			 //主控制器的I2C与	MPU6050的AUXI2C直通。控制器可以直接访问HMC5883L
	delay_ms(5);
	return 1;
}





void MPU6050_Data_Read(void)
{
		IIC_Read_1Byte(MPU6050_ADDRESS,ACCEL_XOUT_H,MPU6050_Buffer+0);
		IIC_Read_1Byte(MPU6050_ADDRESS,ACCEL_XOUT_L,MPU6050_Buffer+1);		
		IIC_Read_1Byte(MPU6050_ADDRESS,ACCEL_YOUT_H,MPU6050_Buffer+2);	
		IIC_Read_1Byte(MPU6050_ADDRESS,ACCEL_YOUT_L,MPU6050_Buffer+3);
		IIC_Read_1Byte(MPU6050_ADDRESS,ACCEL_ZOUT_H,MPU6050_Buffer+4);
		IIC_Read_1Byte(MPU6050_ADDRESS,ACCEL_ZOUT_L,MPU6050_Buffer+5);
		
		IIC_Read_1Byte(MPU6050_ADDRESS,GYRO_XOUT_H,MPU6050_Buffer+8);
		IIC_Read_1Byte(MPU6050_ADDRESS,GYRO_XOUT_L,MPU6050_Buffer+9);
		IIC_Read_1Byte(MPU6050_ADDRESS,GYRO_YOUT_H,MPU6050_Buffer+10);
		IIC_Read_1Byte(MPU6050_ADDRESS,GYRO_YOUT_L,MPU6050_Buffer+11);
		IIC_Read_1Byte(MPU6050_ADDRESS,GYRO_ZOUT_H,MPU6050_Buffer+12);
		IIC_Read_1Byte(MPU6050_ADDRESS,GYRO_ZOUT_L,MPU6050_Buffer+13);
	
	
//	IIC_Read_nByte(MPU6050_ADDRESS,ACCEL_XOUT_H,14,MPU6050_Buffer);
}




//void MPU6050_Offset(void)
//{
//	if(ACC_Offset)
//	{
//		static int32_t ACC_X=0,ACC_Y=0,ACC_Z=0;
//		static uint8_t count_acc=0;
//		if(count_acc==0)
//		{
//			offset_acc.x=0;
//			offset_acc.y=0;
//			offset_acc.z=0;
//			ACC_X=0;
//			ACC_Y=0;
//			ACC_Z=0;
//			count_acc=1;
//			return;
//		}
//		else
//		{
//			count_acc++;
//			ACC_X+=acc.x;
//			ACC_Y+=acc.y;
//			ACC_Z+=acc.z;
//		}
//		if(count_acc==251)
//		{
//			count_acc--;
//			offset_acc.x=ACC_X / count_acc;
//			offset_acc.y=ACC_Y / count_acc;
//			offset_acc.z=ACC_Z / count_acc - 2048;
//			count_acc=0;
//			ACC_Offset=0;
////			EEPROM_SAVE_ACC_OFFSET();
//			
//		}
////		LED3_ON;
//	}
//	
//	if(GYRO_Offset)
//	{
//		static int32_t GYRO_X=0,GYRO_Y=0,GYRO_Z=0;
//		static uint8_t count_gyro=0;
//		if(count_gyro==0)
//		{
//			offset_gyro.x=0;
//			offset_gyro.y=0;
//			offset_gyro.z=0;
//			GYRO_X=0;
//			GYRO_Y=0;
//			GYRO_Z=0;
//			count_gyro=1;
//			return;
//		}
//		else
//		{
//			count_gyro++;
//			GYRO_X+=gyro.x;
//			GYRO_Y+=gyro.y;
//			GYRO_Z+=gyro.z;
//		}
//		if(count_gyro==251)
//		{
//			count_gyro--;
//			offset_gyro.x=GYRO_X/count_gyro;
//			offset_gyro.y=GYRO_Y/count_gyro;
//			offset_gyro.z=GYRO_Z/count_gyro;
//			count_gyro=0;
//			GYRO_Offset=0;
////			EEPROM_SAVE_GYRO_OFFSET();
//		}
////		LED3_ON;
//	}
//}






void MPU6050_Data_Compose(void)
{
//	MPU6050_Offset();
	acc.x=((((int16_t)MPU6050_Buffer[0])<<8)|MPU6050_Buffer[1]);//-offset_acc.x;	//减去零偏
	acc.y=((((int16_t)MPU6050_Buffer[2])<<8)|MPU6050_Buffer[3]);//-offset_acc.y;
	acc.z=((((int16_t)MPU6050_Buffer[4])<<8)|MPU6050_Buffer[5]);//-offset_acc.z;

	gyro.x=((((int16_t)MPU6050_Buffer[8])<<8)|MPU6050_Buffer[9]);//-offset_gyro.x;
	gyro.y=((((int16_t)MPU6050_Buffer[10])<<8)|MPU6050_Buffer[11]);//-offset_gyro.y;
	gyro.z=((((int16_t)MPU6050_Buffer[12])<<8)|MPU6050_Buffer[13]);//-offset_gyro.z;	
}



