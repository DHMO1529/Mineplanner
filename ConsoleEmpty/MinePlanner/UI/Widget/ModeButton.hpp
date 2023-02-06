#ifndef MINEPLANNER_UI_WIDGET_MODEBUTTON
#define MINEPLANNER_UI_WIDGET_MODEBUTTON
#include <juce.h>
namespace MinePlanner{
namespace UI{
namespace Widget{
class ModeButton
	: public Component,
		public Button::Listener,
		public Value::Listener
{
public:
	ModeButton();
	void referTo(const Value& value_int);//int

	virtual void buttonClicked(Button* button);
	virtual void valueChanged(Value& value);
private:
	TextButton m_ViewButton;
	TextButton m_EditButton;
	Value m_mode;
};
}//Widget
}//UI
}//MinePlanner
#endif