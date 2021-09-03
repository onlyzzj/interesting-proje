#ifndef __MATH_H__
#define __MATH_H__
#include "stm32f4xx.h"



#define MPU6050_Gyro_angle_250        131.0f               //  500/65536.0=0.007629395=1/131.0 
#define MPU6050_Gyro_angle_500         65.5f               // 1000/65536.0=0.01525879=1/65.5
#define MPU6050_Gyro_angle_1000        32.8f               // 2000/65536.0=0.03051758=1/32.8
#define MPU6050_Gyro_angle_2000        16.4f               // 4000/65536.0=0.06103516=1/16.4


#define MPU6050_Acc_Gram_2         	 16384.0f              //  4/65536.0=0.00006103516=1/16384.0 
#define MPU6050_Acc_Gram_4         	  8192.0f              //  8/65536.0=0.0001220703=1/8192.0
#define MPU6050_Acc_Gram_8         	  4096.0f              // 16/65536.0=0.0002441406=1/4096.0
#define MPU6050_Acc_Gram_16         	2048.0f              // 32/65536.0=0.0004882812=1/2048.0
	
	
#define HMC5883L_Mag_Gauss_088        1370.0f              //    1/1370.0   
#define HMC5883L_Mag_Gauss_13         1090.0f              //    1/1090.0      
#define HMC5883L_Mag_Gauss_19          820.0f              // 	 1/820.0       
#define HMC5883L_Mag_Gauss_25          660.0f              //    1/660.0      
#define HMC5883L_Mag_Gauss_40          440.0f              // 	 1/440.0      
#define HMC5883L_Mag_Gauss_47          390.0f              //    1/390.0      
#define HMC5883L_Mag_Gauss_56          330.0f              //    1/330.0       
#define HMC5883L_Mag_Gauss_81          230.0f              //    1/230.0    






extern float Gyro_angle_x,Gyro_angle_y,Gyro_angle_z;
extern float Gyro_radian_x,Gyro_radian_y,Gyro_radian_z;
extern float Acc_gram_x,Acc_gram_y,Acc_gram_z;
extern float Acc_speed_x,Acc_speed_y,Acc_speed_z;
extern float Mag_gauss_x,Mag_gauss_y,Mag_gauss_z;





void MPU6050_Gyro_Angle(s16 gyro_x,s16 gyro_y,s16 gyro_z);
void MPU6050_Gyro_Radian(float angle_x,float angle_y,float angle_z);
void MPU6050_Acc_Gram(s16 acc_x,s16 acc_y,s16 acc_z);
void MPU6050_Acc_Speed(float gram_x,float gram_y,float gram_z);
void HMC5883L_Mag_Gauss(s16 mag_x,s16 mag_y,s16 mag_z);
float invSqrt(float x); 




#endif

