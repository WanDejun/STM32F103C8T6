#ifndef __SERIAL_H
#define __SERIAL_H
#include "stm32f10x.h"                  // Device header

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendString(char *str);
uint8_t Serial_GetRxFlag(void);
void Serial_SendPacket(char *str);

#endif
