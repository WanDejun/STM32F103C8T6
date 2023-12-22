#ifndef __MYDMA_H
#define __MYDMA_H
#include "stm32f10x.h"                  // Device header

void MyDMA_Init(uint32_t Addr_A, uint32_t Addr_B, uint16_t size);
void MyDMA_Transfer();

#endif