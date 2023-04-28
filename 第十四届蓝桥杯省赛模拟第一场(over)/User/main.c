#include "main.h"

bit flag200ms = 0;
bit DisplayMode = 0;
int distance_Set = 30;
extern unsigned int distance;
unsigned char xdata str[20] = {0};

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
	if(flag200ms == 1)
	{
		flag200ms = 0;
		Get_Distance();
		Led_Single();
		if(DisplayMode == 0)
		{
			DisplayMode0();
		}
		else if(DisplayMode == 1)
		{
			DisplayMode1();
		}
	}
}

void KeyAction(unsigned char keycode)
{
	if(DisplayMode == 0)
	{
		if(keycode == '+')
		{
			DisplayMode = 1;
		}
		else if(keycode == '0')
		{
			distance_Set = distance;
		}
	}
	else if(DisplayMode == 1)
	{
		if(keycode == '+')
		{
			DisplayMode = 0;
		}
		else if(keycode == '-')
		{
			distance_Set += 10;
		}
		else if(keycode == 'D')
		{
			distance_Set -= 10;
			if(distance_Set <= 0)
			{
				distance_Set = 0;
			}
		}
	}
	if(keycode == '8')
	{
		sprintf(str,"Distance:%dcm\r\n",distance);
		SendString(str);
	}
}

void Timer0Handle() interrupt 1
{
	static unsigned char cnt_200ms = 0;
	
	Display();
	KeyScan();
	
	cnt_200ms++;
	if(cnt_200ms >= 100)
	{
		cnt_200ms = 0;
		flag200ms = 1;
	}
}
