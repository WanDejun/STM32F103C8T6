#ifndef __MPU6050_H
#define __MPU6050_H
#include "stm32f10x.h"                  // Device header

struct MPU6050_DataTypeDef{
	double 	AccX, 	AccY, 	AccZ;
	double 	GyroX, 	GyroY, 	GyroZ;
}; 
extern double roll, pitch, yaw;
extern struct MPU6050_DataTypeDef MPU6050_Data;

void MPU6050_Init(void);
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddredd);
void MPU6050_GetData(void);
void MPU6050_Gyro_Attitude_Cal(uint16_t Freq);

#endif
