#include "main.h"

bit flag100ms = 0;
bit flag800ms = 0;
bit DisplayMode = 0;
bit flag3s = 0;
bit Enable = 1;
unsigned int Readtemp;
unsigned char Read_Vep;
unsigned int Display_Vep;
float Vep_Buff;
extern unsigned char xdata Uart_Recv[20];
extern unsigned char index;
unsigned char xdata str[20] = {0};

void Working();
void Relay();

void main()
{
	Init_BUZZ_LED();
	InitDS18B20();
	Timer0Init();
	UartInit();
	EA = 1;
	while(1)
	{
		KeyDriver();
		Working();
	}
}

void Working()
{
	if(flag100ms == 1)
	{
		flag100ms = 0;
		Read_Vep = AD_Read(0x43);
		Vep_Buff = Read_Vep * 100 / 51;
		Vep_Buff = 1000 / 500 * Vep_Buff;
		Display_Vep = Vep_Buff;
		Led_Single();
		if(DisplayMode == 0)
		{
			DisplayMode0();
		}
		else
		{
			DisplayMode1();
		}
		Relay();
	}
	if(flag800ms == 1)
	{
		flag800ms = 0;
		Readtemp = Read_Temp();
		InitDS18B20();
	}
	if(flag3s == 1)
	{
		flag3s = 0;
		SendString("Over!\r\n");
		Uart_Recv[0] = 'F';
		index = 0;
	}
	if(Uart_Recv[0] == '1')
	{
		sprintf(str,"C:%.1f\r\n",(float)Readtemp / 10);
		SendString(str);
		Uart_Recv[0] = 'F';
		index = 0;
	}
	else if(Uart_Recv[0] == '2')
	{
		sprintf(str,"D:%.2fppm\r\n",(float)Display_Vep / 100);
		SendString(str);
		Uart_Recv[0] = 'F';
		index = 0;
	}
	else if((Uart_Recv[0] != '2') && (Uart_Recv[0] != '1') && (Uart_Recv[0] != 'O'))
	{
		Uart_Recv[0] = 'F';
		index = 0;
	}
}

void KeyAction(unsigned char keycode)
{
	if(Enable == 0)
	{
		if(keycode == '1')
		{
			if(DisplayMode == 0)
			{
				DisplayMode = 1;
			}
			else
			{
				DisplayMode = 0;
			}
		}
		else if(keycode == '4')
		{
			Enable = 1;
			DisplayModeOFF();
			Init_BUZZ_LED();
		}
	}
	else
	{
		if(keycode == '4')
		{
			Enable = 0;
			Uart_Recv[0] = 'C';
			index = 0;
			DisplayMode = 0;		
		}
	}		
}

void Relay()
{
	P0 = 0x00;
	SelectHC138(5);
	if(Display_Vep < 300)
	{
		P04 = 1;
	}
	else
	{
		P04 = 0;
	}
	SelectHC138(0);
}

void Timer0Handle() interrupt 1
{	
	static unsigned char cnt_100ms = 0;
	static unsigned int cnt_800ms = 0;
	static unsigned int cnt_3s = 0;
	
	Display();
	KeyScan();
	
	if(Enable == 0)
	{
		cnt_100ms++;
		cnt_800ms++;
		if(cnt_100ms >= 100)
		{
			cnt_100ms = 0;
			flag100ms = 1;
		}
		if(cnt_800ms >= 800)
		{
			cnt_800ms = 0;
			flag800ms = 1;
		}
		if(strcmp(Uart_Recv,"Open\r\n") == 0)
		{
			cnt_3s++;
		}
		else
		{
			cnt_3s = 0;
		}
		if(cnt_3s >= 3000)
		{
			cnt_3s = 0;
			flag3s = 1;
		}
	}
	else
	{
		cnt_100ms = 0;
		cnt_800ms = 0;
		cnt_3s = 0;
	}
}
