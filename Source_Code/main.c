/*
 * File:   main.c
 * Author: Anuj
 * Project: car_black_box
 */

#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "i2c.h"
#include "ds1307.h"
#include "event_log.h"
#include "view_log.h"
#include "clear_log.h"
#include "uart.h"
#include "download_log.h"
#include "set_time.h"

volatile State_t state;

unsigned char key;
unsigned int adc_val;
unsigned char speed;
char speed_str[3];

unsigned char sec;
unsigned char min;
unsigned char hour;

char time[9];

unsigned char event_pos = 0;

/* Password */
char password[5] = "1010";
char entered_pwd[5];

unsigned char pwd_index = 0;
unsigned char attempts = 3;

unsigned char menu_pos = 0;

char *event[] =
{
    "ON",
    "GN",
    "G1",
    "G2",
    "G3",
    "G4",
    "G5",
    "GR",
    "C "
};

void get_time(void)
{
    sec  = read_ds1307(SEC_ADDR);
    min  = read_ds1307(MIN_ADDR);
    hour = read_ds1307(HOUR_ADDR);

    sec &= 0x7F;

    time[0] = ((hour >> 4) & 0x03) + '0';
    time[1] = (hour & 0x0F) + '0';

    time[2] = ':';

    time[3] = ((min >> 4) & 0x0F) + '0';
    time[4] = (min & 0x0F) + '0';

    time[5] = ':';

    time[6] = ((sec >> 4) & 0x0F) + '0';
    time[7] = (sec & 0x0F) + '0';

    time[8] = '\0';
}

unsigned char check_password(void)
{
    unsigned char i;

    for(i = 0; i < 4; i++)
    {
        if(password[i] != entered_pwd[i])
        {
            return 0;
        }
    }

    return 1;
}

void init_config(void)
{
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_i2c();
    init_ds1307();
    init_uart();

    state = DASHBOARD;
}

void display_dashboard(void)
{
    adc_val = read_adc();

    speed = (adc_val * 99UL) / 1023;

    speed_str[0] = (speed / 10) + '0';
    speed_str[1] = (speed % 10) + '0';
    speed_str[2] = '\0';

    get_time();

    clcd_print("TIME     EVT SP", LINE1(0));

    clcd_print(time, LINE2(0));

    clcd_print(event[event_pos], LINE2(9));

    clcd_print(speed_str, LINE2(13));
}

void display_login(void)
{
    clcd_print("ENTER PASSWORD", LINE1(0));

    if(key == SW4 && pwd_index < 4)
    {
        entered_pwd[pwd_index] = '1';

        clcd_putch('*', LINE2(6 + pwd_index));

        pwd_index++;
    }
    else if(key == SW5 && pwd_index < 4)
    {
        entered_pwd[pwd_index] = '0';

        clcd_putch('*', LINE2(6 + pwd_index));

        pwd_index++;
    }

    if(pwd_index == 4)
    {
        entered_pwd[4] = '\0';

        if(check_password())
        {
            clear_screen();

            state = MENU;

            pwd_index = 0;

            attempts = 3;
        }
        else
        {
            attempts--;

            clear_screen();

            clcd_print("WRONG PASSWORD", LINE1(0));

            __delay_ms(1000);

            clear_screen();

            pwd_index = 0;

            if(attempts == 0)
            {
                attempts = 3;

                state = DASHBOARD;
            }
        }
    }
}

void display_menu(void)
{
    if(menu_pos == 0)
    {
        clcd_print("> View Log", LINE1(0));
        clcd_print("  Clear Log", LINE2(0));
    }
    else if(menu_pos == 1)
    {
        clcd_print("> Clear Log", LINE1(0));
        clcd_print("  Download Log", LINE2(0));
    }
    else if(menu_pos == 2)
    {
        clcd_print("> Download Log", LINE1(0));
        clcd_print("  Set Time", LINE2(0));
    }
    else
    {
        clcd_print("> Set Time", LINE1(0));
    }

    if(key == SW2)
    {
        if(menu_pos < 3)
        {
            menu_pos++;
        }
    }

    if(key == SW3)
    {
        if(menu_pos > 0)
        {
            menu_pos--;
        }
    }
}

void main(void)
{
    init_config();
    
    puts_uart("\r\nSYSTEM STARTED\r\n");
    
    while(1)
    {
        key = read_switches();

        if(state == DASHBOARD)
        {
            if(key == SW2)
            {
                if(event_pos < 7)
                {
                    event_pos++;
                    log_event();
                }
            }

            if(key == SW3)
            {
                if(event_pos > 1)
                {
                    event_pos--;
                    log_event();
                }
            }

            if(key == SW1)
            {
                event_pos = 8;
                log_event();
            }
        }

        switch(state)
        {
            case DASHBOARD:

                display_dashboard();

                if(key == SW4 || key == SW5)
                {
                    clear_screen();

                    pwd_index = 0;

                    state = LOGIN;
                }

                break;

            case LOGIN:

                display_login();

                break;

            case MENU:

                display_menu();

                if(key == SW4)
                {
                    if(menu_pos == 0)
                    {
                        clear_screen();
                        state = VIEW_LOG;
                    }
                    else if(menu_pos == 1)
                    {
                        clear_screen();
                        state = CLEAR_LOG;
                    }
                    else if(menu_pos == 2)
                    {
                        clear_screen();
                        state = DOWNLOAD_LOG;
                    }
                    else if(menu_pos == 3)
                    {
                        clear_screen();
                        state = SET_TIME;
                    }
                }

                if(key == SW5)
                {
                    clear_screen();
                    state = DASHBOARD;
                }

                break;

            case VIEW_LOG:

                view_log();

                if(key == SW5)
                {
                    clear_screen();
                    state = MENU;
                }

                break;

            case CLEAR_LOG:

                clear_log();

                if(key == SW4)
                {
                    clear_all_logs();

                    clear_screen();

                    state = CLEAR_SUCCESS;
                }

                if(key == SW5)
                {
                    clear_screen();

                    state = MENU;
                }

                break;

            case DOWNLOAD_LOG:

                clcd_print("DOWNLOADING...", LINE1(0));

                download_log();

                __delay_ms(1000);

                clear_screen();

                state = MENU;

                break;

            case CLEAR_SUCCESS:

                clcd_print("LOGS CLEARED", LINE1(0));

                __delay_ms(1000);

                clear_screen();

                state = MENU;

                break;
                
            case SET_TIME:
                
                set_time();
                
                if(key == SW5)
                
                {
                    clear_screen();
                    state = MENU;
                }
                
                break;
        }
    }
}