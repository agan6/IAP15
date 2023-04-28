#include "led.h"
#include "init.h"
#include "onewire.h"

extern unsigned char Set_Temp;
extern unsigned int tempbuf;
extern bit DA_Mode;
extern unsigned char Display_Mode;
extern float DA_Output;
unsigned char code Led_Number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

void Display()
{
	static unsigned char i = 0;
	
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

void DisplayMode_1()
{
	Led_Buff[0] = 0xC6;
	Led_Buff[4] = Led_Number[tempbuf / 1000 % 10];
	Led_Buff[5] = Led_Number[tempbuf / 100 % 10] & 0x7F;
	Led_Buff[6] = Led_Number[tempbuf / 10 % 10];
	Led_Buff[7] = Led_Number[tempbuf % 10];
}

void DisplayMode_2()
{
	Led_Buff[0] = 0x8C;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = 0xFF;
	Led_Buff[6] = Led_Number[Set_Temp / 10 % 10];
	Led_Buff[7] = Led_Number[Set_Temp % 10];
}

void DisplayMode_3()
{	
	Led_Buff[0] = 0x88;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = Led_Number[(unsigned int)DA_Output / 100 % 10] & 0x7F;
	Led_Buff[6] = Led_Number[(unsigned int)DA_Output / 10 % 10];
	Led_Buff[7] = Led_Number[(unsigned int)DA_Output % 10];
}

void Led_Single()
{
	P0 = 0xFF;
	if(DA_Mode == 0)
	{
		SelectHC138(4);
		P00 = 0;
		SelectHC138(0);
	}
	else
	{
		SelectHC138(4);
		P00 = 1;
		SelectHC138(0);
	}
	if(Display_Mode == 0)
	{
		SelectHC138(4);
		P01 = 0;
		SelectHC138(0);
	}
	else
	{	
		SelectHC138(4);
		P01 = 1;
		SelectHC138(0);
	}
	if(Display_Mode == 1)
	{
		SelectHC138(4);
		P02 = 0;
		SelectHC138(0);
	}
	else
	{	
		SelectHC138(4);
		P02 = 1;
		SelectHC138(0);
	}
	if(Display_Mode == 2)
	{
		SelectHC138(4);
		P03 = 0;
		SelectHC138(0);
	}
	else
	{	
		SelectHC138(4);
		P03 = 1;
		SelectHC138(0);
	}
}
