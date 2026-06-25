#include "set_time.h"
#include "clcd.h"
#include "ds1307.h"
#include "matrix_keypad.h"

extern unsigned char key;
extern State_t state;

unsigned char hh = 12;
unsigned char mm = 0;
unsigned char ss = 0;

unsigned char field = 0;

void set_time(void)
{
    char buf[9];

    buf[0] = (hh / 10) + '0';
    buf[1] = (hh % 10) + '0';
    buf[2] = ':';

    buf[3] = (mm / 10) + '0';
    buf[4] = (mm % 10) + '0';
    buf[5] = ':';

    buf[6] = (ss / 10) + '0';
    buf[7] = (ss % 10) + '0';
    buf[8] = '\0';

    clcd_print("SET TIME", LINE1(0));
    clcd_print(buf, LINE2(0));
    
    if(field == 0)
    
    {
        clcd_putch('^', LINE1(0));
        clcd_putch('^', LINE1(1));
    }
    else if(field == 1)
    {
        clcd_putch('^', LINE1(3));
        clcd_putch('^', LINE1(4));
    }
    else if(field == 2)
    {
        clcd_putch('^', LINE1(6));
        clcd_putch('^', LINE1(7));
    }

    if(key == SW4)
    {
        if(field == 0)
        {
            hh = (hh + 1) % 24;
        }
        else if(field == 1)
        {
            mm = (mm + 1) % 60;
        }
        else if(field == 2)
        {
            ss = (ss + 1) % 60;
        }
    }

    if(key == SW5)
    {
        if(field < 2)
    {
        field++;
    }
        else
        {
            write_ds1307(HOUR_ADDR,
                    ((hh / 10) << 4) | (hh % 10));
            
            write_ds1307(MIN_ADDR,
                    ((mm / 10) << 4) | (mm % 10));
            
            write_ds1307(SEC_ADDR,
                    ((ss / 10) << 4) | (ss % 10));
            
            field = 0;
            
            clear_screen();
            
            state = MENU;
        }
    }
}
