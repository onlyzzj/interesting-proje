#ifndef __xunji_h__
#define __xunji_h__

#include "common.h"
#include"qudong.h"

extern int flag1;
extern int flag2;

sbit HW1=P1^0;//第一个探头
sbit HW2=P1^1;//第二个探头
sbit HW3=P1^2;//第三个探头
sbit HW4=P1^3;//第四个探头

void xunji(void);

#endif