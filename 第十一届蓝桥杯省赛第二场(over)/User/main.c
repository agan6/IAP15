#include "main.h"

bit flag100ms = 0;
bit flag800ms = 0;
bit DisplayMode = 0;
bit temp_Change = 1;
unsigned int tempbuf;
unsigned char temp_Max = 30;
unsigned char temp_Min = 20;
unsigned char temp_Max_Org;
unsigned char temp_Min_Org;
unsigned char temp_Max_Afe;
unsigned char temp_Min_Afe;

void Working();

void main()
{
	Init_BUZZ_LED();
	Timer0Init();
	InitDS18B20();
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
		Led_Single();
		if(DisplayMode == 0)
		{
			DisplayMode0();
		}
		else if(DisplayMode == 1)
		{
			DisplayMode1();
		}
		if(tempbuf > temp_Max)
		{
			DA_Write(255 * 4 / 5);
		}
		else if((tempbuf >= temp_Min) && (tempbuf <= temp_Max))
		{
			DA_Write(255 * 3 / 5);
		}
		else if(tempbuf < temp_Min)
		{
			DA_Write(255 * 2 / 5);
		}
	}
	if(flag800ms == 1)
	{
		flag800ms = 0;
		tempbuf = Read_Temp();
		InitDS18B20();
	}
}

void KeyAction(unsigned char keycode)
{
	if(keycode == '4')
	{
		if(DisplayMode == 0)
		{
			temp_Change = 1;
			DisplayMode = 1;
			temp_Max_Org = temp_Max;
			temp_Min_Org = temp_Min;
		}
		else if(DisplayMode == 1)
		{
			DisplayMode = 0;
			temp_Max_Afe = temp_Max;
			temp_Min_Afe = temp_Min;
			if(temp_Max < temp_Min)
			{
				temp_Max = temp_Max_Org;
				temp_Min = temp_Min_Org;
			}
		}
	}
	if(temp_Change == 0)
	{
		if(keycode == '3')
		{
			temp_Change = 1;
		}
		else if(keycode == '2')
		{
			if((temp_Max >= 0) && (temp_Max < 100))
			{
				temp_Max++;
			}
		}
		else if(keycode == '1')
		{
			if((temp_Max >= 0) && (temp_Max < 100))
			{
				temp_Max--;
			}
		}
	}
	else if(temp_Change == 1)
	{
		if(keycode == '3')
		{
			temp_Change = 0;
		}
		else if(keycode == '2')
		{
			if((temp_Min >= 0) && (temp_Min < 100))
			{
				temp_Min++;
			}
		}
		else if(keycode == '1')
		{
			if((temp_Min >= 0) && (temp_Min < 100))
			{
				temp_Min--;
			}
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
