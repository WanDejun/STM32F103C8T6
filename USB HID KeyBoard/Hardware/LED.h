#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"                  // Device header

void LED_Init(void);
void LED_Set(uint16_t Pin);
void LED_Reset(uint16_t Pin);
void LED_Flip(uint16_t Pin);

#endif
