#include "main.h"

bit flag100ms = 0;
bit flag800ms = 0;
bit DisplayMode = 0;
bit DisplayMode_Change_Enable = 0;
unsigned int tempbuf;
unsigned int temp_Read;
unsigned int Read_Vep;
extern unsigned char xdata UartRecv[20];
extern unsigned char index;
unsigned char xdata str[20] = {0};

void Working();

void main()
{
	Timer0Init();
	Init_BUZZ_LED();
	InitDS18B20();
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
		Read_Vep = Read_Vep * 100 / 51;
		Led_Single();
		BUZZ_RELAY();
		if(DisplayMode == 0)
		{
			DisplayMode0();
		}
		else
		{
			DisplayMode1();
		}
		if(DisplayMode_Change_Enable == 0)
		{
			index = 0;
			if(UartRecv[0] == 'A')
			{
				DisplayMode = 0;
			}
			else if(UartRecv[0] == 'B')
			{
				DisplayMode = 1;
			}
		}
	}
	if(flag800ms == 1)
	{
		flag800ms = 0;
		temp_Read = Read_Temp();
		if(temp_Read > 500)
		{
			tempbuf = tempbuf;
		}
		else
		{
			tempbuf = temp_Read;
		}
		InitDS18B20();
	}
}

void KeyAction(unsigned char keycode)
{
	if(keycode == '4')
	{
		DisplayMode_Change_Enable = 0;
	}
	else if(keycode == '1')
	{
		DisplayMode_Change_Enable = 1;
	}
	else if(keycode == '6')
	{
		if(DisplayMode == 0)
		{
			sprintf(str,"TEMP:%.1f℃\r\n",(float)tempbuf / 10);
			SendString(str);
		}
		else
		{
			sprintf(str,"Voltage:%.2fV\r\n",(float)Read_Vep / 100);
			SendString(str);
		}
	}
}

void Timer0Handle() interrupt 1
{
	static unsigned char cnt_100ms = 0;
	static unsigned int cnt_800ms = 0;
	
	Display();
	KeyScan();
	
	cnt_100ms++;
	if(cnt_100ms >= 100)
	{
		cnt_100ms = 0;
		flag100ms = 1;
	}
	cnt_800ms++;
	if(cnt_800ms >= 800)
	{
		cnt_800ms = 0;
		flag800ms = 1;
	}
}
