#include "stm32f10x.h"                  // Device header
#include "TIM.h"
#include "DHT11.h"
#include "Serial.h"

void TIM_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_InternalClockConfig(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36000;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 1;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4, ENABLE);
}

void TIM4_IRQHandler(void) {
	extern unsigned int rec_data[4];
	if (TIM_GetITStatus(TIM4, TIM_IT_Update)) {
		DHT11_REC_Data();
		Serial_Printf("%2d.%1d\n", rec_data[2], rec_data[3]);
		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
