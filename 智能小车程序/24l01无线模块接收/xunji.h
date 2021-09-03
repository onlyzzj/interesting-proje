#ifndef __xunji_h__
#define __xunji_h__

#include "common.h"
#include"delay.h"
#include "nRF24L01_RX.h"
#include"qudong.h"

//红外寻迹探头,从左边数起
//检测到了黑线返回低电平,相应指示灯亮
sbit HW1=P1^0;//第一个探头
sbit HW2=P1^1;//第二个探头
sbit HW3=P1^2;//第三个探头
sbit HW4=P1^3;//第四个探头


void xunji(void);

#endif