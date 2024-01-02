#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void PWM_Init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 2000  - 1; //周期为20ms, 分辨率为 1/2000 即 0.01ms
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStruture;
	TIM_OCStructInit(&TIM_OCInitStruture);   
	TIM_OCInitStruture.TIM_OCMode = TIM_OCMode_PWM1; //比较模式
	TIM_OCInitStruture.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性
	TIM_OCInitStruture.TIM_OutputState = ENABLE; //输出使能
	TIM_OCInitStruture.TIM_Pulse = 0; //CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStruture);
	
	TIM_Cmd(TIM2, ENABLE);
}

void PWN_SetCompare1(uint16_t Compare) {
	TIM_SetCompare1(TIM2, Compare); //设置CCR值
}
