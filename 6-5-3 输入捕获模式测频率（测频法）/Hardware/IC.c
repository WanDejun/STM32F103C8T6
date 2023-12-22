#include "stm32f10x.h"                  // Device header
#include "IC.h"

static FreqCnt;

void IC_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_Inverted, 0x02); //时钟信号源，输入滤波
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; //TIM2通道检测输入上升沿个数
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65535 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1; //1预分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM4);
	
	//TIM4通道定时0.1s
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4, ENABLE);
}

uint32_t IC_GetFreq(void) {
	return (FreqCnt) * 10;
}

void TIM4_IRQHandler(void) {
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) {
		FreqCnt = TIM_GetCounter(TIM2);
		TIM_SetCounter(TIM2, 0);
		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}
