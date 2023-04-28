#include "led.h"
#include "init.h"

bit LED3_Flash = 0;
extern unsigned int Noise;
extern int Noise_Set;
extern bit DisplayMode;
unsigned char code Led_Number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

void Display()
{
	static unsigned char i;
	
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
	Led_Buff[1] = Led_Number[1];
	
	if((Noise >= 100) && (Noise <= 900))
	{
		Led_Buff[5] = Led_Number[Noise / 100 % 10];
		Led_Buff[6] = Led_Number[Noise / 10 % 10] & 0x7F;
		Led_Buff[7] = Led_Number[Noise % 10];
	}
	else if((Noise >= 10) && (Noise <= 99))
	{
		Led_Buff[5] = 0xFF;
		Led_Buff[6] = Led_Number[Noise / 10 % 10] & 0x7F;
		Led_Buff[7] = Led_Number[Noise % 10];
	}
}

void DisplayMode1()
{
	Led_Buff[0] = 0xC1;
	Led_Buff[1] = Led_Number[2];
	Led_Buff[5] = 0xFF;
	
	if((Noise_Set >= 10) && (Noise_Set <= 99))
	{
		Led_Buff[6] = Led_Number[Noise_Set / 10 % 10];
		Led_Buff[7] = Led_Number[Noise_Set % 10];
	}
	else if((Noise_Set >= 0) && (Noise_Set <= 9))
	{
		Led_Buff[6] = 0xFF;
		Led_Buff[7] = Led_Number[Noise_Set % 10];
	}
}

void Led_Single()
{
	P0 = 0xFF;
	SelectHC138(4);
	if(DisplayMode == 0)
	{
		P00 = 0;
	}
	else
	{
		P00 = 1;
	}
	if(DisplayMode == 1)
	{
		P01 = 0;
	}
	else
	{
		P01 = 1;
	}
	if(Noise > Noise_Set * 10)
	{
		P02 = LED3_Flash;
		LED3_Flash = ~LED3_Flash;
	}
	else
	{
		P02 = 1;
	}
	SelectHC138(0);
}
