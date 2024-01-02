#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Image.h"
#include "W25Q64.h"
#include "Serial.h"

void Init(void) {
	OLED_Init();
	W25Q64_Init();
	Serial_Init();
}

int main(void) {
	Init();
	
	uint16_t i;
	
	while (1) {
		for (i = 0; i < 547; i++) {
			Image_Load(0x1000 * i); //轮播图片，形成视频，W25Q64每个Sector为4k，每张图片1k，因此选择4张图片同时操作
			Show_Image(0); //显示图片
			Delay_ms(100);
			Show_Image(1);
			Delay_ms(100);
			Show_Image(2);
			Delay_ms(100);
			Show_Image(3);
			Delay_ms(99);
		}
	}
}
