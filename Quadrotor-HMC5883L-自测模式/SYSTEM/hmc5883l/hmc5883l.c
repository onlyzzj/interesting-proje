#include "hmc5883l.h"
#include "iic.h"
#include "delay.h"


u8 HMC5883L_Buffer[6];
struct _mag  mag;


u8 HMC5883L_Init(void)
{
	u8 ASCII_A,ASCII_B,ASCII_C;
	IIC_Read_1Byte(HMC5883L_ADDRESS,ID_A,&ASCII_A);
	IIC_Read_1Byte(HMC5883L_ADDRESS,ID_B,&ASCII_B);
	IIC_Read_1Byte(HMC5883L_ADDRESS,ID_C,&ASCII_C);
	if(ASCII_A!='H'||ASCII_B!='4'||ASCII_C!='3')
	{
		return 0;	
	}
	IIC_Write_1Byte(HMC5883L_ADDRESS,CONFIG_A,0x71);
	delay_ms(5);
	IIC_Write_1Byte(HMC5883L_ADDRESS,CONFIG_B,0xA0);
	delay_ms(5);
	IIC_Write_1Byte(HMC5883L_ADDRESS,MODE,0x01); 
	delay_ms(5);
	return 1;	 
}





void HMC5883L_Data_Read(void)
{
	IIC_Read_1Byte(HMC5883L_ADDRESS,Magnetometer_XOUT_M,HMC5883L_Buffer+0);
	IIC_Read_1Byte(HMC5883L_ADDRESS,Magnetometer_XOUT_L,HMC5883L_Buffer+1);		
	IIC_Read_1Byte(HMC5883L_ADDRESS,Magnetometer_ZOUT_M,HMC5883L_Buffer+2);	
	IIC_Read_1Byte(HMC5883L_ADDRESS,Magnetometer_ZOUT_L,HMC5883L_Buffer+3);
	IIC_Read_1Byte(HMC5883L_ADDRESS,Magnetometer_YOUT_M,HMC5883L_Buffer+4);
	IIC_Read_1Byte(HMC5883L_ADDRESS,Magnetometer_YOUT_L,HMC5883L_Buffer+5);
	
	
//	IIC_Read_nByte(HMC5883L_ADDRESS,Magnetometer_XOUT_M,6,MPU6050_Buffer);
}








void HMC5883L_Data_Compose(void)
{
	mag.x=((((int16_t)HMC5883L_Buffer[0])<<8)|HMC5883L_Buffer[1]);
	mag.z=((((int16_t)HMC5883L_Buffer[2])<<8)|HMC5883L_Buffer[3]);
	mag.y=((((int16_t)HMC5883L_Buffer[4])<<8)|HMC5883L_Buffer[5]);
}




