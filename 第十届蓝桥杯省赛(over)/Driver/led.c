#include "led.h"
#include "init.h"

unsigned char code Led_Number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

extern unsigned int Feaq_Cnt;
extern unsigned int Temp;
extern bit Display_mode;
extern bit DAC_mode;

void Display()
{
	static unsigned char i = 0;
	
	SelectHC138(6);
	P0 = 0x00;
	SelectHC138(7);
	P0 = 0xFF;
	
	SelectHC138(6);
	P0 = 0x01 << i;
	SelectHC138(0);
	
	P0 = 0xFF;
	SelectHC138(7);
	P0 = Led_Buff[i];
	SelectHC138(0);
	P0 = 0x00;
	
	i++;
	i &= 0x07;
}

void DisplayMode_1()
{
	Led_Buff[0] = 0x8E;
	if(Feaq_Cnt < 100)
	{
		Led_Buff[3] = 0xFF;
		Led_Buff[4] = 0xFF;
		Led_Buff[5] = 0xFF;
		Led_Buff[6] = Led_Number[Feaq_Cnt / 10 % 10];
		Led_Buff[7] = Led_Number[Feaq_Cnt % 10];
	}
	else if((Feaq_Cnt >= 100)&&(Feaq_Cnt < 1000))
	{
		Led_Buff[3] = 0xFF;
		Led_Buff[4] = 0xFF;
		Led_Buff[5] = Led_Number[Feaq_Cnt / 100 % 10];
		Led_Buff[6] = Led_Number[Feaq_Cnt / 10 % 10];
		Led_Buff[7] = Led_Number[Feaq_Cnt % 10];
	}
	else if((Feaq_Cnt >= 1000)&&(Feaq_Cnt < 10000))
	{
		Led_Buff[3] = 0xFF;
		Led_Buff[4] = Led_Number[Feaq_Cnt / 1000 % 10];
		Led_Buff[5] = Led_Number[Feaq_Cnt / 100 % 10];
		Led_Buff[6] = Led_Number[Feaq_Cnt / 10 % 10];
		Led_Buff[7] = Led_Number[Feaq_Cnt % 10];
	}
	else if((Feaq_Cnt >= 10000)&&(Feaq_Cnt < 100000))
	{	
		Led_Buff[3] = Led_Number[Feaq_Cnt / 10000 % 10];
		Led_Buff[4] = Led_Number[Feaq_Cnt / 1000 % 10];
		Led_Buff[5] = Led_Number[Feaq_Cnt / 100 % 10];
		Led_Buff[6] = Led_Number[Feaq_Cnt / 10 % 10];
		Led_Buff[7] = Led_Number[Feaq_Cnt % 10];
	}
}

void DisplayMode_2()
{
	Led_Buff[0] = 0xC1;
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = Led_Number[Temp / 100 % 10] & 0x7F;
	Led_Buff[6] = Led_Number[Temp / 10 % 10];
	Led_Buff[7] = Led_Number[Temp % 10];
}

void DisplayMode_OFF()
{
	Led_Buff[0] = 0xFF;
	Led_Buff[1] = 0xFF;
	Led_Buff[2] = 0xFF;
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = 0xFF;
	Led_Buff[6] = 0xFF;
	Led_Buff[7] = 0xFF;
}

void Led_Single()
{
	P0 = 0xFF;
	if(Display_mode == 0)
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P00 = 1;
		P01 = 0;
		SelectHC138(0);
	}
	else if(Display_mode == 1)
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P00 = 0;
		P01 = 1;
		SelectHC138(0);
	}
	if((Temp >= 150) && (Temp < 250))
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P02 = 0;
		SelectHC138(0);
	}
	else if(Temp >= 350)
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P02 = 0;
		SelectHC138(0);
	}
	else
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P02 = 1;
		SelectHC138(0);
	}
	if((Feaq_Cnt >= 1000) && (Feaq_Cnt < 5000))
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P03 = 0;
		SelectHC138(0);
	}
	if(Feaq_Cnt >= 10000)
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P03 = 0;
		SelectHC138(0);
	}
	else
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P03 = 1;
		SelectHC138(0);
	}
	if(DAC_mode == 0)
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P04 = 1;
		SelectHC138(0);
	}
	else
	{
		P0 |= 0xE0;
		SelectHC138(4);
		P04 = 0;
		SelectHC138(0);
	}
}
