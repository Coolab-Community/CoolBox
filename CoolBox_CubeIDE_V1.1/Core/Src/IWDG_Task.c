#include "IWDG_Task.h"
#include "main.h"

extern IWDG_HandleTypeDef hiwdg;

void IWDG_Task (const void * argument)
{

  while(1)
  {
	  HAL_IWDG_Refresh(&hiwdg);

  }
}
