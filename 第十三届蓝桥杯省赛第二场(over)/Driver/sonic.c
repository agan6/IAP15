#include "sonic.h"
#include "init.h"
#include "intrins.h"

unsigned int distance;
float time;

void Delay13us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 36;
	while (--i);
}

void SendWare()
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

    Timer1Init();
    SendWare();
    TR1 = 1;
    while((TF1 == 0) && (RX == 1));
    TR1 = 0;
    if(TF1 == 0)
    {
        t = (TH1 << 8) | TL1;
		time = t;
        time = time * 17 / 1000;
		distance = time;
    }
	else
	{
		TF1 = 0;
		distance = 999;
	}
}
