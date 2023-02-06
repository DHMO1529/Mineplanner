#include "MinePlanner/UI/Widget/MyCheckButton.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
MyCheckButton::MyCheckButton():
 m_toggleButton(String::empty)
,Component(String::empty)
{
	this->setSize(150,25);
	m_toggleButton.setSize(this->getWidth(),this->getHeight());
	this->addAndMakeVisible(&m_toggleButton);
}
void MyCheckButton::setText(const String& text)
{
	m_toggleButton.setButtonText(text);
	m_toggleButton.changeWidthToFitText();
}
void MyCheckButton::setToolTip(const String& tooltip)
{
	m_toggleButton.setTooltip(tooltip);
}
void MyCheckButton::setShortCut(const KeyPress& key)
{
	m_toggleButton.addShortcut(key);
}
void MyCheckButton::referTo(const Value& value_bool)
{
	m_toggleButton.getToggleStateValue().referTo(value_bool);
}

}//Widget
}//UI
}//MinePlanner