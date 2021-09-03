#include "usart.h"




int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	USART1_Init(115200);
	while(1)
	{
		u8 tbuf[4];
		tbuf[0]=0X11;
		tbuf[1]=0X22;
		tbuf[2]=0X33;
		tbuf[3]=0XFF;
		USART1_Send(tbuf,4);
	}
}
