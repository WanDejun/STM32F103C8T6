#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "stdio.h"
#include "TIM.h"

const uint16_t Array_Size = 4;
uint8_t Array[Array_Size] = {'a', 'b', 'c', 'd'};
uint8_t T_data;

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	Serial_Init();
	TIM_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "Num0:");
	OLED_ShowString(2, 1, "Num1:");
	OLED_ShowString(3, 1, "Num2:");
	OLED_ShowString(4, 1, "Num3:");
	
	while (1) {
		OLED_ShowHexNum(1, 6, Serial_ReceiveDatas[0], 2);
		OLED_ShowHexNum(2, 6, Serial_ReceiveDatas[1], 2);
		OLED_ShowHexNum(3, 6, Serial_ReceiveDatas[2], 2);
		OLED_ShowHexNum(4, 6, Serial_ReceiveDatas[3], 2);
		OLED_ShowHexNum(1, 12, (uint8_t)USART_GetFlagStatus(USART1, USART_FLAG_RXNE), 4);
	}
}
