#ifndef __MPU6050_H
#define __MPU6050_H
#include "stm32f10x.h"                  // Device header

struct MPU6050_DataTypeDef{
	int16_t AccX, AccY, AccZ;
	int16_t GyroX, GyroY, GyroZ;
}; 
extern struct MPU6050_DataTypeDef MPU6050_Data;

void i2c_Init(void);
void i2c_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t i2c_ReadReg(void);

#endif
