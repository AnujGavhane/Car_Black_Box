/* 
 * File:   uart.h
 * Author: Anuj
 */

#ifndef UART_H
#define UART_H

void init_uart(void);
void putch(unsigned char data);
void puts_uart(const char *str);

#endif
