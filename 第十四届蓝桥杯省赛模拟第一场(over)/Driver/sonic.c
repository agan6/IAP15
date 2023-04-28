#include "sonic.h"
#include "intrins.h"
#include "init.h"

unsigned int distance;

void Delay13us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 36;
	while (--i);
}

void SendWave()
{
	unsigned char i;
	
	for(i = 0; i < 8; i++)
	{
		TX = 1;
		Delay13us();
		TX = 0;
		Delay13us();
	}

}

void Get_Distance()
{
	unsigned int t;
	float time;
	
	TH1 = 0x00;
	TL1 = 0x00;
	SendWave();
	
	TR1 = 1;
	while((TF1 == 0) && (RX == 1));
	TR1 = 0;
	
	if(TF1 == 0)
	{
		t = TH1;
		t = (t << 8) | TL1;
		time = t;
		time = time * 0.017;
		distance = time;
	}
	else
	{
		TF1 = 0;
		distance = 999;
	}
}
