#ifndef __HMC5883L_H_
#define __HMC5883L_H_
#include "stm32f4xx.h" 




u8 HMC5883L_Init(void);
void HMC5883L_Data_Read(void);
void HMC5883L_Data_Compose(void);










struct _mag
{
	int16_t x;
	int16_t y;
	int16_t z;
};
extern struct _mag mag;
extern struct _mag filter_mag;
extern struct _mag offset_mag;





#define HMC5883L_ADDRESS      	 0x3C         //0x3C=0x1E<<1



#define CONFIG_A                  0x00         //配置寄存器A
#define CONFIG_B                  0x01         //配置寄存器B
#define MODE                      0x02         //模式寄存器
#define Magnetometer_XOUT_M       0x03         //X轴磁力计高位
#define Magnetometer_XOUT_L       0x04         //X轴磁力计低位
#define Magnetometer_ZOUT_M       0x05         //Z轴磁力计高位
#define Magnetometer_ZOUT_L       0x06         //Z轴磁力计低位
#define Magnetometer_YOUT_M       0x07         //Y轴磁力计高位
#define Magnetometer_YOUT_L       0x08         //Y轴磁力计低位
#define STATUS                    0x09         //状态寄存器
#define ID_A                      0x0A         //识别寄存器A
#define ID_B                      0x0B         //识别寄存器B
#define ID_C                      0x0C         //识别寄存器C








#endif
