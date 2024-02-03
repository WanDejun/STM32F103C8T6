#include "MyTIM.h"
#include "stm32f10x.h"                  // Device header

void MyTIM_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStruture;
	TIM_OCStructInit(&TIM_OCInitStruture);
	TIM_OCInitStruture.TIM_OCMode = TIM_OCMode_PWM1; //比较模式
	TIM_OCInitStruture.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性
	TIM_OCInitStruture.TIM_OutputState = ENABLE; //输出使能
	TIM_OCInitStruture.TIM_Pulse = 500; //CCR
	TIM_OC2Init(TIM2, &TIM_OCInitStruture);
	
	TIM_Cmd(TIM2, ENABLE);
}
