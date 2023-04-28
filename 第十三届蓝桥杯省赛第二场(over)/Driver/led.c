#include "led.h"
#include "init.h"
#include "sonic.h"

extern unsigned int Read_Vep;
extern unsigned char Vep_Max;
extern unsigned char Vep_Min;
extern unsigned int distance;
extern bit Sonic_Mode;
extern unsigned char DisplayMode;
bit LED7_Flash = 0;
unsigned char code Led_Number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

void Display()
{
    static unsigned char i = 0;

    SelectHC138(7);
    P0 = 0xFF;
    SelectHC138(0);

    P0 = 0x00;
    SelectHC138(6);
    P0 = 0x01 << i;
    SelectHC138(0);

    P0 = 0xFF;
    SelectHC138(7);
    P0 = Led_Buff[i];
    SelectHC138(0);

    i++;
    i &= 0x07;
}

void DisplayMode0()
{
    Led_Buff[0] = 0xC1;
	
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
    Led_Buff[5] = Led_Number[Read_Vep / 100 % 10] & 0x7F;
    Led_Buff[6] = Led_Number[Read_Vep / 10 % 10];
    Led_Buff[7] = Led_Number[Read_Vep % 10];
}

void DisplayMode1()
{
	if(Sonic_Mode == 0)
	{
		Led_Buff[0] = 0xC7;
		Led_Buff[3] = 0xFF;
		Led_Buff[4] = 0xFF;
		if((distance >= 100) && (distance <= 999))
		{
			Led_Buff[5] = Led_Number[distance / 100 % 10];
			Led_Buff[6] = Led_Number[distance / 10 % 10];
			Led_Buff[7] = Led_Number[distance % 10];
		}
		else if((distance >= 10) && (distance <= 99))
		{
			Led_Buff[5] = 0xFF;
			Led_Buff[6] = Led_Number[distance / 10 % 10];
			Led_Buff[7] = Led_Number[distance % 10];
		}
		else if((distance >= 0) && (distance <= 9))
		{
			Led_Buff[5] = 0xFF;
			Led_Buff[6] = 0xFF;
			Led_Buff[7] = Led_Number[distance % 10];
		}
	}
	else if(Sonic_Mode == 1)
	{
		Led_Buff[0] = 0xC7;
		Led_Buff[3] = 0xFF;
		Led_Buff[4] = 0xFF;
		Led_Buff[5] = 0x88;
		Led_Buff[6] = 0x88;
		Led_Buff[7] = 0x88;
	}
}

void DisplayMode2()
{
	Led_Buff[0] = 0x8C;
	
	Led_Buff[3] = Led_Number[Vep_Max / 10 % 10] & 0x7F;
    Led_Buff[4] = Led_Number[Vep_Max % 10];
	Led_Buff[5] = 0xFF;
	Led_Buff[6] = Led_Number[Vep_Min / 10 % 10] & 0x7F;
    Led_Buff[7] = Led_Number[Vep_Min % 10];
}

void Led_Single()
{
	P0 = 0xFF;
	SelectHC138(4);
	if(DisplayMode == 0)
	{
		P00 = 0;
		P01 = 1;
		P02 = 1;
	}
	else if(DisplayMode == 1)
	{
		P00 = 1;
		P01 = 0;
		P02 = 1;
	}
	else if(DisplayMode == 2)
	{
		P00 = 1;
		P01 = 1;
		P02 = 0;
	}
	if(Sonic_Mode == 0)
	{
		P07 = LED7_Flash;
		LED7_Flash = ~LED7_Flash;
	}
	else
	{
		P07 = 1;
	}
	SelectHC138(0);
}
