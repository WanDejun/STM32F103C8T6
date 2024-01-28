#include "hw_config.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t PrevXferComplete = 1;
RCC_ClocksTypeDef RCC_ClockFreq;
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void) {
  Set_System();
  
  USB_Interrupts_Config();
  
  Set_USBClock();
  
  USB_Init();
  
  while (1) {
    if (bDeviceState == CONFIGURED) {
      if ((KeyState() != 0) && (PrevXferComplete)) {
        KeyBoard_Send();
      }
    }
  }
}
