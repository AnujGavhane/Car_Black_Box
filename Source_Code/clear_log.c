#include "clear_log.h"
#include "event_log.h"
#include "clcd.h"
#include "eeprom.h"

extern unsigned char log_pos;

void clear_log(void)
{
    clcd_print("CLEAR LOG ?", LINE1(0));
    clcd_print("SW4:YES SW5:NO", LINE2(0));
}

void clear_all_logs(void)
{
    unsigned char i;

    for(i = 0; i < 100; i++)
    {
        write_internal_eeprom(i, 0xFF);
    }

    log_pos = 0;
}