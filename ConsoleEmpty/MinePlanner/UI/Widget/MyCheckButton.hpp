#ifndef MINEPLANNER_UI_WIDGET_MYCHECBUTTON
#define MINEPLANNER_UI_WIDGET_MYCHECBUTTON
#include <juce.h>
namespace MinePlanner{
namespace UI{
namespace Widget{
class MyCheckButton : public Component
{
public:
	MyCheckButton();
	void setText(const String& text);
	void setShortCut(const KeyPress& key);
	void setToolTip(const String& tooltip);

	void referTo(const Value& value_bool);
private:
	ToggleButton m_toggleButton;
};
}//Widget
}//UI
}//MinePlanner
#endif