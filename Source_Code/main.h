/* 
 * File:   main.h
 * Author: Anuj
 * Project: car_black_box
 */

#ifndef MAIN_H
#define MAIN_H

#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

typedef enum
{
    DASHBOARD,
    LOGIN,
    MENU,
    VIEW_LOG,
    CLEAR_LOG,
    DOWNLOAD_LOG,
    SET_TIME,
    CLEAR_SUCCESS
} State_t;

#endif