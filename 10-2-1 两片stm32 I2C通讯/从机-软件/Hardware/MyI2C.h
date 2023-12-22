#ifndef __MYI2C_H
#define __MYI2C_H
#include "stm32f10x.h"                  // Device header

void MyI2C_Init(void);
extern uint8_t Rx_Data[8], Address;

#endif
