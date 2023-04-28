#include "main.h"

bit flag800ms = 0;
bit flag500ms = 0;
bit DA_Mode = 0;
bit flag100ms = 0;
unsigned int tempbuf;
unsigned char Set_Temp = 25;
unsigned char Display_Mode = 0;
float DA_Output;

void Working();

void main()
{
	Init_BUZZ_LED();
	Timer0Init();
	Init_Temp();
	while(1)
	{
		Working();
	}
}

void Working()
{
	unsigned int temp;
	KeyDriver();
	if(flag100ms == 1)
	{
		flag100ms = 0;
		Led_Single();
		if(Display_Mode == 0)
		{
			DisplayMode_1();
		}
		else if(Display_Mode == 1)
		{
			DisplayMode_2();
		}
		else if(Display_Mode == 2)
		{
			DisplayMode_3();
		}
	}
	if(flag500ms == 1)
	{
		flag500ms = 0;
		if(DA_Mode == 0)
		{
			if(tempbuf > Set_Temp * 100) 
			{
				DA_Output = 0;
				DA_Write(0);
			}
			else 
			{
				DA_Output = 500;
				DA_Write(255);
			}
		}
		else if(DA_Mode == 1)
		{
			if((tempbuf > 2000) && (tempbuf < 4000))
			{
				DA_Output = tempbuf * 3 / 20 - 200;
				DA_Write((unsigned char)(DA_Output * 51 / 100));
			}
			else if(tempbuf <= 2000)
			{
				DA_Output = 100;
				DA_Write(100 * 51 / 100);
			}
			else if(tempbuf >= 4000)
			{
				DA_Output = 400;
				DA_Write(400 * 51 / 100);
			}
		}
	}
	if(flag800ms == 1)
	{		
		temp = Read_Temp();
		
		if((temp > 4000) || (temp < 0))
		{
			tempbuf = tempbuf;
		}
		else
		{
			tempbuf = temp;
		}
		flag800ms = 0;
		Init_Temp();
	}
}

void KeyAction(unsigned char keycode)
{
	if(keycode == '7')
	{
		if(DA_Mode == 0)
		{
			DA_Mode = 1;
		}
		else if(DA_Mode == 1)
		{
			DA_Mode = 0;
		}
	}
	if(Display_Mode == 0)
	{
		if(keycode == '+')
		{
			Display_Mode = 1;
		}
	}
	else if(Display_Mode == 1)
	{
		if(keycode == '+')
		{
			Display_Mode = 2;
		}
		else if(keycode == '0')
		{
			Set_Temp++;
		}
		else if(keycode == '8')
		{
			Set_Temp--;
		}
	}
	else if(Display_Mode == 2)
	{
		if(keycode == '+')
		{
			Display_Mode = 0;
		}
	}
}

void Timer0Handle() interrupt 1
{
	static unsigned int cnt_800ms = 0;
	static unsigned int cnt_500ms = 0;
	static unsigned int cnt_100ms = 0;
	
	Display();
	KeyScan();
	
	cnt_800ms++;
	cnt_500ms++;
	cnt_100ms++;
	if(cnt_800ms >= 800)
	{
		cnt_800ms = 0;
		flag800ms = 1;
	}
	if(cnt_500ms >= 500)
	{
		cnt_500ms = 0;
		flag500ms = 1;
	}
	if(cnt_100ms >= 100)
	{
		cnt_100ms = 0;
		flag100ms = 1;
	}
}
