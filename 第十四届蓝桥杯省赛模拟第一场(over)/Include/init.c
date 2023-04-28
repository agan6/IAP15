#include "init.h"

unsigned char Uart_Recv[20];
unsigned char Uart_Recv_Index = 0;

void SelectHC138(unsigned char channel)
{
	P2 &= 0x1F;
	P2 |= (channel & 0x07) << 5;
}

void Init_BUZZ_LED()
{
	SelectHC138(4);
	P0 = 0xFF;
	SelectHC138(5);
	P0 = 0x00;
	SelectHC138(0);
}

void Timer0Init(void)		//1����@12.000MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x20;		//���ö�ʱ��ʼֵ
	TH0 = 0xD1;		//���ö�ʱ��ʼֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;
}

void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��ʱ��1Tģʽ
	T2L = 0xC7;		//���ö�ʱ��ʼֵ
	T2H = 0xFE;		//���ö�ʱ��ʼֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
	ES = 1;
}

void SendByte(unsigned char dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}

void SendString(unsigned char *str)
{
	while(*str != '\0')
	{
		SendByte(*str++);
	}
}

void UartHandle() interrupt 4
{
	if(RI == 1)
	{
		Uart_Recv[Uart_Recv_Index] = SBUF;
		Uart_Recv_Index++;
		RI = 0;
	}
}
