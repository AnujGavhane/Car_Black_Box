#include <xc.h>
#include "uart.h"

void init_uart(void)
{
    TRISC6 = 0;
    TRISC7 = 1;

    BRGH = 1;
    SPBRG = 129;      // 9600 baud @20MHz

    SYNC = 0;
    SPEN = 1;

    TXEN = 1;
    CREN = 1;
}

void putch(unsigned char data)
{
    while(!TXIF);

    TXREG = data;
}

void puts_uart(const char *str)
{
    while(*str)
    {
        putch(*str++);
    }
}