#include "hw_config.h"

__IO uint8_t PrevXferComplete = 1;

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
      if ((JoyState() != 0) && (PrevXferComplete)) {
        Joystick_Send(JoyState());
      }
    }
  }
}
