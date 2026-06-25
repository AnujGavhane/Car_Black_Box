#include "view_log.h"
#include "clcd.h"
#include "eeprom.h"
#include "matrix_keypad.h"
#include "main.h"

extern unsigned char key;
extern unsigned char log_pos;
extern State_t state;

unsigned char view_index = 0;

void view_log(void)
{
    unsigned char addr;
    char log[9];

    clcd_print("# TIME     EV SP", LINE1(0));

    if(log_pos == 0)
    {
        clear_screen();
        
        clcd_print("NO LOGS", LINE1(4));
        clcd_print("AVAILABLE", LINE2(4));
        
        return;
    }

    addr = (view_index % 10) * 10;

    log[0] = read_internal_eeprom(addr++);
    log[1] = read_internal_eeprom(addr++);
    log[2] = ':';
    log[3] = read_internal_eeprom(addr++);
    log[4] = read_internal_eeprom(addr++);
    log[5] = ':';
    log[6] = read_internal_eeprom(addr++);
    log[7] = read_internal_eeprom(addr++);
    log[8] = '\0';

    char index[3];
    
    index[0] = (view_index / 10) + '0';
    index[1] = (view_index % 10) + '0';
    index[2] = '\0';
    
    clcd_print(index, LINE2(0));
    clcd_print(log, LINE2(2));

    clcd_putch(read_internal_eeprom(addr++), LINE2(11));
    clcd_putch(read_internal_eeprom(addr++), LINE2(12));

    clcd_putch(read_internal_eeprom(addr++), LINE2(14));
    clcd_putch(read_internal_eeprom(addr++), LINE2(15));

    if(key == SW2)
    {
        if(view_index < (log_pos - 1))
        {
            view_index++;
        }
    }

    if(key == SW3)
    {
        if(view_index > 0)
        {
            view_index--;
        }
    }
    
    if(key == SW5)
    {
        return;
    }
}