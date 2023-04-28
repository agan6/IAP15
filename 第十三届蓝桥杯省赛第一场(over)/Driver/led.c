#include "led.h"
#include "init.h"

bit Control_LED3 = 0;
extern unsigned int tempbuf;
extern unsigned char Timer_Set[7];
extern unsigned char Temp_Set;
extern bit Control_Mode;
extern bit Time_Mode;
extern bit flag_Relay;
unsigned char Led_Buff[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
unsigned char code Led_Number[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void Display()
{
	static unsigned char i;
	
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

void DisplayMode1()
{
	Led_Buff[0] = 0xC1;
	Led_Buff[1] = Led_Number[1];
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = Led_Number[tempbuf / 100 % 10];
	Led_Buff[6] = Led_Number[tempbuf / 10 % 10] & 0x7F;
	Led_Buff[7] = Led_Number[tempbuf % 10];
}

void DisplayMode2()
{
	Led_Buff[0] = 0xC1;
	Led_Buff[1] = Led_Number[2];
	
	if(Time_Mode == 0)
	{
		Led_Buff[3] = Led_Number[Timer_Set[2] / 16];
		Led_Buff[4] = Led_Number[Timer_Set[2] % 16];
		Led_Buff[5] = 0xBF;
		Led_Buff[6] = Led_Number[Timer_Set[1] / 16];
		Led_Buff[7] = Led_Number[Timer_Set[1] % 16];
	}
	else
	{
		Led_Buff[3] = Led_Number[Timer_Set[1] / 16];
		Led_Buff[4] = Led_Number[Timer_Set[1] % 16];
		Led_Buff[5] = 0xBF;
		Led_Buff[6] = Led_Number[Timer_Set[0] / 16];
		Led_Buff[7] = Led_Number[Timer_Set[0] % 16];
	}
}

void DisplayMode3()
{
	Led_Buff[0] = 0xC1;
	Led_Buff[1] = Led_Number[3];
	Led_Buff[3] = 0xFF;
	Led_Buff[4] = 0xFF;
	Led_Buff[5] = 0xFF;
	Led_Buff[6] = Led_Number[Temp_Set / 10 % 10];
	Led_Buff[7] = Led_Number[Temp_Set % 10];
}

void Led_Single()
{
	P0 = 0xFF;
	if((Timer_Set[1] == 0x00) && ((Timer_Set[0] >= 0x00) && (Timer_Set[0] <= 0x05)))
	{
		SelectHC138(4);
		P00 = 0;
		SelectHC138(0);
	}
	if(Timer_Set[0] == 0x05)
	{
		SelectHC138(4);
		P00 = 1;
		SelectHC138(0);
	}
	if(Control_Mode == 0)
	{
		SelectHC138(4);
		P01 = 0;
		SelectHC138(0);
	}
	else if(Control_Mode == 1)
	{
		SelectHC138(4);
		P01 = 1;
		SelectHC138(0);
	}
	if(flag_Relay == 0)
	{
		SelectHC138(4);
		P02 = 1;
		SelectHC138(0);
	}
	else
	{
		SelectHC138(4);
		P02 = Control_LED3;
		Control_LED3 = ~Control_LED3;
		SelectHC138(0);
	}
}
