#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

extern osMailQId (Mail_q);   // Declare external handler for  Mailq    

Model::Model() : modelListener(0)
{
}

void Model::tick()
{

    osEvent event = osMailGet(Mail_q, osWaitForever); // Grab the incoming Mail
    
     if (event.status == osEventMail)
     {
         ADC_Struct *received_Value = (ADC_Struct *)event.value.p;  // get Mail-Tdef  pointer 
         CurrentValue.ADC_1 = received_Value->ADC_1/1000 ;/*(ADC Value/resolution)*Vref = real tension 
                                                                      Resolution 12 bits <=> 4095 dec ; Vref = 3.3v 
                                                                      *2 <=> ADC value *2 for the application ; the same thing for *4 :) */
         CurrentValue.ADC_2 = received_Value->ADC_2/1000;
         modelListener->updatePresenter();
         osMailFree(Mail_q, received_Value);    // Free the memory location of the Mailq
     }
}
