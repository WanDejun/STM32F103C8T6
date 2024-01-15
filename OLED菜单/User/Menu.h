#ifndef __MENU_H
#define __MEMU_H
#include "stm32f10x.h"                  // Device header

typedef enum { Home, SubPage1, SubPage2, SubPage3, SubPage1_SubPage1 } PageName_t;

typedef struct {
	uint16_t i_val1;
} param_t;

typedef struct {
	uint8_t PageItemCnt;
	char PageItemList[12][17];
	void (*(route[12]))(void);
} PageInfo_t;

void OLED_MenuInit(void);
void OLED_MenuAdd(PageName_t PageName, char* str, void (*route)(void));
void OLED_MenuLoad(PageName_t PageName);
void OLED_MenuClear(PageName_t PageName);
void OLED_MenuDownRoll_1Px(void);
void OLED_MenuUpRoll_1Px(void);
void OLED_MenuSelectDown(void);
void OLED_MenuSelectUp(void);

#endif
