/**
  ******************************************************************************
  * @file    usb_prop.h
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   All processing related to KeyBoard Mouse demo
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
#ifndef __USB_PROP_H
#define __USB_PROP_H

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
/* Exported types ------------------------------------------------------------*/
typedef enum _HID_REQUESTS
{
  GET_REPORT = 1,
  GET_IDLE,
  GET_PROTOCOL,

  SET_REPORT = 9,
  SET_IDLE,
  SET_PROTOCOL
} HID_REQUESTS;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void KeyBoard_init(void);
void KeyBoard_Reset(void);
void KeyBoard_SetConfiguration(void);
void KeyBoard_SetDeviceAddress (void);
void KeyBoard_Status_In (void);
void KeyBoard_Status_Out (void);
RESULT KeyBoard_Data_Setup(uint8_t);
RESULT KeyBoard_NoData_Setup(uint8_t);
RESULT KeyBoard_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *KeyBoard_GetDeviceDescriptor(uint16_t );
uint8_t *KeyBoard_GetConfigDescriptor(uint16_t);
uint8_t *KeyBoard_GetStringDescriptor(uint16_t);
RESULT KeyBoard_SetProtocol(void);
uint8_t *KeyBoard_GetProtocolValue(uint16_t Length);
RESULT KeyBoard_SetProtocol(void);
uint8_t *KeyBoard_GetReportDescriptor(uint16_t Length);
uint8_t *KeyBoard_GetHIDDescriptor(uint16_t Length);
uint8_t *Audio_Equipment_Controller_GetReportDescriptor(uint16_t Length);
uint8_t *Audio_Equipment_Controller_GetHIDDescriptor(uint16_t Length);

/* Exported define -----------------------------------------------------------*/
#define KeyBoard_GetConfiguration          NOP_Process
//#define KeyBoard_SetConfiguration          NOP_Process
#define KeyBoard_GetInterface              NOP_Process
#define KeyBoard_SetInterface              NOP_Process
#define KeyBoard_GetStatus                 NOP_Process
#define KeyBoard_ClearFeature              NOP_Process
#define KeyBoard_SetEndPointFeature        NOP_Process
#define KeyBoard_SetDeviceFeature          NOP_Process
//#define KeyBoard_SetDeviceAddress          NOP_Process

#define REPORT_DESCRIPTOR                  0x22

#endif /* __USB_PROP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
