#include "stm32f10x.h"                  // Device header
#include "Menu.h"
#include "OLED.h"
#include "Delay.h"
#include "string.h"

extern uint8_t OLED_DisplayBuf[][128];

PageInfo_t PageInfoList[5];

uint8_t MenuItemCnt; //选项词条数量
uint8_t MenuItemIndex; //当前选中的词条的索引
uint8_t MenuBoxPosition; //选项框在屏幕上的位置 0-3
uint8_t MenuItemLength[12]; // 词条的长度
PageName_t MenuPageName;

void OLED_MenuInit(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) == SET) {
		uint8_t i, j;
		for (i = 0; i < 128; i++) for (j = 0; j < 128; j++);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == Bit_RESET) {
			PageInfoList[MenuPageName].route[MenuItemIndex]();
		}
		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void TestPageName(PageName_t PageName) {
	if ((uint8_t)PageName >= 5) {
		while (1); // PageName ERROR!
	}
}

void OLED_MenuLoad(PageName_t PageName) {
	TestPageName(PageName);
	
	uint8_t i, j, k; 
	
	for (i = 0; i < 24; i++) {
		for (j = 0; j < 128; j++) { //清空显数据
			OLED_DisplayBuf[i][j] = 0;
		}
	}
	
	MenuItemCnt = 0; // 加载显存数据
	for (k = 0; k < PageInfoList[PageName].PageItemCnt; k++) {
		for (i = 0; PageInfoList[PageName].PageItemList[k][i] != '\0'; i++) {
			for (j = 0; j < 8; j++) {
				OLED_DisplayBuf[MenuItemCnt << 1][i << 3 | j] = OLED_F8x16[PageInfoList[PageName].PageItemList[k][i] - ' '][j];
				OLED_DisplayBuf[MenuItemCnt << 1 | 1][i << 3 | j] = OLED_F8x16[PageInfoList[PageName].PageItemList[k][i] - ' '][j | 0x08];
			}
		}
		MenuItemLength[MenuItemCnt] = i << 3;
		MenuItemCnt++;
	}
	
	MenuPageName = PageName; // 初始化显示控制
	MenuItemIndex = 0;
	MenuBoxPosition = 0;
	OLED_ReverseArea(0, 0, MenuItemLength[0], 16);
	OLED_Update();
}

void OLED_MenuAdd(PageName_t PageName, char* str, void (*route)(void)) {
	TestPageName(PageName);
	
	strcpy(PageInfoList[PageName].PageItemList[PageInfoList[PageName].PageItemCnt], str);
	PageInfoList[PageName].route[PageInfoList[PageName].PageItemCnt] = route;
	PageInfoList[PageName].PageItemCnt++;
}

void OLED_MenuClear(PageName_t PageName) {
	TestPageName(PageName);
	
	PageInfoList[PageName].PageItemCnt = 0;
}

void OLED_MenuUpRoll_1Px(void) {
	uint8_t temp, i, j;
	for (i = 0; i < 128; i++) {
		temp = OLED_DisplayBuf[0][i] & 1;
		OLED_DisplayBuf[0][i] >>= 1;
		for (j = 1; j < MenuItemCnt << 1; j++) {
			OLED_DisplayBuf[j - 1][i] |= (OLED_DisplayBuf[j][i] & 1) << 7;
			OLED_DisplayBuf[j][i] >>= 1;
		}
		OLED_DisplayBuf[j - 1][i] |= temp << 7;
	}
}

void OLED_MenuDownRoll_1Px(void) {
	int16_t temp, i, j;
	for (i = 0; i < 128; i++) {
		temp = OLED_DisplayBuf[(MenuItemCnt << 1) - 1][i] >> 7;
		OLED_DisplayBuf[(MenuItemCnt << 1) - 1][i] <<= 1;
		
		for (j = (MenuItemCnt << 1) - 2; j >= 0; j--) {
			OLED_DisplayBuf[j + 1][i] |= OLED_DisplayBuf[j][i] >> 7;
			OLED_DisplayBuf[j][i] <<= 1;
		}
		OLED_DisplayBuf[0][i] |= temp;
	}
}

void OLED_MenuSelectDown(void) {
	uint8_t i;
	if (MenuItemIndex == MenuItemCnt - 1) return;
	else if (MenuBoxPosition == 3) {
		float dx = (MenuItemLength[MenuItemIndex + 1] - MenuItemLength[MenuItemIndex]) / 8 + 1e-2;
		float xSize = MenuItemLength[MenuItemIndex];
		for (i = 0; i < 8; i++) {
			OLED_ReverseArea(0, 48, xSize, 16);
			OLED_MenuUpRoll_1Px();
			OLED_MenuUpRoll_1Px();
			
			xSize += dx;
			OLED_ReverseArea(0, 48, xSize, 16);
			OLED_Update();
			Delay_ms(10);
		}
	}
	else {
		float dx = (MenuItemLength[MenuItemIndex + 1] - MenuItemLength[MenuItemIndex]) / 8 + 1e-2;
		float xSize = MenuItemLength[MenuItemIndex];
		uint8_t y = MenuBoxPosition << 4, dy = 2;
		for (i = 0; i < 8; i++) {
			OLED_ReverseArea(0, y, xSize, 16);
			
			xSize += dx;
			y += dy;
			OLED_ReverseArea(0, y, xSize, 16);
			OLED_Update();
			
			Delay_ms(10);
		}
		MenuBoxPosition++;
	}
	MenuItemIndex++;
}

void OLED_MenuSelectUp(void) {
	uint8_t i;
	if (MenuItemIndex == 0) return;
	else if (MenuBoxPosition == 0) {
		float dx = (MenuItemLength[MenuItemIndex - 1] - MenuItemLength[MenuItemIndex]) / 8 + 1e-2;
		float xSize = MenuItemLength[MenuItemIndex];
		for (i = 0; i < 8; i++) {
			OLED_ReverseArea(0, 0, xSize, 16);
			OLED_MenuDownRoll_1Px();
			OLED_MenuDownRoll_1Px();
			
			xSize += dx;
			OLED_ReverseArea(0, 0, xSize, 16);
			OLED_Update();
			
			Delay_ms(10);
		}
	}
	else {
		float dx = (MenuItemLength[MenuItemIndex - 1] - MenuItemLength[MenuItemIndex]) / 8 + 1e-2;
		float xSize = MenuItemLength[MenuItemIndex];
		uint8_t y = MenuBoxPosition << 4, dy = 2;
		for (i = 0; i < 8; i++) {
			OLED_ReverseArea(0, y, xSize, 16);
			
			xSize += dx;
			y -= dy;
			OLED_ReverseArea(0, y, xSize, 16);
			OLED_Update();
			
			Delay_ms(10);
		}
		MenuBoxPosition--;
	}
	MenuItemIndex--;
}
