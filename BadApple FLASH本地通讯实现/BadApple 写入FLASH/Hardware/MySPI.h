#ifndef __MYSPI_H
#define __MYSPI_H
#include "stm32f10x.h"                  // Device header

void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
void MySPI_SwapArray(uint8_t *Array, uint16_t ArraySize);
uint8_t MySPI_SwapByte(uint8_t Data);
#endif
