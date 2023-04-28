#include "init.h"

bit flag_Relay = 0;

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

void Timer0Init(void)		
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;		
	TL0 = 0x20;		
	TH0 = 0xD1;		
	TF0 = 0;		
	TR0 = 1;		
	ET0 = 1;
	EA = 1;
}

void Relay()
{
	P0 = 0x00;
	if(flag_Relay == 0)
	{
		SelectHC138(5);
		P04 = 0;
		SelectHC138(0);
	}
	else
	{
		SelectHC138(5);
		P04 = 1;
		SelectHC138(0);
	}
}
