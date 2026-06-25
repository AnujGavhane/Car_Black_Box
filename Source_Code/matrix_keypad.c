#include <xc.h>
#include "matrix_keypad.h"

void init_matrix_keypad(void)
{
    TRISB = 0x1F;      // RB0-RB4 inputs
    OPTION_REGbits.nRBPU = 0;
}

unsigned char read_switches(void)
{
    if(RB2 == 0)
    {
        while(RB2 == 0);
        return SW1;
    }

    if(RB1 == 0)
    {
        while(RB1 == 0);
        return SW2;
    }

    if(RB0 == 0)
    {
        while(RB0 == 0);
        return SW3;
    }

    if(RB3 == 0)
    {
        while(RB3 == 0);
        return SW4;
    }

    if(RB4 == 0)
    {
        while(RB4 == 0);
        return SW5;
    }

    return ALL_RELEASED;
}