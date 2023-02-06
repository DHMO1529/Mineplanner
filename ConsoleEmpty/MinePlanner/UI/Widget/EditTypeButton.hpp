#ifndef MINEPLANNER_UI_WIDGET_EDITTYPEBUTTON
#define MINEPLANNER_UI_WIDGET_EDITTYPEBUTTON
#include <juce.h>
namespace MinePlanner{
namespace UI{
namespace Widget{
class EditTypeButton
	: public Component,
		public Button::Listener,
		public Value::Listener				 
{
public:
	EditTypeButton();

	void referTo(const Value& value_int);

	//内部コールバック
	virtual void buttonClicked(Button* button);
	virtual void valueChanged(Value& value);
private:
	Label m_label;
	TextButton m_add;
	TextButton m_swap;
	TextButton m_delete;
	Value m_type;
};
}//Widget
}//UI
}//MinePlanner
#endif