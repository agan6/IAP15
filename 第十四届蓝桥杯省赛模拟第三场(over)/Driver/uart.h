#ifndef _UART_H
#define _UART_H

#include <STC15F2K60S2.H>

void UartInit(void);
void SendString(unsigned char *str);

#endif
