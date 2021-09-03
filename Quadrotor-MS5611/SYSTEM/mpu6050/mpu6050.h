#ifndef _MPU6050_H_
#define _MPU6050_H_
#include "stm32f4xx.h"


//extern uint8_t	GYRO_Offset;	
//extern uint8_t	ACC_Offset;
//extern uint32_t I2C_Erro;



u8 MPU6050_Init(void);
void MPU6050_Data_Read(void);
void MPU6050_Offset(void);
void MPU6050_Data_Compose(void);



struct _acc
{
	int16_t x;
	int16_t y;
	int16_t z;
};
extern struct _acc acc;
extern struct _acc filter_acc;
extern struct _acc offset_acc;


struct _gyro
{
	int16_t x;
	int16_t y;
	int16_t z;
};
extern struct _gyro gyro;
extern struct _gyro filter_gyro;
extern struct _gyro offset_gyro;


#define MPU6050_ADDRESS      			  MPU6050_ADDRESS_AD0_LOW
#define MPU6050_ADDRESS_AD0_LOW     0xD0      //当AD0引脚接低电平时     0xD0=0x68<<1
#define MPU6050_ADDRESS_AD0_HIGH    0xD2      //当AD0引脚接高电平时     0xD2=0x69<<1


#define SELF_TEST_X         0x0D        //X自检寄存器
#define SELF_TEST_Y         0x0E        //Y自检寄存器
#define SELF_TEST_Z         0x0F        //Z自检寄存器
#define SELF_TEST_A         0x10        //A自检寄存器
#define SMPLRT_DIV      	 	0x19        //采样频率分频器
#define CONFIG           		0x1A        //配置寄存器
#define GYRO_CONFIG      		0x1B        //陀螺仪配置
#define ACCEL_CONFIG     		0x1C        //加速度计配置
#define MOT_THR          		0x1F        //运动检测阈值
#define FIFO_EN          		0x23        //FIFO使能
#define I2C_MST_CTRL     		0x24        //IIC主机控制
#define I2C_SLV0_ADDR    		0x25        //IIC从机0地址
#define I2C_SLV0_REG     		0x26        //IIC从机0寄存器
#define I2C_SLV0_CTRL    		0x27        //IIC从机0控制
#define I2C_SLV1_ADDR    		0x28        //IIC从机1地址
#define I2C_SLV1_REG     		0x29        //IIC从机1寄存器
#define I2C_SLV1_CTRL    		0x2A        //IIC从机1控制
#define I2C_SLV2_ADDR   	 	0x2B        //IIC从机2地址
#define I2C_SLV2_REG     		0x2C        //IIC从机2寄存器
#define I2C_SLV2_CTRL    		0x2D        //IIC从机2控制
#define I2C_SLV3_ADDR    		0x2E        //IIC从机3地址
#define I2C_SLV3_REG     		0x2F        //IIC从机3寄存器
#define I2C_SLV3_CTRL    		0x30        //IIC从机3控制
#define I2C_SLV4_ADDR    		0x31        //IIC从机4地址
#define I2C_SLV4_REG     		0x32        //IIC从机4寄存器
#define I2C_SLV4_DO      		0x33
#define I2C_SLV4_CTRL    		0x34        //IIC从机4控制
#define I2C_SLV4_DI      		0x35
#define I2C_MST_STATUS   		0x36        //IIC主机状态
#define INT_PIN_CFG      		0x37        //引脚旁路使能配置寄存器
#define INT_ENABLE       		0x38        //中断使能寄存器
#define INT_STATUS       		0x3A        //中断状态寄存器
#define ACCEL_XOUT_H     		0x3B        //X轴加速度高位
#define ACCEL_XOUT_L     		0x3C        //X轴加速度低位
#define ACCEL_YOUT_H     		0x3D        //Y轴加速度高位
#define ACCEL_YOUT_L     		0x3E        //Y轴加速度低位
#define ACCEL_ZOUT_H    		0x3F        //Z轴加速度高位
#define ACCEL_ZOUT_L     		0x40        //Z轴加速度高位
#define TEMP_OUT_H       		0x41        //温度测量高位
#define TEMP_OUT_L       		0x42        //温度测量低位
#define GYRO_XOUT_H      		0x43        //X轴陀螺仪高位
#define GYRO_XOUT_L      		0x44        //X轴陀螺仪低位
#define GYRO_YOUT_H      		0x45        //Y轴陀螺仪高位
#define GYRO_YOUT_L      		0x46        //Y轴陀螺仪低位
#define GYRO_ZOUT_H      		0x47        //Z轴陀螺仪高位
#define GYRO_ZOUT_L      		0x48        //Z轴陀螺仪低位
#define EXT_SENS_DATA_00 		0x49        //外部传感器0数据
#define EXT_SENS_DATA_01 		0x4A        //外部传感器1数据
#define EXT_SENS_DATA_02 		0x4B        //外部传感器1数据
#define EXT_SENS_DATA_03 		0x4C        //外部传感器3数据
#define EXT_SENS_DATA_04 		0x4D        //外部传感器4数据
#define EXT_SENS_DATA_05 		0x4E        //外部传感器5数据
#define EXT_SENS_DATA_06 		0x4F        //外部传感器6数据
#define EXT_SENS_DATA_07 		0x50        //外部传感器7数据
#define EXT_SENS_DATA_08 		0x51        //外部传感器8数据
#define EXT_SENS_DATA_09 		0x52        //外部传感器9数据
#define EXT_SENS_DATA_10 		0x53        //外部传感器10数据
#define EXT_SENS_DATA_11 		0x54        //外部传感器11数据
#define EXT_SENS_DATA_12 		0x55        //外部传感器12数据
#define EXT_SENS_DATA_13 		0x56        //外部传感器13数据
#define EXT_SENS_DATA_14 		0x57        //外部传感器14数据
#define EXT_SENS_DATA_15 		0x58        //外部传感器15数据
#define EXT_SENS_DATA_16 		0x59        //外部传感器16数据
#define EXT_SENS_DATA_17 		0x5A        //外部传感器17数据
#define EXT_SENS_DATA_18 		0x5B        //外部传感器18数据
#define EXT_SENS_DATA_19 		0x5C        //外部传感器19数据
#define EXT_SENS_DATA_20 		0x5D        //外部传感器20数据
#define EXT_SENS_DATA_21 		0x5E        //外部传感器21数据
#define EXT_SENS_DATA_22 		0x5F        //外部传感器22数据
#define EXT_SENS_DATA_23 		0x60        //外部传感器23数据
#define I2C_SLV0_DO      		0x63        //IIC从机0输出数据
#define I2C_SLV1_DO      		0x64        //IIC从机1输出数据
#define I2C_SLV2_DO      		0x65        //IIC从机2输出数据
#define I2C_SLV3_DO      		0x66        //IIC从机3输出数据
#define I2C_MST_DELAY_CTRL  0x67        //IIC主机延时管理   
#define SIGNAL_PATH_RESET   0x68        //信号通道复位
#define MOT_DETECT_CTRL     0x69        //运动检测控制
#define USER_CTRL        		0x6A        //用户配置
#define PWR_MGMT_1       		0x6B        //电源管理1
#define PWR_MGMT_2       		0x6C        //电源管理2
#define FIFO_COUNTH      		0x72        //FIFO计数寄存器【15:8】
#define FIFO_COUNTL      		0x73        //FIFO计数寄存器【7：0】
#define FIFO_R_W         		0x74        //FIFO读/写
#define WHO_AM_I         		0x75        //我是谁





#endif

