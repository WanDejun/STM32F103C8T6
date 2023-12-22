#include "stm32f10x.h"                  // Device header
#include "IC.h"

void IC_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65535 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //捕获通道编号
	TIM_ICInitStructure.TIM_ICFilter = 0x02; //滤波
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //边沿检测
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //输入信号分频
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //捕获的输入通道,直连
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3, ENABLE);
}

uint32_t IC_GetFreq(void) {
	return 1000000 / (TIM_GetCapture1(TIM3) + 1);
}

uint32_t IC_GetDuty(void) {
	return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);
}
