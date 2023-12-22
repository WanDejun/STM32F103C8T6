#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"                  // Device header

void LED_Init(void);
void LED_set(uint8_t Pin, BitAction Action);
void LED_Flip(uint8_t Pin);

#endif