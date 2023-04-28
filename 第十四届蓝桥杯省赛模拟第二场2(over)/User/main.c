#include "main.h"

bit flag100ms = 0;
bit DisplayMode = 0;
unsigned int Read_Vep;
unsigned int Noise;
int Noise_Set = 65;
float Read_Vep_Buf;
extern unsigned char Uart_Recv[20];
unsigned char xdata str[20];
extern unsigned char Recv_Index;

void Working();

void main()
{
	Init_BUZZ_LED();
	Timer0Init();
	UartInit();
	EA = 1;
	while(1)
	{
		Working();
	}
}

void Working()
{
	KeyDriver();
	if(flag100ms == 1)
	{
		flag100ms = 0;
		Read_Vep = AD_Read(0x43);
		Read_Vep_Buf = Read_Vep * 100 / 51;
		Read_Vep_Buf = Read_Vep_Buf * 9 / 5;
		Noise = Read_Vep_Buf;
		Led_Single();
		if(DisplayMode == 0)
		{
			DisplayMode0();
		}
		else
		{
			DisplayMode1();
		}
	}
	if(DisplayMode == 0)
	{
		if(strcmp(Uart_Recv,"Return") == 0)
		{
			sprintf(str,"Noises:%.1fdB\r\n",Read_Vep_Buf / 10);
			SendString(str);
			Uart_Recv[0] = '1';
			Recv_Index = 0;
		}
	}
}

void KeyAction(unsigned char keycode)
{
	if(keycode == '6')
	{
		if(DisplayMode == 0)
		{
			DisplayMode = 1;
		}
		else
		{
			DisplayMode = 0;
		}
	}
	if(DisplayMode == 1)
	{
		if(keycode == 'B')
		{
			Noise_Set += 5;
			if(Noise_Set >= 90)
			{
				Noise_Set = 90;
			}
		}
		else if(keycode == 'A')
		{
			Noise_Set -= 5;
			if(Noise_Set <= 0)
			{
				Noise_Set = 0;
			}
		}
	}
}

void Timer0Handle() interrupt 1
{
	static unsigned char cnt_100ms = 0;
	
	Display();
	KeyScan();
	
	cnt_100ms++;
	if(cnt_100ms >= 100)
	{
		cnt_100ms = 0;
		flag100ms = 1;
	}
}
