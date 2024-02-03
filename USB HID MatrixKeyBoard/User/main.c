#include "hw_config.h"
#include "LED.h"

__IO uint8_t PrevXferComplete = 1; //用于标志是否需要采集数据, 1为需要. 0为不需要

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void) {
	Set_System(); // GPIO初始化

	USB_Interrupts_Config(); // USB中断配置

	Set_USBClock(); // USB时钟配置

	USB_Init(); // USB 外设初始化
	
	LED_Init(); // LED初始化
  
	while (1) {
		if (bDeviceState == CONFIGURED) {
			if ((KeyState() != 0) && (PrevXferComplete)) { //获取按键事件
				KeyBoard_Send(); // 发送按键信息
			}
		}
	}
}
