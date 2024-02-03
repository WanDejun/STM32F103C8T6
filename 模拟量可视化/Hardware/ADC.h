#ifndef __ADC_H
#define __ADC_H
#include "stm32f10x.h"                  // Device header

void ADC1_Init(void);
uint16_t ReadAnalogValue(void);

#endif
