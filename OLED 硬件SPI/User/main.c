#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void) {
	/*OLED初始化*/
	OLED_Init();
	
	/*在(0, 0)位置显示字符'A'，字体大小为8*16点阵*/
	OLED_ShowChar(0, 0, 'A', OLED_8X16);
	
	/*在(16, 0)位置显示字符串"Hello World!"，字体大小为8*16点阵*/
	OLED_ShowString(16, 0, "Hello World!", OLED_8X16);
	
	/*在(0, 18)位置显示字符'A'，字体大小为6*8点阵*/
	OLED_ShowChar(0, 18, 'A', OLED_6X8);
	
	/*在(16, 18)位置显示字符串"Hello World!"，字体大小为6*8点阵*/
	OLED_ShowString(16, 18, "Hello World!", OLED_6X8);
	
	/*在(0, 28)位置显示数字12345，长度为5，字体大小为6*8点阵*/
	OLED_ShowNum(0, 28, 12345, 5, OLED_6X8);
	
	/*在(40, 28)位置显示有符号数字-66，长度为2，字体大小为6*8点阵*/
	OLED_ShowSignedNum(40, 28, -66, 2, OLED_6X8);
	
	/*在(70, 28)位置显示十六进制数字0xA5A5，长度为4，字体大小为6*8点阵*/
	OLED_ShowHexNum(70, 28, 0xA5A5, 4, OLED_6X8);
	
	/*在(0, 38)位置显示二进制数字0xA5，长度为8，字体大小为6*8点阵*/
	OLED_ShowBinNum(0, 38, 0xA5, 8, OLED_6X8);
	
	/*在(60, 38)位置显示浮点数字123.45，整数部分长度为3，小数部分长度为2，字体大小为6*8点阵*/
	OLED_ShowFloatNum(60, 38, 123.45, 3, 2, OLED_6X8);
	
	/*在(0, 48)位置显示汉字串"你好，世界。"，字体大小为固定的16*16点阵*/
	OLED_ShowChinese(0, 48, "你好，世界。");
	
	/*在(96, 48)位置显示图像，宽16像素，高16像素，图像数据为Diode数组*/
	OLED_ShowImage(96, 48, 16, 16, Diode);
	
	/*在(96, 18)位置打印格式化字符串，字体大小为6*8点阵，格式化字符串为"[%02d]"*/
	OLED_Printf(96, 18, OLED_6X8, "[%02d]", 6);
	
	/*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
	OLED_Update();
	
	/*延时3000ms，观察现象*/
	Delay_ms(3000);
	
	/*清空OLED显存数组*/
	OLED_Clear();
	
	/*在(5, 8)位置画点*/
	OLED_DrawPoint(5, 8);
	
	/*获取(5, 8)位置的点*/
	if (OLED_GetPoint(5, 8))
	{
		/*如果指定点点亮，则在(10, 4)位置显示字符串"YES"，字体大小为6*8点阵*/
		OLED_ShowString(10, 4, "YES", OLED_6X8);
	}
	else
	{
		/*如果指定点未点亮，则在(10, 4)位置显示字符串"NO "，字体大小为6*8点阵*/
		OLED_ShowString(10, 4, "NO ", OLED_6X8);
	}
	
	/*在(40, 0)和(127, 15)位置之间画直线*/
	OLED_DrawLine(40, 0, 127, 15);
	
	/*在(40, 15)和(127, 0)位置之间画直线*/
	OLED_DrawLine(40, 15, 127, 0);
	
	/*在(0, 20)位置画矩形，宽12像素，高15像素，未填充*/
	OLED_DrawRectangle(0, 20, 12, 15, OLED_UNFILLED);
	
	/*在(0, 40)位置画矩形，宽12像素，高15像素，填充*/
	OLED_DrawRectangle(0, 40, 12, 15, OLED_FILLED);
	
	/*在(20, 20)、(40, 25)和(30, 35)位置之间画三角形，未填充*/
	OLED_DrawTriangle(20, 20, 40, 25, 30, 35, OLED_UNFILLED);
	
	/*在(20, 40)、(40, 45)和(30, 55)位置之间画三角形，填充*/
	OLED_DrawTriangle(20, 40, 40, 45, 30, 55, OLED_FILLED);
	
	/*在(55, 27)位置画圆，半径8像素，未填充*/
	OLED_DrawCircle(55, 27, 8, OLED_UNFILLED);
	
	/*在(55, 47)位置画圆，半径8像素，填充*/
	OLED_DrawCircle(55, 47, 8, OLED_FILLED);
	
	/*在(82, 27)位置画椭圆，横向半轴12像素，纵向半轴8像素，未填充*/
	OLED_DrawEllipse(82, 27, 12, 8, OLED_UNFILLED);
	
	/*在(82, 47)位置画椭圆，横向半轴12像素，纵向半轴8像素，填充*/
	OLED_DrawEllipse(82, 47, 12, 8, OLED_FILLED);
	
	/*在(110, 18)位置画圆弧，半径15像素，起始角度25度，终止角度125度，未填充*/
	OLED_DrawArc(110, 18, 15, 25, 125, OLED_UNFILLED);
	
	/*在(110, 38)位置画圆弧，半径15像素，起始角度25度，终止角度125度，填充*/
	OLED_DrawArc(110, 38, 15, 25, 125, OLED_FILLED);
	
	/*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
	OLED_Update();
	
	/*延时3000ms，观察现象*/
	Delay_ms(3000);
	
	while (1)
	{
		for (uint8_t i = 0; i < 4; i ++)
		{
			/*将OLED显存数组部分数据取反，从(0, i * 16)位置开始，宽128像素，高16像素*/
			OLED_ReverseArea(0, i * 16, 128, 16);
			
			/*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
			OLED_Update();
			
			/*延时1000ms，观察现象*/
			Delay_ms(1000);
			
			/*把取反的内容翻转回来*/
			OLED_ReverseArea(0, i * 16, 128, 16);
		}
		
		/*将OLED显存数组全部数据取反*/
		OLED_Reverse();
		
		/*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
		OLED_Update();
		
		/*延时1000ms，观察现象*/
		Delay_ms(1000);
	}
}
