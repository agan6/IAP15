#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <STC15F2K60S2.H>

sbit KEY_IN_1 = P3^0;
sbit KEY_IN_2 = P3^1;
sbit KEY_IN_3 = P3^2;
sbit KEY_IN_4 = P3^3;

void KeyDriver();
void KeyScan();

#endif
