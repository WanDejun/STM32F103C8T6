#ifndef __ASYNC_H
#define __ASYNC_H
#include "stm32f10x.h"                  // Device header
#include "VisualFunction.h"

void async_Init(void);
uint8_t async_Call(void);
void async_AddTransaction(VisualFuntion_t* vFunc, uint16_t delayTime);


#endif
