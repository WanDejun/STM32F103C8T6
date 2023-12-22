#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"                  // Device header

void Timer_Init(void);
uint16_t TimerGetCnt(void);

#endif