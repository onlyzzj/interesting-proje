#include"delay.h"

void delay_us(uint x)
{
	uint i,j;
	for (j=0;j<x;j++)
		for (i=0;i<12;i++);
}

void delay_ms(uint x)
{
	uint i,j;
	for (j=0;j<x;j++)
		for (i=0;i<120;i++);
}