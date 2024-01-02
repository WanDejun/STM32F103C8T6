#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "LightSenser.h"

uint16_t Key_Num;

static void Init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断分组
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	OLED_Init();
	LightSenser_Init();
}

int main(void) {
	Init();
	
	while (1) {
		OLED_ShowNum(2, 1, LightSenserGetCnt(), 5);
		
		OLED_ShowString(1, 1, "Runing");
		Delay_ms(100);
		OLED_ShowString(1, 1, "      ");
		Delay_ms(100);
		
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		SystemInit();
	}
}
 
