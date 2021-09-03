#ifndef __xunji_h__
#define __xunji_h__

#include "common.h"
#include"delay.h"
#include "nRF24L01_RX.h"
#include"qudong.h"


sbit HW1=P1^0;//最左侧探头（第一个探头）
sbit HW2=P1^1;//第二个探头
sbit HW3=P1^2;//第三个探头
sbit HW4=P1^3;//最右侧探头（第四个探头）


void xunji(void);

#endif