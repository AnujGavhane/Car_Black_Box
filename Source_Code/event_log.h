/* 
 * File:   event_log.h
 * Author: Anuj
 */

#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#include "eeprom.h"

extern unsigned char log_pos;

void log_event(void);
void write_log_eeprom(void);

#endif