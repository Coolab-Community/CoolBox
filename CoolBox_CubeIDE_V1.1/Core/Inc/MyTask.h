#include "main.h" 
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

void ADC_Task (void const * argument);

typedef struct 
{
  float ADC_1 ;   //ADC3 channel IN0  -> A0
  float ADC_2 ;  // ADC3 channel IN8  -> A1
}
ADC_Struct;   // Struct Used to carry de Adc Values through all the .C files using adc values
