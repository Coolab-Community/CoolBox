#include "MyTask.h"
#include "main.h"

extern ADC_HandleTypeDef hadc3; // ADC Handler defined in "main.h"
UART_HandleTypeDef huart1;
osMailQDef (message_q, sizeof(ADC_Struct), ADC_Struct);  // Declaring osmailQ : tranfer adcvalue through threads
osMailQId  (Mail_q); 

ADC_Struct *ADCValues ; 
uint16_t adcBuffer[2]; // Buffer for store the results of the ADC conversion

void ADC_Task (const void * argument)
{
  Mail_q = osMailCreate(osMailQ(message_q), NULL); // Creating the Mail 
  HAL_ADC_Start_DMA(&hadc3, (uint32_t*)adcBuffer, 2); // Start ADC with DMA mode and register valuer in "adcBuffer[]"
  while(1)
  {

    ADCValues = (ADC_Struct *) osMailAlloc(Mail_q, 500);  // Allocate Memory to the MailQ
    ADCValues->ADC_1 = (float)adcBuffer[0]/4095*3300*2;                    //AdcValues 
    ADCValues->ADC_2 = (float)adcBuffer[1]/4095*3300*4;
    osMailPut(Mail_q, ADCValues);                       // Send the Mailq to the Model.cpp 
    osDelay(500);
  }
}
