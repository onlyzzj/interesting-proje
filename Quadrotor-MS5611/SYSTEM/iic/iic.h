#ifndef _IIC_H
#define	_IIC_H
#include "stm32f4xx.h"



#define SCL_H         GPIOB->BSRRL=GPIO_Pin_8		//GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define SCL_L         GPIOB->BSRRH=GPIO_Pin_8		//GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define SDA_H         GPIOB->BSRRL=GPIO_Pin_9		//GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SDA_L         GPIOB->BSRRH=GPIO_Pin_9		//GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define SDA_read      GPIOB->IDR&GPIO_Pin_9 		//GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7)




void IIC_Init(void);
u8 IIC_Start(void);
void IIC_Stop(void);
void IIC_Ask(void);
void IIC_NoAsk(void);
u8 IIC_WaitAsk(void);
void IIC_SendByte(u8 SendByte);
u8 IIC_ReadByte(void);
u8 IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
u8 IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 *REG_data);
u8 IIC_Write_nByte(u8 SlaveAddress,u8 REG_Address,u8 len,u8 *buf);
u8 IIC_Read_nByte(u8 SlaveAddress,u8 REG_Address,u8 len,u8 *buf);
u8 IIC_No_REG_Address_Write_1Byte(u8 SlaveAddress,u8 REG_data);






#endif
