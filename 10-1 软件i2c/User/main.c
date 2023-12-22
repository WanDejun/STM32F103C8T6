#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

uint16_t Key_Num;
extern struct MPU6050_DataTypeDef MPU6050_Data;

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
	MPU6050_Init();
}

int main(void) {
	Init();
	
	uint8_t ID = MPU6050_ReadReg(0x75);
	OLED_ShowString(1, 1, "ID: ");
	OLED_ShowHexNum(1, 5, ID, 2);
	
	while (1) {
		MPU6050_GetData();
		OLED_ShowSignedNum(2, 1, MPU6050_Data.AccX, 5);
		OLED_ShowSignedNum(3, 1, MPU6050_Data.AccY, 5);
		OLED_ShowSignedNum(4, 1, MPU6050_Data.AccZ, 5);
				 
		OLED_ShowSignedNum(2, 8, MPU6050_Data.GyroX, 5);
		OLED_ShowSignedNum(3, 8, MPU6050_Data.GyroY, 5);
		OLED_ShowSignedNum(4, 8, MPU6050_Data.GyroZ, 5);
		
		Delay_ms(5);
	}
}
 
