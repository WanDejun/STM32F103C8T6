#ifndef __STM3210B_EVAL_H
#define __STM3210B_EVAL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32_eval_legacy.h"

typedef enum {  
	KEY_a_A = 0,
	KEY_b_B = 1,
	KEY_c_C = 2,
	KEY_d_D = 3
} KEY_TypeDef;

#define USE_STM3210B_EVAL

#define KEYn                       	4

/**
 * 	@brief KEY_a_A
 */
#define KEY_a_A_PIN                	GPIO_Pin_0
#define KEY_a_A_GPIO_PORT          	GPIOA
#define KEY_a_A_GPIO_CLK           	RCC_APB2Periph_GPIOA
#define KEY_a_A_EXTI_LINE          	EXTI_Line0
#define KEY_a_A_EXTI_PORT_SOURCE   	GPIO_PortSourceGPIOA
#define KEY_a_A_EXTI_PIN_SOURCE    	GPIO_PinSource0
#define KEY_a_A_EXTI_IRQn          	EXTI0_IRQn
/**
 * 	@brief KEY_b_B
 */
#define KEY_b_B_PIN                	GPIO_Pin_1
#define KEY_b_B_GPIO_PORT          	GPIOA
#define KEY_b_B_GPIO_CLK           	RCC_APB2Periph_GPIOA
#define KEY_b_B_EXTI_LINE          	EXTI_Line1
#define KEY_b_B_EXTI_PORT_SOURCE   	GPIO_PortSourceGPIOA
#define KEY_b_B_EXTI_PIN_SOURCE    	GPIO_PinSource1
#define KEY_b_B_EXTI_IRQn          	EXTI1_IRQn
/**
 * 	@brief KEY_c_C
 */
#define KEY_c_C_PIN                	GPIO_Pin_2
#define KEY_c_C_GPIO_PORT          	GPIOA
#define KEY_c_C_GPIO_CLK           	RCC_APB2Periph_GPIOA
#define KEY_c_C_EXTI_LINE          	EXTI_Line2
#define KEY_c_C_EXTI_PORT_SOURCE   	GPIO_PortSourceGPIOA
#define KEY_c_C_EXTI_PIN_SOURCE    	GPIO_PinSource2
#define KEY_c_C_EXTI_IRQn          	EXTI2_IRQn
/**
 * 	@brief KEY_d_D
 */
#define KEY_d_D_PIN                	GPIO_Pin_3
#define KEY_d_D_GPIO_PORT          	GPIOA
#define KEY_d_D_GPIO_CLK           	RCC_APB2Periph_GPIOA
#define KEY_d_D_EXTI_LINE          	EXTI_Line3
#define KEY_d_D_EXTI_PORT_SOURCE   	GPIO_PortSourceGPIOA
#define KEY_d_D_EXTI_PIN_SOURCE    	GPIO_PinSource3
#define KEY_d_D_EXTI_IRQn          	EXTI3_IRQn

uint32_t GetKeyState(KEY_TypeDef Button);
   
#endif /* __STM3210B_EVAL_H */
