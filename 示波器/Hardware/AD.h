#ifndef __AD_H
#define __AD_H
#include "stm32f10x.h"                  // Device header

extern uint16_t AD_Value[128];
void AD_Init(void);

void AD_SetIntervalTime(uint16_t time);
uint16_t AD_GetIntervalTime(void);
void AD_TimingTriggerStart(void);
void AD_TimingTriggerStop(void);

void AD_AutoTrigger(void);
uint8_t AD_GetFinishFlag(void);

#endif
