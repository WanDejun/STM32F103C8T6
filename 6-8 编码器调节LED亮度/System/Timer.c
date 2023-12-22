#include "Timer.h"
#include "stm32f10x.h"                  // Device header

int16_t light;
const uint16_t MAX_LIGHT = 100;

void Timer_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_InternalClockConfig(TIM4); //时钟信号源
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //输入滤波器的采样倍率
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //计数方式
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1; //自动重装器的默认值(计数器的上限)
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1; //PSC预分频器的值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; //重复计数器的值
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	//TIM_TimeBaseInit时会默认执行一次TIM_FLAG_Update中断来写入新数据，这样会导致中断函数被执行了一次
	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //设置中断信号，将TIM4拨到TIM_IT_Update上
	
	NVIC_InitTypeDef NVIC_InitStruct; //设置中断，NVIC就是叫号器
	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM4, ENABLE); //开启TIM4计时器
	
	light = 50;
}

void TIM4_IRQHandler(void) { //TIM2中断函数
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET) {
		light += ((int16_t)TIM_GetCounter(TIM3));
		light = (light > MAX_LIGHT) ? MAX_LIGHT : light;
		light = (light < 0) ? 0 : light;
		
		TIM_SetCompare1(TIM2, light);
		TIM_SetCounter(TIM3, 0);
		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

uint16_t GetLight(void) {
	return light;
}
