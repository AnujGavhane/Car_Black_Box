#include <xc.h>
#include "eeprom.h"

void write_internal_eeprom(unsigned char address,
                           unsigned char data)
{
    EEADR = address;
    EEDATA = data;

    EEPGD = 0;
    WREN = 1;

    GIE = 0;

    EECON2 = 0x55;
    EECON2 = 0xAA;

    WR = 1;

    while(WR);

    WREN = 0;

    GIE = 1;
}

unsigned char read_internal_eeprom(unsigned char address)
{
    EEADR = address;

    EEPGD = 0;

    RD = 1;

    return EEDATA;
}
