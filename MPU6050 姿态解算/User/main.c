#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "math.h"
#include "TIM4.h"

uint16_t Key_Num;
extern struct MPU6050_DataTypeDef MPU6050_Data;

#define PI (acos(-1))

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	MPU6050_Init();
	//TIM4_Init();
}

int main(void) {
	Init();
	
	uint8_t ID = MPU6050_ReadReg(0x75);
	OLED_ShowString(0, 0, "ID: ", 8);
	OLED_ShowHexNum(40, 0, ID, 2, 8);
	OLED_Update();
	
	while (1) {
		MPU6050_Gyro_Attitude_Cal(86);
		OLED_ShowSignedNum(0, 16, MPU6050_Data.GyroX * 10000, 5, 8);
		OLED_ShowSignedNum(0, 32, MPU6050_Data.GyroY * 10000, 5, 8);
		OLED_ShowSignedNum(0, 48, MPU6050_Data.GyroZ * 10000, 5, 8);

		OLED_ShowSignedNum(64, 16 ,roll * 100, 5, 8);
		OLED_ShowSignedNum(64, 32 ,pitch * 100, 5, 8);
		OLED_ShowSignedNum(64, 48 ,yaw * 100, 5, 8);
		
		OLED_Update();
		Delay_ms(10);
	}
}
 
