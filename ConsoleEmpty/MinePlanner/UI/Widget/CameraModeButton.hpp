#ifndef MINEPLANNER_UI_WIDGET_CAMERAMODEBUTTON
#define MINEPLANNER_UI_WIDGET_CAMERAMODEBUTTON
#include <juce.h>
namespace MinePlanner{
namespace UI{
namespace Widget{
class CameraModeButton
	: public Component,
		public Button::Listener,
		public Value::Listener
{
public:
	CameraModeButton();

	void referTo(const Value& value_int);

	virtual void buttonClicked(Button* button);
	virtual void valueChanged(Value& value);
	virtual void enablementChanged();
private:
	TextButton m_normal;
	TextButton m_ortho;
	Value m_mode;//int
};
}//Widget
}//UI
}//MinePlanner
#endif