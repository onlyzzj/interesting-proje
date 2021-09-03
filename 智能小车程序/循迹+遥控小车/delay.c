#include"delay.h"

void delay_us(uint x)
{
	uint i,j;
	for (j=0;j<x;j++)
		for (i=0;i<11;i++);
}

void delay_ms(uint x)
{
	uint i,j;
	for (j=0;j<x;j++)
		for (i=0;i<110;i++);
}