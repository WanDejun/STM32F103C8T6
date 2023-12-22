#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void PWM_Init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //TIM2_OC1重定义
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100  - 1; //PCR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1; //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStruture;
	TIM_OCStructInit(&TIM_OCInitStruture);   
	TIM_OCInitStruture.TIM_OCMode = TIM_OCMode_PWM2; //比较模式 CCMR
	TIM_OCInitStruture.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性 CCER
	TIM_OCInitStruture.TIM_OutputState = ENABLE; //输出使能
	TIM_OCInitStruture.TIM_Pulse = 0; //CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStruture);
	
	TIM_Cmd(TIM2, ENABLE);
}

void PWN_SetCompare1(uint16_t Compare) {
	TIM_SetCompare1(TIM2, Compare);
}
