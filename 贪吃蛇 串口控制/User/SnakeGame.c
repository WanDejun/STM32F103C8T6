#include "stm32f10x.h"                  // Device header
#include "SnakeGame.h"
#include "lcd.h"
#include "lcd_init.h"
#include "Delay.h"
#include "Key.h"
#include "MyRTC.h"
#include "Store.h"

#define LENX 32
#define LENY 32

#define BODY_COLOR		GREEN
#define HEAD_COLOR		BLUE
#define CANDY_COLOR		RED

uint16_t SLEEP_TIME; //难度

uint8_t output_data[LENY][LENX];

typedef struct LOCATION{
    uint8_t x;
    uint8_t y;
} snake_loc, candy_loc;

snake_loc snake_Head, snake_Tail;
struct LOCATION mx_next[LENY][LENX]; //标记后节点
struct LOCATION mx_pre[LENY][LENX]; //标记前节点
uint8_t mx_flag[LENY][LENX]; //标记蛇身
candy_loc candy;
uint8_t flag_game_over = 0;

int8_t dis[5][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {0, 0}};
int8_t key_status; //0:up 1:down 2:left 3:right 4:stop

uint16_t Score; 

uint32_t srand;

uint32_t rand() {
  srand = ~srand + (srand << 15); // srand = (srand << 15) - srand - 1;
  srand = srand ^ (srand >> 12);
  srand = srand + (srand << 2);
  srand = srand ^ (srand >> 4);
  srand = srand * 2057; // srand = (srand + (srand << 3)) + (srand << 11);
  srand = srand ^ (srand >> 16);
  return srand;
}

static void ShowScore(void) {
	LCD_ShowString(2, 132, (uint8_t *)"Score:", WHITE, BLACK, 12, 0);
	LCD_ShowIntNum(36, 132, Score, 4, WHITE, BLACK, 12);
}

static void ShowHighestScore(void) {
	LCD_ShowString(2, 144, (uint8_t *)"History Highest:", WHITE, BLACK, 12, 0);
	LCD_ShowIntNum(96, 144, Store_Data[1], 4, WHITE, BLACK, 12);
}

static void SelectHardLevel_TextSelect(uint8_t loc) {//置loc处的按键为选中
	switch (loc) {
		case 0:
			LCD_ShowString(0, 24, (uint8_t*)" Easy", BLACK, WHITE, 12, 0);
			break;
		case 1:
			LCD_ShowString(0, 36, (uint8_t*)" Medium", BLACK, WHITE, 12, 0);
			break;
		case 2:
			LCD_ShowString(0, 48, (uint8_t*)" Hard", BLACK, WHITE, 12, 0);
			break;
		default:
			break;
	}
}

static void SelectHardLevel_TextUnSelect(uint8_t loc) { //置loc处的按键为非选中
	switch (loc) {
		case 0:
			LCD_ShowString(0, 24, (uint8_t*)" Easy", WHITE, BLACK, 12, 0);
			break;
		case 1:
			LCD_ShowString(0, 36, (uint8_t*)" Medium", WHITE, BLACK, 12, 0);
			break;
		case 2:
			LCD_ShowString(0, 48, (uint8_t*)" Hard", WHITE, BLACK, 12, 0);
			break;
		default:
			break;
	}
}

static void SelectHardLevel(void) {
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	
	uint8_t loc = 0, keycode;
	LCD_ShowString(0, 0, (uint8_t*)"Selete your game hard", WHITE, BLACK, 12, 0);
	LCD_ShowString(0, 12, (uint8_t*)"level:", WHITE, BLACK, 12, 0);
	LCD_ShowString(0, 24, (uint8_t*)" Easy", BLACK, WHITE, 12, 0);
	LCD_ShowString(0, 36, (uint8_t*)" Medium", WHITE, BLACK, 12, 0);
	LCD_ShowString(0, 48, (uint8_t*)" Hard", WHITE, BLACK, 12, 0);
	
	while (1) {
		while (!Key_GetNum().KeyHold); //等待按键按下
		keycode = Key_GetNum().KeyCode;
		
		switch (keycode) {
		case 0:
			SelectHardLevel_TextUnSelect(loc);
			loc = (3 + loc - 1) % 3;
			SelectHardLevel_TextSelect(loc);
			break;
		case 1:
			SelectHardLevel_TextUnSelect(loc);
			loc = (loc + 1) % 3;
			SelectHardLevel_TextSelect(loc);
			break;
		case 3:
			goto loop;
		default:
			break;
		}
		while (Key_GetNum().KeyHold); //等待按键释放
	}
	loop:
	while (Key_GetNum().KeyHold); //等待按键释放
	
	switch (loc) {
    case 0:
        SLEEP_TIME = 50;
        break;
    case 1:
        SLEEP_TIME = 30;
        break;
    case 2:
        SLEEP_TIME = 10;
        break;
    default:
        break;
    }
}

