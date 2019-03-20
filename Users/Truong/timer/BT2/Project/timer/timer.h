#ifndef _TIMER_H
#define _TIMER_H
#include "STM32F4xx.h"

void set_timer(u16 timer, u16 time);
void start_timer(u16 timer);
void stop_timer(u16 timer);
#endif