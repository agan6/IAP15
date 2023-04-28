#ifndef _SONIC_H
#define _SONIC_H

#include <STC15F2K60S2.H>

sbit TX = P1^0;
sbit RX = P1^1;

void Get_Distance();

#endif
