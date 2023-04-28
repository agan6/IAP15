#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <STC15F2K60S2.H>

sbit KEY_IN_1 = P4^4;
sbit KEY_IN_2 = P4^2;
sbit KEY_IN_3 = P3^5;
sbit KEY_IN_4 = P3^4;
sbit KEY_OUT_1 = P3^2;
sbit KEY_OUT_2 = P3^3;

void KeyDriver();
void KeyScan();

#endif
