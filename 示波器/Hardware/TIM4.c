#include "stm32f10x.h"                  // Device header
#include "TIM4.h"
#include "AD.h"

void TIM4_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_InternalClockConfig(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 36000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 2000 - 1; 
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM4_SetTime(uint16_t time) { // 单位ms
	TIM_PrescalerConfig(TIM4, time << 1, TIM_PSCReloadMode_Update);
}

uint16_t TIM4_GetTime(void) {
	return TIM_GetPrescaler(TIM4) >> 1;
}

void TIM4_Start() {
	TIM_SetCounter(TIM4, 0);
	TIM_Cmd(TIM4, ENABLE);
}

void TIM4_Stop() {
	TIM_Cmd(TIM4, DISABLE);
}

void TIM4_IRQHandler(void) {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) {
		DMA_Cmd(DMA1_Channel1, DISABLE);
		DMA_SetCurrDataCounter(DMA1_Channel1, 128);
		DMA_Cmd(DMA1_Channel1, ENABLE);
		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
