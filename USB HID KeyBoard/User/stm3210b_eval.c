#include "stm3210b_eval.h"

/**
 * 	@brief 按键信息
 */
GPIO_TypeDef* KEY_PORT[KEYn] = {	KEY_a_A_GPIO_PORT, KEY_b_B_GPIO_PORT, KEY_c_C_GPIO_PORT, KEY_d_D_GPIO_PORT,
									KEY_ALL_GPIO_PORT };

const uint16_t KEY_PIN[KEYn] = {	KEY_a_A_PIN, KEY_b_B_PIN, KEY_c_C_PIN, KEY_d_D_PIN, KEY_ALL_PIN }; 

const uint32_t KEY_CLK[KEYn] = {	KEY_a_A_GPIO_CLK, KEY_b_B_GPIO_CLK, KEY_c_C_GPIO_CLK, KEY_d_D_GPIO_CLK,
									KEY_ALL_GPIO_CLK }; 

const uint16_t KEY_EXTI_LINE[KEYn] = { KEY_a_A_EXTI_LINE, KEY_b_B_EXTI_LINE, KEY_c_C_EXTI_LINE, KEY_d_D_EXTI_LINE,
									   KEY_ALL_EXTI_LINE }; 

const uint16_t KEY_EXTI_PORT_SOURCE[KEYn] = { KEY_a_A_EXTI_PORT_SOURCE, KEY_b_B_EXTI_PORT_SOURCE, 
											  KEY_c_C_EXTI_PORT_SOURCE, KEY_d_D_EXTI_PORT_SOURCE,
											  KEY_ALL_EXTI_PORT_SOURCE }; 
								
const uint16_t KEY_EXTI_PIN_SOURCE[KEYn] = {	KEY_a_A_EXTI_PIN_SOURCE, KEY_b_B_EXTI_PIN_SOURCE, 
												KEY_c_C_EXTI_PIN_SOURCE, KEY_d_D_EXTI_PIN_SOURCE,
												KEY_ALL_EXTI_PIN_SOURCE }; 

const uint16_t KEY_EXTI_IRQn[KEYn] = { KEY_a_A_EXTI_IRQn, KEY_b_B_EXTI_IRQn, KEY_c_C_EXTI_IRQn, KEY_d_D_EXTI_IRQn,
									   KEY_ALL_EXTI_IRQn }; 

uint32_t GetKeyState(KEY_TypeDef Button)
{
  return GPIO_ReadInputDataBit(KEY_PORT[Button], KEY_PIN[Button]);
}

