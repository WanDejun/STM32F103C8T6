#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "Delay.h"
#include "MySPI.h"
#include "TIM.h"

uint8_t Array[13] = {72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 33, 0};

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	OLED_Init();
	MySPI_Init();
	TIM_Init();
}

int main(void) {
	Init();

	while (1) {
		OLED_ShowString(1, 1, (char *)Array);
	}
}
 void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)) {
		MySPI_Start();
		MySPI_SwapArray(Array, 13);
		MySPI_Stop();
		//OLED_ShowChar(2, 1, '#');
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

