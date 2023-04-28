#include "led.h"
#include "init.h"
#include "string.h"

unsigned char code Led_Number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
extern unsigned int Readtemp;
extern unsigned int Display_Vep;
extern bit DisplayMode;
extern bit Enable;
extern unsigned char index;
extern unsigned char xdata Uart_Recv[20];

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
	Led_Buff[1] = Led_Number[1];
	
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = Led_Number[Readtemp / 100 % 10];
	Led_Buff[6] = Led_Number[Readtemp / 10 % 10] & 0x7F;
	Led_Buff[7] = Led_Number[Readtemp % 10];
}

void DisplayMode1()
{
	Led_Buff[0] = 0xC1;
	Led_Buff[1] = Led_Number[2];
	
	if((Display_Vep >= 1000) && (Display_Vep <= 9999))
	{
		Led_Buff[4] = Led_Number[Display_Vep / 1000 % 10];
		Led_Buff[5] = Led_Number[Display_Vep / 100 % 10] & 0x7F;
		Led_Buff[6] = Led_Number[Display_Vep / 10 % 10];
		Led_Buff[7] = Led_Number[Display_Vep % 10];
	}
	else if((Display_Vep >= 100) && (Display_Vep <= 999))
	{
		Led_Buff[4] = 0xFF;
		Led_Buff[5] = Led_Number[Display_Vep / 100 % 10] & 0x7F;
		Led_Buff[6] = Led_Number[Display_Vep / 10 % 10];
		Led_Buff[7] = Led_Number[Display_Vep % 10];
	}
}

void DisplayModeOFF()
{
	Led_Buff[0] = 0xFF;
	Led_Buff[1] = 0xFF;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = 0xFF;
	Led_Buff[6] = 0xFF;
	Led_Buff[7] = 0xFF;
}

void Led_Single()
{
	P0 = 0xFF;
	SelectHC138(4);
	if(Enable == 0)
	{
		P00 = 0;
	}
	else
	{
		P00 = 1;	
	}
	if(DisplayMode == 0)
	{
		P01 = 0;
	}
	else
	{
		P01 = 1;
	}
	if(DisplayMode == 1)
	{
		P02 = 0;
	}
	else
	{
		P02 = 1;	
	}
	if((Readtemp < 200) || (Readtemp > 260))
	{
		P05 = 0;
	}
	else
	{
		P05 = 1;
	}
	if(strcmp(Uart_Recv,"Open\r\n") == 0)
	{
		P07 = 0;
		index = 0;
	}
	else
	{
		P07 = 1;
	}
	SelectHC138(0);
}
