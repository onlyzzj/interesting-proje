#ifndef  __common_h_
#define  __common_h_

#include <reg52.h>
  
typedef  unsigned int uint;
typedef	 unsigned char uchar;


sbit EN1=P1^1;
sbit EN2=P1^2;
sbit in1=P0^0;    //iN1 iN2 为右电机    //in1=0;in2=1;前转
sbit in2=P0^1;	  						
sbit in3=P0^2;    //iN3 iN4 为左电机	//in3=1;in4=0;前转
sbit in4=P0^3;


#endif