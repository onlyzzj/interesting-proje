#ifndef  __key_h_
#define  __key_h_

#include "common.h"

extern int x;
extern int y;

sbit zuo_Key_add=P2^1; //左电机加速
sbit zuo_Key_dec=P2^3; //左电机减速
sbit you_Key_add=P2^2; //右电机加速
sbit you_Key_dec=P2^0; //右电机减速

void zuo_speed_high(void);
void zuo_speed_low(void);
void you_speed_high(void);
void you_speed_low(void);

#endif