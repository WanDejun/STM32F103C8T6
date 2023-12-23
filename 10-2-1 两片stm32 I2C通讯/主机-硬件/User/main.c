#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "i2c.h"
#include "TIM.h"
#include "LED.h"

uint8_t Num;
extern struct MPU6050_DataTypeDef MPU6050_Data;

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	i2c_Init();
	TIM_Init();
	LED_Init();
}

int main(void) {
	Init();
	
	while (1) {
		
	}
}
void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)) {
		//Send();
		Num = i2c_ReadReg();
		if (Num == 0x21) LED_set(GPIO_Pin_8, Bit_RESET);
//		static uint8_t num = 0x00;
//		num++;
//		MPU6050_WriteReg(num, 0x41);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
