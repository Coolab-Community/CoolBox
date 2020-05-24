#include "IWDG_Task.h"
#include "main.h"

extern IWDG_HandleTypeDef hiwdg;
UART_HandleTypeDef huart1;
void IWDG_Task (const void * argument)
{

  while(1)
  {

	  HAL_IWDG_Refresh(&hiwdg);
	  osDelay(1);
  }
}
