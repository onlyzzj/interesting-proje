#ifndef __led_h__
#define __led_h__


#include "common.h"
#include"delay.h"
#include "nRF24L01_RX.h"

sbit LED1=P0^0;
sbit LED2=P0^1;
sbit LED3=P0^2;
sbit LED4=P0^3;
sbit LED5=P0^4;
sbit LED6=P0^5;
sbit LED7=P0^6;
sbit LED8=P0^7;

void led(void);


#endif