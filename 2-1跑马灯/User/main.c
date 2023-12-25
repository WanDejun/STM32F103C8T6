#include "stm32f10x.h"                  /* Device header */


void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //自己定义
      while(i--) ;    
   }
}

int main(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_Write(GPIOA, ~0);
	
	int GPIO_INFO = 0;
	while (1) {
		int i;
		GPIO_INFO = 1;
		for (i = 0; i < 10; i++) {
			GPIO_Write(GPIOA, ~GPIO_INFO);
			delay_ms(100);
			GPIO_INFO <<= 1;
		}
	}
}
 
