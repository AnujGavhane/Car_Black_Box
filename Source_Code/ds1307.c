#include "ds1307.h"
#include "i2c.h"

void write_ds1307(unsigned char addr, unsigned char data)
{
    i2c_start();

    i2c_write(DS1307_WRITE);
    i2c_write(addr);
    i2c_write(data);

    i2c_stop();
}

unsigned char read_ds1307(unsigned char addr)
{
    unsigned char data;

    i2c_start();

    i2c_write(DS1307_WRITE);
    i2c_write(addr);

    i2c_rep_start();

    i2c_write(DS1307_READ);

    data = i2c_read(1);

    i2c_stop();

    return data;
}

void init_ds1307(void)
{
    write_ds1307(SEC_ADDR,0x00);
    write_ds1307(MIN_ADDR,0x35);
    write_ds1307(HOUR_ADDR,0x12);
}
