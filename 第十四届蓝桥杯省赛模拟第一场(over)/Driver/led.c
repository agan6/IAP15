#include "led.h"
#include "init.h"

extern unsigned int distance;
extern int distance_Set;
extern bit DisplayMode;
bit LED3_Flash = 0;
unsigned char code Led_Number[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
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
	
	Led_Buff[5] = Led_Number[(distance / 100) % 10];
	Led_Buff[6] = Led_Number[(distance / 10) % 10];
	Led_Buff[7] = Led_Number[distance % 10];
}

void DisplayMode1()
{
	Led_Buff[0] = 0xC1;
	Led_Buff[1] = Led_Number[2];
	
	Led_Buff[5] = Led_Number[distance_Set / 100 % 10];
	Led_Buff[6] = Led_Number[distance_Set / 10 % 10];
	Led_Buff[7] = Led_Number[distance_Set % 10];
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
	if(distance > distance_Set)
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
