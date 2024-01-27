#ifndef __STM3210B_EVAL_H
#define __STM3210B_EVAL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32_eval_legacy.h"

typedef enum {
	  LED1 = 0,
	  LED2 = 1,
	  LED3 = 2,
	  LED4 = 3
} Led_TypeDef;

typedef enum {  
	BUTTON_CLICK_L = 0,
	BUTTON_CLICK_R = 1,
	BUTTON_CLICK_M = 2,
	BUTTON_RIGHT = 3,
	BUTTON_LEFT = 4,
	BUTTON_UP = 5,
	BUTTON_DOWN = 6,
	BUTTON_ROLL_UP = 7,
	BUTTON_ROLL_DOWN =  8
} Button_TypeDef;

#define USE_STM3210B_EVAL

#define BUTTONn                          	9

/**
 * 	@brief Click_L-button
 */
#define CLICK_L_BUTTON_PIN                	GPIO_Pin_4
#define CLICK_L_BUTTON_GPIO_PORT          	GPIOA
#define CLICK_L_BUTTON_GPIO_CLK           	RCC_APB2Periph_GPIOA
#define CLICK_L_BUTTON_EXTI_LINE          	EXTI_Line4
#define CLICK_L_BUTTON_EXTI_PORT_SOURCE   	GPIO_PortSourceGPIOA
#define CLICK_L_BUTTON_EXTI_PIN_SOURCE    	GPIO_PinSource4
#define CLICK_L_BUTTON_EXTI_IRQn          	EXTI4_IRQn
/**	
 * @brief Click_R-button	
 */	
#define CLICK_R_BUTTON_PIN                	GPIO_Pin_5
#define CLICK_R_BUTTON_GPIO_PORT          	GPIOA
#define CLICK_R_BUTTON_GPIO_CLK           	RCC_APB2Periph_GPIOA
#define CLICK_R_BUTTON_EXTI_LINE          	EXTI_Line5
#define CLICK_R_BUTTON_EXTI_PORT_SOURCE   	GPIO_PortSourceGPIOA
#define CLICK_R_BUTTON_EXTI_PIN_SOURCE    	GPIO_PinSource5
#define CLICK_R_BUTTON_EXTI_IRQn          	EXTI9_5_IRQn 
/**	
 * @brief Click_M push-button
 */
#define CLICK_M_BUTTON_PIN                  GPIO_Pin_6
#define CLICK_M_BUTTON_GPIO_PORT            GPIOA
#define CLICK_M_BUTTON_GPIO_CLK             RCC_APB2Periph_GPIOA
#define CLICK_M_BUTTON_EXTI_LINE            EXTI_Line6
#define CLICK_M_BUTTON_EXTI_PORT_SOURCE     GPIO_PortSourceGPIOA
#define CLICK_M_BUTTON_EXTI_PIN_SOURCE      GPIO_PinSource6
#define CLICK_M_BUTTON_EXTI_IRQn            EXTI9_5_IRQn
/**
 * @brief Joystick Right push-button
 */
#define RIGHT_BUTTON_PIN                 	GPIO_Pin_0
#define RIGHT_BUTTON_GPIO_PORT           	GPIOA
#define RIGHT_BUTTON_GPIO_CLK            	RCC_APB2Periph_GPIOA
#define RIGHT_BUTTON_EXTI_LINE           	EXTI_Line0
#define RIGHT_BUTTON_EXTI_PORT_SOURCE    	GPIO_PortSourceGPIOA
#define RIGHT_BUTTON_EXTI_PIN_SOURCE     	GPIO_PinSource0
#define RIGHT_BUTTON_EXTI_IRQn           	EXTI0_IRQn
/**
 * @brief Joystick Left push-button
 */
#define LEFT_BUTTON_PIN                  	GPIO_Pin_1
#define LEFT_BUTTON_GPIO_PORT            	GPIOA
#define LEFT_BUTTON_GPIO_CLK             	RCC_APB2Periph_GPIOA
#define LEFT_BUTTON_EXTI_LINE            	EXTI_Line1
#define LEFT_BUTTON_EXTI_PORT_SOURCE     	GPIO_PortSourceGPIOA
#define LEFT_BUTTON_EXTI_PIN_SOURCE      	GPIO_PinSource1
#define LEFT_BUTTON_EXTI_IRQn            	EXTI1_IRQn  
/**
 * @brief Joystick Up push-button
 */
#define UP_BUTTON_PIN                    	GPIO_Pin_2
#define UP_BUTTON_GPIO_PORT              	GPIOA
#define UP_BUTTON_GPIO_CLK               	RCC_APB2Periph_GPIOA
#define UP_BUTTON_EXTI_LINE              	EXTI_Line2
#define UP_BUTTON_EXTI_PORT_SOURCE       	GPIO_PortSourceGPIOA
#define UP_BUTTON_EXTI_PIN_SOURCE        	GPIO_PinSource2
#define UP_BUTTON_EXTI_IRQn              	EXTI2_IRQn  
/**	
 * @brief Joystick Down push-button	
 */  	
#define DOWN_BUTTON_PIN                  	GPIO_Pin_3
#define DOWN_BUTTON_GPIO_PORT            	GPIOA
#define DOWN_BUTTON_GPIO_CLK             	RCC_APB2Periph_GPIOA
#define DOWN_BUTTON_EXTI_LINE            	EXTI_Line3
#define DOWN_BUTTON_EXTI_PORT_SOURCE     	GPIO_PortSourceGPIOA
#define DOWN_BUTTON_EXTI_PIN_SOURCE      	GPIO_PinSource3
#define DOWN_BUTTON_EXTI_IRQn            	EXTI3_IRQn  
/**
 * @brief Roll_up-button
 */
#define ROLL_UP_BUTTON_PIN               	GPIO_Pin_7
#define ROLL_UP_BUTTON_GPIO_PORT         	GPIOA
#define ROLL_UP_BUTTON_GPIO_CLK          	RCC_APB2Periph_GPIOA
#define ROLL_UP_BUTTON_EXTI_LINE         	EXTI_Line7
#define ROLL_UP_BUTTON_EXTI_PORT_SOURCE  	GPIO_PortSourceGPIOA
#define ROLL_UP_BUTTON_EXTI_PIN_SOURCE   	GPIO_PinSource7
#define ROLL_UP_BUTTON_EXTI_IRQn         	EXTI9_5_IRQn
/**
 * @brief Roll_down-button
 */
#define ROLL_DOWN_BUTTON_PIN              	GPIO_Pin_8
#define ROLL_DOWN_BUTTON_GPIO_PORT        	GPIOA
#define ROLL_DOWN_BUTTON_GPIO_CLK         	RCC_APB2Periph_GPIOA
#define ROLL_DOWN_BUTTON_EXTI_LINE        	EXTI_Line8
#define ROLL_DOWN_BUTTON_EXTI_PORT_SOURCE 	GPIO_PortSourceGPIOA
#define ROLL_DOWN_BUTTON_EXTI_PIN_SOURCE  	GPIO_PinSource8
#define ROLL_DOWN_BUTTON_EXTI_IRQn        	EXTI9_5_IRQn   


uint32_t GetKeyState(Button_TypeDef Button);
   
#endif /* __STM3210B_EVAL_H */
