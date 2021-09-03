#ifndef  __common_h_
#define  __common_h_


#include <reg52.h>
#include<intrins.h>

  
typedef  unsigned int uint;
typedef	 unsigned char uchar;


sbit LED1=P0^0;
sbit LED2=P0^1;
sbit LED3=P0^2;
sbit LED4=P0^3;
sbit LED5=P0^4;
sbit LED6=P0^5;
sbit LED7=P0^6;
sbit LED8=P0^7;

sbit Key1=P2^3;
sbit Key2=P2^1;
sbit Key3=P2^2;
sbit Key4=P2^0;
//sbit Key5=P2^0;
//sbit Key6=P2^1;
//sbit Key7=P2^2;
//sbit Key8=P2^3;

#endif