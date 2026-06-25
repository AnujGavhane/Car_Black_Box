#include "download_log.h"
#include "uart.h"
#include "eeprom.h"

extern unsigned char log_pos;

void download_log(void)
{
    unsigned char i;
    unsigned char addr;

    puts_uart("\r\nDOWNLOAD STARTED\r\n");
    puts_uart("\r\n----- LOG DATA -----\r\n");
    
    if(log_pos == 0)
    {
        puts_uart("\r\nNO LOGS AVAILABLE\r\n");
        return;
    }

    for(i = 0; i < log_pos && i < 10; i++)
    {
        addr = i * 10;

        putch(i + '0');
        putch(' ');

        putch(read_internal_eeprom(addr++));
        putch(read_internal_eeprom(addr++));
        putch(':');

        putch(read_internal_eeprom(addr++));
        putch(read_internal_eeprom(addr++));
        putch(':');

        putch(read_internal_eeprom(addr++));
        putch(read_internal_eeprom(addr++));

        putch(' ');

        putch(read_internal_eeprom(addr++));
        putch(read_internal_eeprom(addr++));

        putch(' ');

        putch(read_internal_eeprom(addr++));
        putch(read_internal_eeprom(addr++));

        puts_uart("\r\n");
    }

    puts_uart("--------------------\r\n");
}