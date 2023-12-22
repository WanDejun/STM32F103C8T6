#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "TIM.h"
#include "LED.h"

uint16_t Key_Num;
extern struct MPU6050_DataTypeDef MPU6050_Data;

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	MPU6050_Init();
	TIM_Init();
	LED_Init();
}

void WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT) {
	uint32_t Timeout = 10000;
	while (I2C_CheckEvent (I2Cx, I2C_EVENT) == ERROR) { //等待模式选择标志位
		Timeout--;
		if (Timeout == 0) {
			return;
		}
	}
}

void Send(void) {
	I2C_GenerateSTART(I2C2, ENABLE); // 生成start, 非阻塞式函数
	WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT); //等待标志位
	
	I2C_Send7bitAddress(I2C2, 0x10, I2C_Direction_Transmitter); // 从机地址 0x0F
	WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, 0x41); //发送0x41
	WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING); //等待标志位,数据从寄存器转移到输出移位寄存器
	
	I2C_GenerateSTOP(I2C2, ENABLE);
}

int main(void) {
	Init();
	
	while (1) {
		
	}
}
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)) {
		//Send();
		LED_Flip(GPIO_Pin_6);
		static uint8_t num = 0x00;
		num++;
		MPU6050_WriteReg(num, 0x41);
		LED_Flip(GPIO_Pin_6);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
