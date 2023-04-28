#include "init.h"

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
	EA = 1;
}

