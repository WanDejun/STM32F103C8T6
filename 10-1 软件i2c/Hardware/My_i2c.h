#ifndef __MY_I2C_H
#define __MY_I2C_H
#include "stm32f10x.h"                  // Device header

void My_i2c_Init(void);
void My_i2c_Start(void);
void My_i2c_Stop(void);
void My_i2c_SendByte(uint8_t Byte);
uint8_t My_i2c_ReceiveByte(void);
void My_i2c_SendAck(uint8_t AckByte);
uint8_t My_i2c_ReceiveAck(void);

#endif
