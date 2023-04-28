#include "main.h"

bit Start_T0 = 0;
bit flag1s = 0;
bit flag500ms = 0;
bit Display_mode = 0;
bit DAC_mode = 0;
bit Display_Enable = 0;
unsigned char Set_dat;
unsigned int Feaq_Cnt;
unsigned int Temp;

void working();
void ReadFreq(unsigned int *dat);

void main()
{
	Init_LED_BUZZ();
	Timer0Init();
	Timer1Init();
	EA = 1;
	while(1)
	{
		working();
	}
}

void working()
{
	KeyDriver();
		
	if(Start_T0 == 1)
	{
		Start_T0 = 0;
		TR0 = 1;
	}
	if(flag1s == 1)
	{	
		flag1s = 0;
		ReadFreq(&Feaq_Cnt);
		Led_Single();
		if(Display_Enable == 0)
		{
			if(Display_mode == 0)
			{			
				DisplayMode_1();
			}
		}
		else if(Display_Enable == 1)
		{
			DisplayMode_OFF();
		}
		if(DAC_mode == 0)
		{
			Set_dat = 200 * 51 / 100;
			DA_Write(Set_dat);
		}
		else if(DAC_mode == 1)
		{
			DA_Write(AD_Read(0x43));
		}
	}
	
	if(flag500ms == 1)
	{
		flag500ms = 0;
		Temp = (unsigned int)AD_Read(0x43);
		Temp = Temp * 100 / 51;
		if(Display_Enable == 0)
		{
			if(Display_mode == 1)
			{
				DisplayMode_2();
			}
		}
		else if(Display_Enable == 1)
		{
			DisplayMode_OFF();
		}
	}
}

void ReadFreq(unsigned int *dat)
{
	TR0 = 0;
	*dat = TH0;
	*dat = (*dat << 8 | TL0) / 2;
	TH0 = 0;
	TL0 = 0;
}

void KeyAction(unsigned char keycode)
{
	if(Display_Enable == 0)
	{
		if(Display_mode == 0)
		{
			if(keycode == '4')
			{
				Display_mode = 1;
			}
		}
		else if(Display_mode == 1)
		{
			if(keycode == '4')
			{
				Display_mode = 0;
			}
		}
		if(keycode == '1')
		{
			Display_Enable = 1;
		}
	}
	else if(Display_Enable == 1)
	{
		if(keycode == '1')
		{
			Display_Enable = 0;
		}
	}
	if(DAC_mode == 0)
	{
		if(keycode == '3')
		{
			DAC_mode = 1;
		}
	}
	else if(DAC_mode == 1)
	{
		if(keycode == '3')
		{
			DAC_mode = 0;
		}
	}
}

void Timer1Handle() interrupt 3
{
	static unsigned int index = 0;
	static unsigned int cnt = 0;
	
	Display();
	KeyScan();
	
	if(index == 0)
	{
		Start_T0 = 1;
	}
	index++;
	if(index >= 1000)
	{
		index = 0;
		flag1s = 1;
	}
	
	cnt++;
	if(cnt >= 500)
	{
		cnt = 0;
		flag500ms = 1;
	}
}
