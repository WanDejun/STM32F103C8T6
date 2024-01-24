/**
  ******************************************************************************
  * @file    platform_config.h
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Evaluation board specific configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#if defined (USE_STM32L152_EVAL)
  #include "stm32l152_eval.h"

#elif defined (USE_STM32L152D_EVAL)
  #include "stm32l152d_eval.h"

#elif defined (USE_STM3210E_EVAL)
  #include "stm3210e_eval.h"

#elif defined (USE_STM3210B_EVAL)
  #include "stm3210b_eval.h"

#elif defined (USE_STM32373C_EVAL)
 #include "stm32373c_eval.h"

#elif defined (USE_STM32303C_EVAL)
 #include "stm32303c_eval.h"

#elif defined (USE_NUCLEO)
  #include "stm32f30x.h"

#else
 #error "Missing define: Evaluation board (ie. USE_STM3210E_EVAL)"
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Define if Low power mode is enabled; it allows entering the device into 
   STOP mode following USB Suspend event, and wakes up after the USB wakeup
   event is received. */
//#define USB_LOW_PWR_MGMT_SUPPORT
     
/*Unique Devices IDs register set*/

#if defined(STM32L1XX_MD) || defined(STM32L1XX_HD) || defined(STM32L1XX_MD_PLUS) 

#define         ID1          (0x1FF80050)
#define         ID2          (0x1FF80054)
#define         ID3          (0x1FF80064)

#elif defined (STM32F37X) || defined(STM32F30X)

#define         ID1          (0x1FFFF7AC)
#define         ID2          (0x1FFFF7B0)
#define         ID3          (0x1FFFF7B4)

#else /*STM32F1x*/

#define         ID1          (0x1FFFF7E8)
#define         ID2          (0x1FFFF7EC)
#define         ID3          (0x1FFFF7F0)

#endif

/* Define the STM32F10x hardware depending on the used evaluation board */
#ifdef USE_STM3210B_EVAL
  #define USB_DISCONNECT                      GPIOD  
  #define USB_DISCONNECT_PIN                  GPIO_Pin_9
  
  #define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOD

  #define RCC_APB2Periph_ALLGPIO              (RCC_APB2Periph_GPIOA \
                                               | RCC_APB2Periph_GPIOB \
                                               | RCC_APB2Periph_GPIOC \
                                               | RCC_APB2Periph_GPIOD \
                                               | RCC_APB2Periph_GPIOE )
#elif defined (USE_STM3210E_EVAL)
  #define USB_DISCONNECT                      GPIOB  
  #define USB_DISCONNECT_PIN                  GPIO_Pin_14
  #define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOB
                                                
  #define RCC_APB2Periph_ALLGPIO              (RCC_APB2Periph_GPIOA \
                                               | RCC_APB2Periph_GPIOB \
                                               | RCC_APB2Periph_GPIOC \
                                               | RCC_APB2Periph_GPIOD \
                                               | RCC_APB2Periph_GPIOE \
                                               | RCC_APB2Periph_GPIOF \
                                               | RCC_APB2Periph_GPIOG )

/* The build-in USB peripheral of the STM32F103 (As example) does not provide a 
   specific interrupt for USB cable plug/unplug detection. 
   The correct way to detect the USB cable plug/unplug is to detect the availability 
   of the VBUS line using a normal GPIO pin (external interrupt line).
   PA0 is chosen just as illustrating example, you should modify the defines
   below according to your hardware configuration */

#define USB_USE_VBUS_SENSING


#if defined(USB_USE_VBUS_SENSING)
/* Configure VBUS Sensing pin */ 
  #define USB_VBUS_SENSING_PORT                     GPIOA  
  #define USB_VBUS_SENSING_PIN                      GPIO_Pin_0
  #define RCC_APB2Periph_GPIO_USB_VBUS_SENSING      RCC_APB2Periph_GPIOA
#endif

#elif defined (USE_STM32L152_EVAL) || defined (USE_STM32L152D_EVAL)
 /* 
   For STM32L15xx devices it is possible to use the internal USB pullup
   controlled by register SYSCFG_PMC (refer to RM0038 reference manual for
   more details).
   It is also possible to use external pullup (and disable the internal pullup)
   by setting the define USB_USE_EXTERNAL_PULLUP in file platform_config.h
   and configuring the right pin to be used for the external pull up configuration.
   To have more details on how to use an external pull up, please refer to 
   STM3210E-EVAL evaluation board manuals.
   */
 /* Uncomment the following define to use an external pull up instead of the 
    integrated STM32L15xx internal pull up. In this case make sure to set up
    correctly the external required hardware and the GPIO defines below.*/
