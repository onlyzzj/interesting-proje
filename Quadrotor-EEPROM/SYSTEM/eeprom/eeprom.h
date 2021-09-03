#ifndef __EEPROM_H
#define __EEPROM_H
#include "stm32f4xx.h" 





#define  AT24C02_ADDRESS		0xA0                                     //A0、A1、A2都接地




					  
u8 AT24C02_Read_1Byte(u8 BYTE_ADDRESS);						                   //从指定地址读取1个字节的数据
void AT24C02_Write_1Byte(u8 BYTE_ADDRESS,u8 DATA);		               //从指定地址写入1个字节的数据
void AT24C02_Read_nByte(u8 BYTE_ADDRESS,u8 *temp,u8 n);              //从指定地址开始写入n个字节的数据
void AT24C02_Write_nByte(u8 BYTE_ADDRESS,u8 *temp,u8 n);  	         //从指定地址开始读出n个字节的数据
u16 AT24C02_Read_16Bit(u8 BYTE_ADDRESS);                             //指定地址开始读出长度为16bit的数据
void AT24C02_Write_16Bit(u8 BYTE_ADDRESS,u16 DATA);                  //指定地址开始写入长度为16bit的数据
u32 AT24C02_Read_32Bit(u8 BYTE_ADDRESS);                             //指定地址开始读出长度为32bit的数据
void AT24C02_Write_32Bit(u8 BYTE_ADDRESS,u32 DATA);                  //指定地址开始写入长度为32bit的数据
u8 AT24C02_Check(void);                                              //检查器件








#endif
















