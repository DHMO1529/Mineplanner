#include "MinePlanner/UI/Widget/MyNumericUpDown.hpp"

#include "MinePlanner/UI/MainWindow.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
MyNumericUpDown::MyNumericUpDown(bool isRedistKeyEventCatch):
 SettableTooltipClient()
,m_label(String::empty,String::empty)
,m_slider()
{
	this->setSize(190,40);
		
	m_label.attachToComponent(&m_slider,true);
	this->addAndMakeVisible(&m_label);

	m_slider.setTextBoxStyle(Slider::TextBoxLeft,false,70,25);
	m_slider.setSize(70,40);
	m_slider.setTopRightPosition(this->getWidth(),0);

	m_slider.setSliderStyle(Slider::IncDecButtons);
	m_slider.setRange(-256.0,512.0,1.0);
	m_slider.setIncDecButtonsMode(Slider::incDecButtonsDraggable_Vertical);
	m_slider.setMouseDragSensitivity(1000);
	
	this->setMouseClickGrabsKeyboardFocus(false);
	this->addAndMakeVisible(&m_slider);

	if(isRedistKeyEventCatch)
		getMainWindow()->addKeyListener(this);
}
MyNumericUpDown::~MyNumericUpDown()
{
}
void MyNumericUpDown::setText(const String& text)
{
	m_label.setText(text,false);
}
void MyNumericUpDown::setToolTip(const String& tooltip)
{
	m_label.setTooltip(tooltip);
}
void MyNumericUpDown::setRange(int min,int max)
{
	m_slider.setRange(min,max,1.0);
}
void MyNumericUpDown::setLabelColour(int colourId,const Colour& colour)
{
	m_label.setColour(colourId,colour);
}
void MyNumericUpDown::setValue(int value)
{
	m_slider.setValue(value);
}
int MyNumericUpDown::getValue()const
{
	return static_cast<int>( m_slider.getValue() );
}

void MyNumericUpDown::referTo(const Value& value_double)
{
	m_slider.getValueObject().referTo(value_double);
}
//private
void MyNumericUpDown::upValue()
{
	setValue(getValue() + 1);
}
void MyNumericUpDown::downValue()
{
	setValue(getValue() - 1);
}
bool MyNumericUpDown::keyPressed(const KeyPress& key,Component*)
{
	if(!this->isShowing())
	{
		return false;
	}
	if(key.getKeyCode() == KeyPress::upKey)
	{
		upValue();
		return true;
	}
	else if(key.getKeyCode() == KeyPress::downKey)
	{
		downValue();
		return true;
	}
	return false;
}
}//Widget
}//UI
}//MinePlanner