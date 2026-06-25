/* 
 * File:   ds1307.h
 * Author: Anuj
 */

#ifndef DS1307_H
#define DS1307_H

#define DS1307_WRITE 0xD0
#define DS1307_READ  0xD1

#define SEC_ADDR 0x00
#define MIN_ADDR 0x01
#define HOUR_ADDR 0x02

void init_ds1307(void);
unsigned char read_ds1307(unsigned char addr);
void write_ds1307(unsigned char addr, unsigned char data);

#endif