#ifndef _INIT_H
#define _INIT_H

#include <STC15F2K60S2.H>

void SelectHC138(unsigned char channel);
void Init_LED_BUZZ();
void Timer0Init(void);
void Timer1Init(void);

#endif
