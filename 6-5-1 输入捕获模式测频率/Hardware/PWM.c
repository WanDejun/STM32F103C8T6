#include "pwm.h"
#include "stm32f10x.h"                  // Device header


void PWM_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, & GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1; //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1; //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = ENABLE;
	TIM_OCInitStructure.TIM_Pulse = 99; //CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare1(uint16_t Compare) {
	TIM_SetCompare1(TIM2, Compare);
}

void PWM_SetPrescaler(uint16_t Prescaler) {
	TIM_PrescalerConfig(TIM2, Prescaler, TIM_PSCReloadMode_Update);
}
