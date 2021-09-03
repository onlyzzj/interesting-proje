#include "nRF24L01_RX.h"
#include"delay.h"

uchar sta; //×´Ì¬±äÁ¿ 
uchar code TX_Addr[]={0x34,0x43,0x10,0x10,0x01};
uchar code TX_Buffer[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar RX_Buffer[RX_DATA_WITDH];


void nRF24L01_Init(void)
{
	delay_us(2000);
	CE=0;
	CSN=1;
	SCK=0;
	IRQ=1;
}

uchar SPI_RW(uchar byte)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		if(byte&0x80)
			MOSI=1;
		else 
			MOSI=0;
		byte<<=1;
		SCK=1;
		if(MISO)
			byte|=0x01;
		SCK=0;
	}
	return byte;
}

uchar SPI_W_Reg(uchar reg,uchar value)
{
	uchar status;
	CSN=0;
	status=SPI_RW(reg);
	SPI_RW(value);
	CSN=1;
	return status;
}

uchar SPI_R_byte(uchar reg)
{
	uchar status;
	CSN=0;
	SPI_RW(reg);
	status=SPI_RW(0);
	CSN=1;
	return status;
}

uchar SPI_R_DBuffer(uchar reg,uchar *Dat_Buffer,uchar Dlen)
{
	uchar reg_value,i;
	CSN=0;
	reg_value=SPI_RW(reg);
	for(i=0;i<Dlen;i++)
	{
		Dat_Buffer[i]=SPI_RW(0);
	}
	CSN=1;
	return reg_value;
}

uchar SPI_W_DBuffer(uchar reg,uchar *TX_Dat_Buffer,uchar Dlen)
{
	uchar reg_value,i;
	CSN=0;
	reg_value=SPI_RW(reg);
	for(i=0;i<Dlen;i++)
	{
		SPI_RW(TX_Dat_Buffer[i]);
	}
	CSN=1;
	return reg_value;	
}

void nRF24L01_Set_RX_Mode(void)
{
	CE=0;//´ý»ú
	SPI_W_DBuffer(W_REGISTER+TX_ADDR,TX_Addr,TX_ADDR_WITDH);
	SPI_W_DBuffer(W_REGISTER+RX_ADDR_P0,TX_Addr,TX_ADDR_WITDH);
	SPI_W_Reg(W_REGISTER+EN_AA,0x01);//auot ack
	SPI_W_Reg(W_REGISTER+EN_RX_ADDR,0x01);
	SPI_W_Reg(W_REGISTER+SETUP_RETR,0x0a);
	SPI_W_Reg(W_REGISTER+RX_PW_P0,RX_DATA_WITDH);
	SPI_W_Reg(W_REGISTER+RF_CH,0x40);
	SPI_W_Reg(W_REGISTER+RF_SETUP,0x07);//0db,lna
	SPI_W_Reg(W_REGISTER+CONFIG,0x0f);
	CE=1;
	delay_ms(5);
}

uchar nRF24L01_RX_Data(void)
{
	sta=SPI_R_byte(R_REGISTER+STATUS);
	if(RX_DR)
	{
		CE=0;
		SPI_R_DBuffer(R_RX_PLOAD,RX_Buffer,RX_DATA_WITDH);
		SPI_W_Reg(W_REGISTER+STATUS,0xff);
		CSN=0;
		SPI_RW(FLUSH_RX);
		CSN=1;
		return 1;
	}
	else
		return 0;
	
}








