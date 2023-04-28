/*	# 	DS1302代码片段说明
	1. 	本文件夹中提供的驱动代码供参赛选手完成程序设计参考。
	2. 	参赛选手可以自行编写相关代码或以该代码为基础，根据所选单片机类型、运行速度和试题
		中对单片机时钟频率的要求，进行代码调试和修改。
*/								

//
#include "ds1302.h"
#include "intrins.h"

unsigned char Time_Read_Addr[7] = {0x81,0x83,0x85,0x87,0x89,0x8B,0x8D};
unsigned char Time_Write_Addr[7] = {0x80,0x82,0x84,0x86,0x88,0x8A,0x8C};
unsigned char Timer_Set[7] = {0x55,0x59,0x23,0x30,0x03,0x07,0x23};

void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//
unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

void Read_DS1302()
{
	unsigned char i;
	
	for(i = 0; i < 7; i++)
	{
		Timer_Set[i] = Read_Ds1302_Byte(Time_Read_Addr[i]);
	}
}

void Init_DS1302()
{
	unsigned char i;
	
	Write_Ds1302_Byte(0x8E,0x00);
	for(i = 0; i < 7; i++)
	{
		Write_Ds1302_Byte(Time_Write_Addr[i],Timer_Set[i]);
	}
	Write_Ds1302_Byte(0x8E,0x80);
}
