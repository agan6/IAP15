#include "led.h"
#include "init.h"

unsigned char code Led_Number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
extern unsigned int Read_Vep; 
extern int Set_Vep;
extern unsigned char Change_Number;
extern unsigned char Error_Cnt;
extern bit flag5s;

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

    Led_Buff[5] = Led_Number[Read_Vep / 100 % 10] & 0x7F;
    Led_Buff[6] = Led_Number[Read_Vep / 10 % 10];
    Led_Buff[7] = Led_Number[Read_Vep % 10];
}

void DisplayMode1()
{
	Led_Buff[0] = 0x8C;
	
	Led_Buff[5] = Led_Number[Set_Vep / 100 % 10] & 0x7F;
    Led_Buff[6] = Led_Number[Set_Vep / 10 % 10];
    Led_Buff[7] = Led_Number[Set_Vep % 10];
}

void DisplayMode2()
{
	Led_Buff[0] = 0xC8;
	
	Led_Buff[5] = 0xFF;
    Led_Buff[6] = Led_Number[Change_Number / 10 % 10];
    Led_Buff[7] = Led_Number[Change_Number % 10];
}

void Led_Single()
{
	P0 = 0xFF;
	SelectHC138(4);
	if(flag5s == 1)
	{
		P00 = 0;
	}
	else
	{
		P00 = 1;
	}
	if(Change_Number % 2 == 1)
	{
		P01 = 0;
	}
	else
	{
		P01 = 1;
	}
	if(Error_Cnt >= 3)
	{
		P02 = 0;
	}
	else
	{
		P02 = 1;
	}
	SelectHC138(0);
}
