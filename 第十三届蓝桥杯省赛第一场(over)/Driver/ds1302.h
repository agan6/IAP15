#ifndef _DS1302_H
#define _DS1302_H

#include <STC15F2K60S2.H>

sbit SCK = P1^7;
sbit SDA = P2^3;
sbit RST = P1^3;

void Init_DS1302();
void Read_DS1302();

#endif
