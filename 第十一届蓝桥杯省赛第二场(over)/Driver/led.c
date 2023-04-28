#include "led.h"
#include "init.h"

extern unsigned int tempbuf;
extern unsigned char temp_Max;
extern unsigned char temp_Min;
extern unsigned char temp_Max_Afe;
extern unsigned char temp_Min_Afe;
unsigned char code Led_Number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

void Display()
{
	static unsigned char i;
	
	SelectHC138(6);
	P0 = 0x00;
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
	Led_Buff[0] = 0xC6;
	
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
	
	Led_Buff[6] = Led_Number[tempbuf / 10 % 10];
	Led_Buff[7] = Led_Number[tempbuf % 10];
}

void DisplayMode1()
{
	Led_Buff[0] = 0x8C;

	Led_Buff[3] = Led_Number[temp_Max / 10 % 10];
	Led_Buff[4] = Led_Number[temp_Max % 10];
	
	Led_Buff[6] = Led_Number[temp_Min / 10 % 10];
	Led_Buff[7] = Led_Number[temp_Min % 10];
}

void Led_Single()
{
	P0 = 0xFF;
	SelectHC138(4);
	if(tempbuf > temp_Max)
	{
		P00 = 0;
	}
	else
	{
		P00 = 1;
	}
	if((tempbuf >= temp_Min) && (tempbuf <= temp_Max))
	{
		P01 = 0;
	}
	else
	{
		P01 = 1;
	}
	if(tempbuf < temp_Min)
	{
		P02 = 0;
	}
	else
	{
		P02 = 1;
	}
	if(temp_Max_Afe < temp_Min_Afe)
	{
		P03 = 0;
	}
	else
	{
		P03 = 1;
	}
	SelectHC138(0);
}
