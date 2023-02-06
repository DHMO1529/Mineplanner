#include "MinePlanner/UI/Widget/MyButton.hpp"
#include <boost/foreach.hpp>
#include "MinePlanner/UI/RepaintOpenGL.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
MyButton::MyButton():
 m_button()
,Component(String::empty)
{
	this->setSize(200,25);
		
	m_button.setBounds(0,0,this->getWidth(),this->getHeight());
	m_button.addListener(this);
	this->addAndMakeVisible(&m_button);
}
void MyButton::setText(const String& text)
{
	m_button.setButtonText(text);
	m_button.changeWidthToFitText();
}
void MyButton::setToolTip(const String& tooltip)
{
	m_button.setTooltip(tooltip);
}
void MyButton::addListener(MyListener* listener)
{
	m_listeners.push_back(listener);
}
void MyButton::addShortCut(const KeyPress& key)
{
	m_button.addShortcut(key);
}
void MyButton::setColour(int colourId,const Colour &colour)
{
	m_button.setColour(colourId,colour);
}
void MyButton::buttonClicked(Button* button)
{
	BOOST_FOREACH(MyListener* listener,m_listeners)
	{
		listener->onMyButtonClicked(this);
	}

	UI::RepaintOpenGL();
}
}//Widget
}//UI
}//MinePlanner