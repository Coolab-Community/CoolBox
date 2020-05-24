#ifndef MODEL_HPP
#define MODEL_HPP

extern "C" 
{ 
#include "MyTask.h"
}

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    ADC_Struct get_value () { return CurrentValue;} // used in "screenView.cpp" to get adc value
    
protected:
    ModelListener* modelListener;
    
    ADC_Struct CurrentValue = {0,0} ; // Struct defined in "MyTask.h"
};

#endif // MODEL_HPP