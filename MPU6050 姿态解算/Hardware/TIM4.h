#ifndef __TIM4_H
#define __TIM4_H
#include "stm32f10x.h"                  // Device header

void TIM4_Init(void);

void TIM4_SetTime(uint16_t time);
uint16_t TIM4_GetTime(void);

void TIM4_Start(void);
void TIM4_Stop(void);

#endif
