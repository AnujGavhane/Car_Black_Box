#include <xc.h>
#include "i2c.h"

void init_i2c(void)
{
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPADD = 49;      // 100kHz @20MHz
    SSPSTAT = 0x00;

    TRISC3 = 1;
    TRISC4 = 1;
}

void i2c_start(void)
{
    SEN = 1;
    while(SEN);
}

void i2c_rep_start(void)
{
    RSEN = 1;
    while(RSEN);
}

void i2c_stop(void)
{
    PEN = 1;
    while(PEN);
}

void i2c_write(unsigned char data)
{
    SSPBUF = data;

    while(BF);
    while(SSPIF == 0);

    SSPIF = 0;
}

unsigned char i2c_read(unsigned char ack)
{
    RCEN = 1;

    while(!BF);

    unsigned char data = SSPBUF;

    ACKDT = ack;
    ACKEN = 1;

    while(ACKEN);

    return data;
}
