#ifndef _MS5611_H_
#define _MS5611_H_
#include "stm32f4xx.h" 


extern double Temperature,Pressure; 


#define MS5611_ADDRESS          0xEE   //CSB接地，其中C为CSB引脚取反，所以MS5611的IIC地址为0x77    0xEE=0x77<<1


#define MS5611_RESET            0x1E   //复位指令
#define CONVERT_D1_256          0x40 
#define CONVERT_D1_512          0x42
#define CONVERT_D1_1024         0x44 
#define CONVERT_D1_2048         0x46 
#define CONVERT_D1_4096         0x48 
#define CONVERT_D2_256          0x50 
#define CONVERT_D2_512          0x52
#define CONVERT_D2_1024         0x54 
#define CONVERT_D2_2048         0x56 
#define CONVERT_D2_4096         0x58 
#define ADC_READ                0x00
#define PROM_READ_1             0xA0
#define PROM_READ_2             0xA2
#define PROM_READ_3             0xA4
#define PROM_READ_4             0xA6
#define PROM_READ_5             0xA8
#define PROM_READ_6             0xAA
#define PROM_READ_7             0xAC
#define PROM_READ_8             0xAE




void MS5611_Reset(void);
void MS5611_PROM_Read(void);
void MS5611_ADC_Conversion(u8 command);
u32 MS5611_ADC_Read(void);
void MS5611_Get_Temperature(u8 D2_OSR_Temperature);
void MS5611_Get_Pressure(u8 D1_OSR_Pressure);
void MS5611_Init(void);





#endif 

