#include "MenuControler.h"
#include "Menu.h"
#include "LED.h"
#include "Encoder.h"
#include "stm32f10x.h"                  // Device header


/**************************************************************

 **路由/功能函数*******************
 
**************************************************************/

//空路由
static void routeNull(void) {
	;
}

//HomePage 功能
static void route_Home_SubPage1(void) {
	OLED_MenuLoad(SubPage1);
}

static void route_Home_SubPage2(void) {
	OLED_MenuLoad(SubPage2);
}

static void route_Home_SubPage3(void) {
	OLED_MenuLoad(SubPage3);
}

//SubPage1 功能
static void route_SubPage1_SubPage1(void) {
	OLED_MenuLoad(SubPage1_SubPage1);
}

static void route_SubPage1_Return(void) {
	OLED_MenuLoad(Home);
}

//SubPage2 功能
static void route_SubPage2_LED_ON(void) {
	LED_set(GPIO_Pin_2, Bit_RESET);
}

static void route_SubPage2_LED_OFF(void) {
	LED_set(GPIO_Pin_2, Bit_SET);
}

static void route_SubPage2_Return(void) {
	OLED_MenuLoad(Home);
}

//SubPage3 功能
static void route_SubPage3_Return(void) {
	OLED_MenuLoad(Home);
}


//SubPage1_SubPage1 功能
static void route_SubPage1_SubPage1_Return(void) {
	OLED_MenuLoad(SubPage1);
}

/**************************************************************

 **界面初始化*******************
 
**************************************************************/

static void HomePageInit(void) { // Home界面
	OLED_MenuAdd(Home, "Hello Menu!", routeNull);
	OLED_MenuAdd(Home, "SubPage1", route_Home_SubPage1);
	OLED_MenuAdd(Home, "LED Control", route_Home_SubPage2);
	OLED_MenuAdd(Home, "SubPage3", route_Home_SubPage3);
	OLED_MenuAdd(Home, "****************", routeNull);
	OLED_MenuAdd(Home, "Text1", routeNull);
	OLED_MenuAdd(Home, "Try Text2", routeNull);
	OLED_MenuAdd(Home, "This is a text", routeNull);
	OLED_MenuAdd(Home, "(By Mowind)", routeNull);
	OLED_MenuAdd(Home, "(end)", routeNull);
}

static void SubPage1Init(void) { // 子界面1
	OLED_MenuAdd(SubPage1, "Hello SubPage1!", routeNull);
	OLED_MenuAdd(SubPage1, "Next Page", route_SubPage1_SubPage1);
	OLED_MenuAdd(SubPage1, "Text1", routeNull);
	OLED_MenuAdd(SubPage1, "TextText2", routeNull);
	OLED_MenuAdd(SubPage1, "A Text3", routeNull);
	OLED_MenuAdd(SubPage1, "Is Text4", routeNull);
	OLED_MenuAdd(SubPage1, "Text5?", routeNull);
	OLED_MenuAdd(SubPage1, "Return", route_SubPage1_Return);
}

static void SubPage2Init(void) { //子界面2 (LED控制)
	OLED_MenuAdd(SubPage2, "Hello OLED Ctrl", routeNull);
	OLED_MenuAdd(SubPage2, "LED ON!", route_SubPage2_LED_ON);
	OLED_MenuAdd(SubPage2, "LED OFF!", route_SubPage2_LED_OFF);
	OLED_MenuAdd(SubPage2, "Return", route_SubPage2_Return);
}

static void SubPage3Init(void) {
	OLED_MenuAdd(SubPage3, "Return", route_SubPage3_Return);
}

static void SubPage1_SubPage1Init(void) {
	OLED_MenuAdd(SubPage1_SubPage1, "Return", route_SubPage1_SubPage1_Return);
}

/**************************************************************

 **界面控制初始化*******************
 
**************************************************************/

static void MenuControlInit(void) {
	LED_Init();
	Encoder_Init();
	OLED_MenuInit();
	HomePageInit();
	SubPage1Init();
	SubPage2Init();
	SubPage3Init();
	SubPage1_SubPage1Init();
}

/**************************************************************

 **主入口函数*******************
 
**************************************************************/

uint8_t QuitFlag; // 可选择用于退出菜单界面

void MenuMain(void) {
	MenuControlInit(); //初始化各个界面
	
	OLED_MenuLoad(Home); //载入主界面
	QuitFlag = 0;
	
	int16_t countPre = 0, countNxt;
	
	while (1) {
		countNxt = (TIM_GetCounter(TIM2) - 10000) / 4; // 有可能会溢出

		if (countNxt - countPre > 1000) { //下溢, 溢出后要进行反向处理
			OLED_MenuSelectUp();
		}
		else if (countNxt - countPre < -1000) { // 上溢
			OLED_MenuSelectDown();
		}
		if (countNxt - countPre > 0) { //向下滚动
			OLED_MenuSelectDown();
		}
		else if (countNxt - countPre < 0) { //向上滚动
			OLED_MenuSelectUp();
		}
		
		if (QuitFlag) break;
		
		countPre = countNxt;
	}
}
