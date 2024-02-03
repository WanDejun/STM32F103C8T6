#ifndef __74HC595_H
#define __74HC595_H
#include "stm32f10x.h"                  // Device header

void _74HC595_Init(void);
void _74HC595_Write(uint8_t Byte);

#endif
