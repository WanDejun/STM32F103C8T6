#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "MPU6050_reg.h"

#define MPU6050_ADDRESS 0xD0

struct MPU6050_DataTypeDef MPU6050_Data;

void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT) {
	uint32_t Timeout = 10000;
	while (I2C_CheckEvent (I2Cx, I2C_EVENT) == ERROR) { //等待模式选择标志位
		Timeout--;
		if (Timeout == 0) {
			return;
		}
	}
}

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data) {
	I2C_GenerateSTART(I2C2, ENABLE); // 生成start, 非阻塞式函数
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT); //等待标志位
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, RegAddress);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING); //等待标志位,数据从寄存器转移到输出移位寄存器
	
	I2C_SendData(I2C2, Data);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED); //等待标志位,寄存器空
	
	I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress) {
	uint8_t Data;

	I2C_GenerateSTART(I2C2, ENABLE); // 生成start, 库函数均为非阻塞式函数需要等待标志位来判断数据传输/接收完成
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT); //等待模式选择标志位
		
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter); //发送外设地址和写指令
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); //等待传输模式选择标志位（从机应答）
	
	I2C_SendData(I2C2, RegAddress); //写入数据地址
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED); //等待标志位,数据从寄存器转移到输出移位寄存器，数据传输完成
	
	I2C_GenerateSTART(I2C2, ENABLE); //restart状态
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT); //等待模式选择标志位
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver); ////发送外设地址和读指令
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED); //等待传输模式选择标志位（从机应答）
	I2C_AcknowledgeConfig(I2C2, DISABLE); //再开始接收最后一个数据时（不能等数据传输完），设停止应答，此时接收到下一条数据字节后主机不应答（读取模式下，应答表示继续读取下一字节）
	I2C_GenerateSTOP(I2C2, ENABLE); //设stop标志位，在等待读取完成后自动输出STOP命令
	
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED); //输入完成
	Data = I2C_ReceiveData(I2C2); //读取数据（会自动重置RXE标志位）
	
	I2C_AcknowledgeConfig(I2C2, ENABLE); //重新设回应答模式
	return Data;
}

void MPU6050_Init(void) {	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 7200;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C2, &I2C_InitStructure);
	
	I2C_Cmd(I2C2, ENABLE);
}