static void Snake_Init(void) {	
	SelectHardLevel();
		
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK); //
	srand = MyRTC_GetTime();
	
	uint8_t i, j, dis_status;
	
	key_status = rand() % 4;;
	flag_game_over = 0;
	Score = 0;
	
	LCD_ShowString(2, 132, (uint8_t *)"Score: ", WHITE, BLACK, 12, 0);
	ShowScore();
	
	LCD_DrawLine(0, 128, 128, 128, WHITE);
	
	for (i = 0; i < LENX; i++) { //初始化
		for (j = 0; j < LENY; j++) {
			mx_flag[i][j] = 0;
		}
	}
	
	dis_status = key_status;
	
	snake_Head.x = rand() % (LENX - 20) + 10; //初始化头
    snake_Head.y = rand() % (LENY - 20) + 10;
	//绘制蛇头
	LCD_DrawRectangle(snake_Head.x << 2, snake_Head.y << 2, snake_Head.x << 2 | 3, snake_Head.y << 2 | 3, HEAD_COLOR);
	
	for (i = 1; i < 4; i++) {
		mx_flag[snake_Head.x - i * dis[dis_status][0]][snake_Head.y - i * dis[dis_status][1]] = 1;
		//绘制蛇身体
		LCD_DrawRectangle((snake_Head.x - i * dis[dis_status][0]) << 2, (snake_Head.y - i * dis[dis_status][1]) << 2, 
				(snake_Head.x - i * dis[dis_status][0]) << 2 | 3, (snake_Head.y - i * dis[dis_status][1]) << 2 | 3, BODY_COLOR);
		mx_next[snake_Head.x - (i - 1) * dis[dis_status][0]][snake_Head.y - (i - 1) * dis[dis_status][1]].x = snake_Head.x - i * dis[dis_status][0];
		mx_next[snake_Head.x - (i - 1) * dis[dis_status][0]][snake_Head.y - (i - 1) * dis[dis_status][1]].y = snake_Head.y - i * dis[dis_status][1];
		mx_pre[snake_Head.x - i * dis[dis_status][0]][snake_Head.y - i * dis[dis_status][1]].x = snake_Head.x - (i - 1) * dis[dis_status][0];
		mx_pre[snake_Head.x - i * dis[dis_status][0]][snake_Head.y - i * dis[dis_status][1]].y = snake_Head.y - (i - 1) * dis[dis_status][1];
	}
	
	
    snake_Tail.x = snake_Head.x - 3 * dis[dis_status][0]; //初始化尾
    snake_Tail.y = snake_Head.y - 3 * dis[dis_status][1];
	
    do { //初始化糖果
        candy.x = rand() % LENX; 
        candy.y = rand() % LENY;
    } while (mx_flag[candy.x][candy.y]);
	
	LCD_DrawRectangle(candy.x << 2, candy.y << 2, candy.x << 2 | 3, candy.y << 2 | 3, CANDY_COLOR);
	
	while(Key_GetNum().KeyHold);
	
	// for (j = 0; j < 0xff; j++) for (i = 0; i < 0xff; i++);
}

static uint8_t check_cycle_die(int xx, int yy) {
    return mx_flag[xx][yy];
}

static void move_snake(void) {
    int8_t xx = snake_Head.x + dis[key_status][0], yy = snake_Head.y + dis[key_status][1]; //head前移

    if (xx < 0 || yy < 0 || xx >= LENX || yy >= LENY) {flag_game_over = 1; return;} //判断越界

    if (check_cycle_die(xx, yy)) { flag_game_over = 1;return; } //撞上自己
	
	//局部刷新蛇头图像
	LCD_DrawRectangle(snake_Head.x << 2, snake_Head.y << 2, snake_Head.x << 2 | 3, snake_Head.y << 2 | 3, GREEN);
	LCD_DrawRectangle(xx << 2, yy << 2, xx << 2 | 3, yy << 2 | 3, BLUE);

    mx_pre[snake_Head.x][snake_Head.y].x = xx; //修改头指针
    mx_pre[snake_Head.x][snake_Head.y].y = yy;

    mx_next[xx][yy].x = snake_Head.x;
    mx_next[xx][yy].y = snake_Head.y;

    snake_Head.x = xx; //修改头
    snake_Head.y = yy;

    mx_flag[xx][yy] = 1;

    if (snake_Head.x == candy.x && snake_Head.y == candy.y) { //吃到糖果
		// 原本糖果图像消失
		LCD_DrawRectangle(candy.x << 2, candy.y << 2, candy.x << 2 | 3, candy.y << 2 | 3, BLUE);
		
        do {
            candy.x = rand() % LENX;
            candy.y = rand() % LENY;
        } while (mx_flag[candy.x][candy.y]);
        Score++;
		
		// 新糖果图像
		LCD_DrawRectangle(candy.x << 2, candy.y << 2, candy.x << 2 | 3, candy.y << 2 | 3, CANDY_COLOR);
    }
    else {
        mx_flag[snake_Tail.x][snake_Tail.y] = 0;
        xx = mx_pre[snake_Tail.x][snake_Tail.y].x; //修改尾
        yy = mx_pre[snake_Tail.x][snake_Tail.y].y;
		
		// 原本蛇尾图像消失
		LCD_DrawRectangle(snake_Tail.x << 2, snake_Tail.y << 2, snake_Tail.x << 2 | 3, snake_Tail.y << 2 | 3, BLACK);
		
        snake_Tail.x = xx;
        snake_Tail.y = yy;
    }
}

static void output_die(void) {
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	LCD_ShowString(5, 68, (uint8_t *)"GAME OVER!", WHITE, BLACK, 24, 1);
	ShowScore();
	ShowHighestScore();
}

static void game_start(void) {
	Snake_Init();
	while (!Key_GetNum().KeyHold || mx_flag[snake_Head.x + dis[Key_GetNum().KeyCode][0]][snake_Head.y + dis[Key_GetNum().KeyCode][1]]);
    while (!flag_game_over) {
		uint16_t i, j;
		key_status = Key_GetNum().KeyCode + key_status == 1  || Key_GetNum().KeyCode + key_status == 5 ? key_status : Key_GetNum().KeyCode;
		LCD_ShowIntNum(2, 145, key_status, 1, WHITE, BLACK, 12);
		move_snake();
		ShowScore();
		
		for (i = 0; i < SLEEP_TIME; i++) for (j = 0; j < 0xffff; j++);
    }
	if (Score > Store_Data[1]) {
		Store_Data[1] = Score;
		Store_Save();
	}
    output_die();
	
	while (!Key_GetNum().KeyHold);
}

void SnackMain(void) {
    game_start();
}
