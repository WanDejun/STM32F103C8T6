#ifndef __SERIAL_H
#define __SERIAL_H
#include "stm32f10x.h"                  // Device header

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t* Byte, uint16_t size);
void Serial_SendString(const char* str);
void Serial_SendNum(uint32_t Num, uint8_t Length);
void Serial_Printf(const char* Format, ...);

#endif
