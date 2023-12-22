#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "My_i2c.h"
#include "MPU6050_reg.h"

#define MPU6050_ADDRESS 0xD0

struct MPU6050_DataTypeDef MPU6050_Data;

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data) {
	My_i2c_Start();
	
	My_i2c_SendByte(MPU6050_ADDRESS);
	if (My_i2c_ReceiveAck()) { My_i2c_Stop(); return; }
	
	My_i2c_SendByte(RegAddress);
	My_i2c_ReceiveAck();
	
	My_i2c_SendByte(Data);
	My_i2c_ReceiveAck();
	
	My_i2c_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddredd) {
	uint8_t Data;
	My_i2c_Start();
	
	My_i2c_SendByte(MPU6050_ADDRESS);
	if (My_i2c_ReceiveAck()) { My_i2c_Stop(); return 0x0; }	
	
	My_i2c_SendByte(RegAddredd);
	My_i2c_ReceiveAck();
	
	My_i2c_Start();
	
	My_i2c_SendByte(MPU6050_ADDRESS | 0x01);
	My_i2c_ReceiveAck();
	
	Data = My_i2c_ReceiveByte();
	My_i2c_SendAck(1);
	
	My_i2c_Stop();
	return Data;
}

void MPU6050_Init(void) {
	My_i2c_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

void MPU6050_GetData(void) {
	int16_t DataH, DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	MPU6050_Data.AccX = DataH << 8 | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	MPU6050_Data.AccY = DataH << 8 | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	MPU6050_Data.AccZ = DataH << 8 | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	MPU6050_Data.GyroX = DataH << 8 | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	MPU6050_Data.GyroY = DataH << 8 | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	MPU6050_Data.GyroZ= DataH << 8 | DataL;
}
