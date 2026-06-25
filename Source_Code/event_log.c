#include "event_log.h"
#include "eeprom.h"
#include "ds1307.h"

extern unsigned char speed;
extern unsigned char event_pos;
extern char time[];

extern char *event[];

unsigned char log_pos = 0;

void write_log_eeprom(void)
{
    unsigned char addr;

    addr = (log_pos % 10) * 10;

    write_internal_eeprom(addr++, time[0]);
    write_internal_eeprom(addr++, time[1]);
    write_internal_eeprom(addr++, time[3]);
    write_internal_eeprom(addr++, time[4]);
    write_internal_eeprom(addr++, time[6]);
    write_internal_eeprom(addr++, time[7]);

    write_internal_eeprom(addr++, event[event_pos][0]);
    write_internal_eeprom(addr++, event[event_pos][1]);

    write_internal_eeprom(addr++, (speed / 10) + '0');
    write_internal_eeprom(addr++, (speed % 10) + '0');

    log_pos++;
}

void log_event(void)
{
    write_log_eeprom();
}