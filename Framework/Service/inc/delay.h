#ifndef DELAY_H
#define DELAY_H
#include "stm32f4xx.h"

extern void delay_init(uint32_t TICK_RATE_HZ);
extern void Delay_us(uint16_t nus);
extern void Delay_ms(uint16_t nms);
int get_tick_count(unsigned long *count);
#endif

