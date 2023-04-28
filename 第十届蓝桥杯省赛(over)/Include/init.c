#include "init.h"

void SelectHC138(unsigned char channel)
{
	P2 &= 0x1F;
	P2 |= (channel & 0x07) << 5;
}

void Init_LED_BUZZ()
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
	TMOD |= 0x05;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ʼֵ
	TH0 = 0x00;		//���ö�ʱ��ʼֵ
	TF0 = 0;		//���TF0��־
	TR0 = 0;		//��ʱ����ʱ�ر�
	ET0 = 0;
}


void Timer1Init(void)		//1����@12.000MHz
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0x20;		//���ö�ʱ��ʼֵ
	TH1 = 0xD1;		//���ö�ʱ��ʼֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	ET1 = 1;
}

	