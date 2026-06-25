#include <xc.h>
#include "adc.h"

void init_adc(void)
{
    ADCON0 = 0x41;      // AN0, ADC ON
    ADCON1 = 0x80;      // Right justified
}

unsigned int read_adc(void)
{
    GO_nDONE = 1;

    while(GO_nDONE);

    return ((ADRESH << 8) | ADRESL);
}