/* #define USB_USE_EXTERNAL_PULLUP */

#if defined(USB_USE_EXTERNAL_PULLUP)
  /* PA0 is chosen just as illustrating example, you should modify the defines
    below according to your hardware configuration. */
  #define USB_DISCONNECT                      GPIOA
  #define USB_DISCONNECT_PIN                  GPIO_Pin_0
  #define RCC_AHBPeriph_GPIO_DISCONNECT       RCC_AHBPeriph_GPIOA
  #define STM32L15_USB_CONNECT                GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN)
  #define STM32L15_USB_DISCONNECT             GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN)                                        

#else
  #define STM32L15_USB_CONNECT                SYSCFG_USBPuCmd(ENABLE)
  #define STM32L15_USB_DISCONNECT             SYSCFG_USBPuCmd(DISABLE)
#endif /* USB_USE_EXTERNAL_PULLUP */

#elif defined (USE_STM32373C_EVAL)

  #define USB_DISCONNECT                      GPIOC  
  #define USB_DISCONNECT_PIN                  GPIO_Pin_5
  #define RCC_AHBPeriph_GPIO_DISCONNECT       RCC_AHBPeriph_GPIOC
 
  #define GPIO_Pin_KEY                        GPIO_Pin_6   /* PE.6 */
  #define GPIO_Pin_UP                         GPIO_Pin_10  /* PF.10 */
  #define GPIO_Pin_DOWN                       GPIO_Pin_2  /* PF.2 */
  #define GPIO_Pin_LEFT                       GPIO_Pin_4  /* PF.4 */
  #define GPIO_Pin_RIGHT                      GPIO_Pin_9  /* PF.9 */
  
  #define RCC_AHBPeriph_GPIO_JOY_SET1        RCC_AHBPeriph_GPIOF

  #define GPIO_RIGHT                          GPIOF
  #define GPIO_LEFT                           GPIOF
  #define GPIO_DOWN                           GPIOF
  #define GPIO_UP                             GPIOF
  #define GPIO_KEY                            GPIOE

#define RCC_AHBPeriph_ALLGPIO                 (RCC_AHBPeriph_GPIOA \
                                              | RCC_AHBPeriph_GPIOB \
                                              | RCC_AHBPeriph_GPIOC \
                                              | RCC_AHBPeriph_GPIOD \
                                              | RCC_AHBPeriph_GPIOE \
                                              | RCC_AHBPeriph_GPIOF )
#elif defined (USE_STM32303C_EVAL) || defined (USE_NUCLEO)

  #define USB_DISCONNECT                      GPIOB  
  #define USB_DISCONNECT_PIN                  GPIO_Pin_8
  #define RCC_AHBPeriph_GPIO_DISCONNECT       RCC_AHBPeriph_GPIOB

 
  #define GPIO_Pin_KEY                        GPIO_Pin_6   /* PE.6 */
  #define GPIO_Pin_UP                         GPIO_Pin_7  /* PE.7 */
  #define GPIO_Pin_DOWN                       GPIO_Pin_5  /* PD.5 */
  #define GPIO_Pin_LEFT                       GPIO_Pin_5  /* PB.4 */
  #define GPIO_Pin_RIGHT                      GPIO_Pin_6  /* PD.2 */
  
  #define RCC_AHBPeriph_GPIO_JOY_SET1        RCC_AHBPeriph_GPIOF

  #define GPIO_RIGHT                          GPIOD
  #define GPIO_LEFT                           GPIOB
  #define GPIO_DOWN                           GPIOD
  #define GPIO_UP                             GPIOE
  #define GPIO_KEY                            GPIOE

                                     
#define RCC_AHBPeriph_ALLGPIO                 (RCC_AHBPeriph_GPIOA \
                                              | RCC_AHBPeriph_GPIOB \
                                              | RCC_AHBPeriph_GPIOC \
                                              | RCC_AHBPeriph_GPIOD \
                                              | RCC_AHBPeriph_GPIOE \
                                              | RCC_AHBPeriph_GPIOF )

#endif /* USE_STM3210B_EVAL */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __PLATFORM_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

