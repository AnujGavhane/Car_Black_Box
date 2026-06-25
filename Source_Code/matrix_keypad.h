/* 
 * File:   matrix_keypad.h
 * Author: Anuj
 * Project: car_black_box
 */

#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

#define ALL_RELEASED    0xFF

#define SW1             1
#define SW2             2
#define SW3             3
#define SW4             4
#define SW5             5

void init_matrix_keypad(void);

unsigned char read_switches(void);

#endif