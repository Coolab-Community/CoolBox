#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateScreen( ADC_Struct data )
{
  Unicode::snprintfFloat(textArea1Buffer,10, "%4.2f", data.ADC_1);
  Unicode::snprintfFloat(textArea2Buffer,10, "%4.2f", data.ADC_2);
  circleProgress1.setValue(int(data.ADC_1));
  circleProgress2.setValue(int(data.ADC_2));
  circleProgress1.invalidate();
  circleProgress2.invalidate();
  textArea1.invalidate();
  textArea2.invalidate();
}