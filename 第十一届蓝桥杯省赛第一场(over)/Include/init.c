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

void Timer0Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初始值
	TH0 = 0xD4;		//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    ET0 = 1;
    EA = 1;
}
