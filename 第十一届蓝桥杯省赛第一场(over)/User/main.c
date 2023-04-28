#include "main.h"

bit flag100ms = 0;
bit flag5s = 0;
unsigned char DisplayMode = 0;
unsigned int Read_Vep;
unsigned int Read_Vep_Org;
unsigned int Read_Vep_Afe;
int Set_Vep = 300;
unsigned char Change_Number = 0;
unsigned char Error_Cnt = 0;

void Working();

void main()
{
    Init_BUZZ_LED();
    Timer0Init();
	Set_Vep = Eeprom_Read(0x00);
	Set_Vep = Set_Vep * 10;
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
        Read_Vep = AD_Read(0x43) * 100 / 51;
		Read_Vep_Org = Read_Vep;
		Read_Vep = AD_Read(0x43) * 100 / 51;
		Read_Vep_Afe = Read_Vep;
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
		if((Read_Vep_Org > Set_Vep) && (Read_Vep_Afe < Set_Vep))
		{
			Change_Number++;
		}
    }
}

void KeyAction(unsigned char keycode)
{
	if(DisplayMode == 0)
	{
		if(keycode == '-')
		{
			Error_Cnt = 0;
			DisplayMode = 1;
		}
		else
		{
			Error_Cnt++;
		}
	}
	else if(DisplayMode == 1)
	{
		if(keycode == '-')
		{
			Error_Cnt = 0;
			DisplayMode = 2;
			Eeprom_Write(0x00, Set_Vep / 10);
		}
		else if(keycode == 'D')
		{
			Error_Cnt = 0;
			Set_Vep += 50;
			if(Set_Vep > 500)
			{
				Set_Vep = 0;
			}
		}
		else if(keycode == 'C')
		{
			Error_Cnt = 0;
			Set_Vep -= 50;
			if(Set_Vep < 0)
			{
				Set_Vep = 500;
			}
		}
		else
		{
			Error_Cnt++;
		}
	}
	else if(DisplayMode == 2)
	{
		if(keycode == '-')
		{
			DisplayMode = 0;
			Error_Cnt = 0;
		}
		else if(keycode == '9')
		{
			Change_Number = 0;
			Error_Cnt = 0;
		}
		else
		{
			Error_Cnt++;
		}
	}
}

void Timer0Handle() interrupt 1
{
    static unsigned char cnt_100ms = 0;
	static unsigned int cnt_5s = 0;

	Display();
	KeyScan();
	
    cnt_100ms++;
    if(cnt_100ms >= 100)
    {
        cnt_100ms = 0;
        flag100ms = 1;
    }
	
	if(Read_Vep < Set_Vep)
	{
		cnt_5s++;
	}
	else
	{
		cnt_5s = 0;
	}
	if(cnt_5s >= 5000)
	{
		flag5s = 1;
	}
	else
	{
		flag5s = 0;
	}
}
