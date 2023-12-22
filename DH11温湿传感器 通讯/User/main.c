#include "stm32f10x.h"                  /* Device header */
#include "Delay.h"
#include "OLED.h"
#include "DHT11.h"

uint16_t Key_Num;
extern unsigned int rec_data[4];

static void Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	OLED_Init();
}

int main(void) {
	Init();
	
	OLED_ShowString(1, 1, "T:  .");
	OLED_ShowString(2, 1, "H:  .");
	
	while (1) {
		Delay_s(1);
		DHT11_REC_Data(); //接收温度和湿度的数据
		
	    OLED_ShowNum(1,3,rec_data[2],2);
		OLED_ShowNum(1,6,rec_data[3],1);
		OLED_ShowNum(2,3,rec_data[0],2);
		OLED_ShowNum(2,6,rec_data[1],2);
	}
}
 
