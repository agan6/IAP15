#include "main.h"

bit flag100ms = 0;
bit Set_Vep_Mode = 0;
bit Sonic_Mode = 0;
unsigned int Read_vep;
unsigned char DisplayMode = 0;
unsigned char Vep_Max = 45;
unsigned char Vep_Min = 5;
unsigned char Vep_Max_Enter = 45;
unsigned char Vep_Min_Enter = 5;
float dat;
extern unsigned int distance;

void Working();

void main()
{
    Init_BUZZ_LED();
    Timer0Init();
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
        Read_vep = AD_Read(0x43);
        Read_vep = Read_vep * 100 / 51;
		if((Read_vep > (Vep_Min_Enter * 10)) && (Read_vep < (Vep_Max_Enter * 10)))
		{
			Sonic_Mode = 0;
			Get_Distance();
		}
		else
		{
			Sonic_Mode = 1;
		}
		if(Sonic_Mode == 0)
		{
			if(distance <= 20)
			{
				DA_Write(100 * 51 / 100);
			}
			else if(distance >= 500)
			{
				DA_Write(500 * 51 / 100);
			}
			else
			{
				dat = 400 / 60 * distance - 100 / 3;
				dat = dat *
				51 / 100;
				DA_Write(dat);
			}				
		}
		else
		{
			DA_Write(0);
		}
		Led_Single();
		if(DisplayMode == 0)
		{	
			DisplayMode0();
		}
		else if(DisplayMode == 1)
		{
			DisplayMode1();
		}
		else if(DisplayMode == 2)
		{
			DisplayMode2();
		}
    }
}

void KeyAction(unsigned char keycode)
{
	if(DisplayMode == 0)
	{
		if(keycode == '4')
		{
			DisplayMode = 1;
		}
	}
	else if(DisplayMode == 1)
	{
		if(keycode == '4')
		{
			DisplayMode = 2;
			Set_Vep_Mode = 0;
		}
	}
	else if(DisplayMode == 2)
	{
		if(keycode == '4')
		{
			DisplayMode = 0;
			Vep_Max_Enter = Vep_Max;
			Vep_Min_Enter = Vep_Min;
		}
		if(Set_Vep_Mode == 0)
		{
			if(keycode == '3')
			{
				Set_Vep_Mode = 1;
			}
			else if(keycode == '2')
			{
				Vep_Max += 5;
				if(Vep_Max > 50)
				{
					Vep_Max = 5;
				}
				else if(Vep_Max < 5)
				{
					Vep_Max = 50;
				}
			}
			else if(keycode == '1')
			{
				Vep_Max -= 5;
				if(Vep_Max > 50)
				{
					Vep_Max = 5;
				}
				else if(Vep_Max < 5)
				{
					Vep_Max = 50;
				}
			}
		}
		else if(Set_Vep_Mode == 1)
		{
			if(keycode == '3')
			{
				Set_Vep_Mode = 0;
			}
			else if(keycode == '2')
			{
				Vep_Min += 5;
				if(Vep_Min > 50)
				{
					Vep_Min = 5;
				}
				else if(Vep_Min < 5)
				{
					Vep_Min = 50;
				}
			}
			else if(keycode == '1')
			{
				Vep_Min -= 5;
				if(Vep_Min > 50)
				{
					Vep_Min = 5;
				}
				else if(Vep_Min < 5)
				{
					Vep_Min = 50;
				}
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
    if(cnt_100ms >= 200)
    {
        cnt_100ms = 0;
        flag100ms = 1;
    }
}
