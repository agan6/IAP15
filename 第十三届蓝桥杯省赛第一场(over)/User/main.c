#include "main.h"

bit flag800ms = 0;
bit flag100ms = 0;
bit Control_Mode = 0;
bit Time_Mode = 0;
extern bit flag_Relay;
unsigned char Display_Mode = 0;
unsigned int tempbuf;
unsigned char Temp_Set= 24;
extern unsigned char Timer_Set[7];

void working();

void main()
{
	Init_BUZZ_LED();
	Timer0Init();
	InitDS18B20();
	Init_DS1302();
	while(1)
	{
		working();
	}
}

void working()
{
	KeyDriver();
	if(flag100ms == 1)
	{
		flag100ms = 0;
		Read_DS1302();
		if(Control_Mode == 0)
		{
			if(tempbuf > Temp_Set * 10)
			{
				flag_Relay = 1;
				Relay();
			}
			else
			{
				flag_Relay = 0;
				Relay();
			}
		}
		else
		{
			if((Timer_Set[1] == 0x00) && ((Timer_Set[0] >= 0x00) && (Timer_Set[0] <= 0x05)))
			{
				flag_Relay = 1;
				Relay();
			}
			else
			{
				flag_Relay = 0;
				Relay();
			}
		}
		Led_Single();
		if(Display_Mode == 0)
		{
			DisplayMode1();
		}
		else if(Display_Mode == 1)
		{
			DisplayMode2();
		}
		else if(Display_Mode == 2)
		{
			DisplayMode3();
		}
	}
	if(flag800ms == 1)
	{
		flag800ms = 0;
		tempbuf = ReadTemp();
		InitDS18B20();
	}
}

void KeyAction1(unsigned char keycode)
{
	if(keycode == '9')
	{
		if(Control_Mode == 0)
		{
			Control_Mode = 1;
		}
		else if(Control_Mode == 1)
		{
			Control_Mode = 0;
		}
	}
	if(keycode == '-')
	{
		if(Display_Mode == 0)
		{
			Display_Mode = 1;
		}
		else if(Display_Mode == 1)
		{
			Display_Mode = 2;
		}
		else if(Display_Mode == 2)
		{
			Display_Mode = 0;
		}
	}
	if(Display_Mode == 1)
	{
		if(keycode == 'D')
		{
			Time_Mode = 1;
		}
	}
	if(Display_Mode == 2)
	{
		if((Temp_Set < 99) && (Temp_Set > 10))
		{
			if(keycode == 'C')
			{
				Temp_Set++;
			}
			else if(keycode == 'D')
			{
				Temp_Set--;
			}
		}
	}
}

void KeyAction2(unsigned char keycode)
{
	if(keycode == 'D')
	{
		if(Display_Mode == 1)
		{
			Time_Mode = 0;
		}
	}
}

void Timer0Handle() interrupt 1
{
	static unsigned int cnt_800ms = 0;
	static unsigned char cnt_100ms = 0;
	
	KeyScan();
	Display();
	
	cnt_800ms++;
	cnt_100ms++;
	if(cnt_100ms >= 100)
	{
		cnt_100ms = 0;
		flag100ms = 1;
	}
	if(cnt_800ms >= 800)
	{
		cnt_800ms = 0;
		flag800ms = 1;
	}
}
