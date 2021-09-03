#ifndef  __lcd12864_h_
#define  __lcd12864_h_
#include "common.h"


#define DATAPORT P1
sbit rs=P3^2;
sbit rw=P3^1;
sbit en=P3^0;
sbit PSB=P0^4;
sbit beiguang=P3^7;


void write_com(uchar com);
void write_data(uchar dat);
void init_lcd12864(void);
void write_string(uchar x,uchar y,char *z);



#endif