#ifndef _ONEWIRE_H
#define _ONEWIRE_H

#include <STC15F2K60S2.H>

sbit DQ = P1^4;

void Init_Temp();
unsigned int Read_Temp();

#endif
