#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "ADC.h"
#include "MyTIM.h"
// #include "math.h"

// #define pi acos(-1)

int main(void) {
	OLED_Init();
	ADC1_Init();
	MyTIM_Init();
//	uint16_t i = 0;
	OLED_ShowString(0, 48, "Brightness:", 8);
	
	while (1) {
		/*正弦波绘制************************/
//		double i;
//		for (i = 0; i < 2 * pi; i += 0.1) {
//			OLED_RollAddDate(24 - sin(i) * 23);
//			OLED_RollUpdate();
//			Delay_ms(2);
//		}
		/***********************************/
		
		/*读取外部电压**********************/
		OLED_RollAddDate((ReadAnalogValue() * 47) >> 12);
		OLED_ShowNum(88, 48, 48 - ((ReadAnalogValue() * 47) >> 12), 2, 8);
		OLED_RollUpdate();
		Delay_ms(5);
		/***********************************/
		
		/*测试帧率**************************/
//		OLED_ShowNum(88, 48, i, 5, 8);
//		OLED_RollUpdate();
//		i++;
		/***********************************/
	}
}
