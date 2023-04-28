#ifndef _IIC_H
#define _IIC_H

#include <STC15F2K60S2.H>

sbit scl = P2^0;
sbit sda = P2^1;

unsigned char AD_Read(unsigned char addr);
void DA_Write(unsigned char dat);
unsigned char Eeprom_Read(unsigned char addr);
void Eeprom_Write(unsigned char addr, unsigned char dat);

#endif
