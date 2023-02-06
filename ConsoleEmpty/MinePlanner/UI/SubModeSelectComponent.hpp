#ifndef MINEPLANNER_UI_SUBMODESELECTCOMPONENT_HPP
#define MINEPLANNER_UI_SUBMODESELECTCOMPONENT_HPP
#include <juce.h>
#include "MinePlanner/UI/Widget/MyCheckButton.hpp"
#include "MinePlanner/UI/Widget/MyButton.hpp"
namespace MinePlanner{
namespace UI{
class SubModeSelectComponent
	: public Component,
		public Widget::MyButton::MyListener
{
public:
	SubModeSelectComponent();
	void updateDisplay();
	virtual void onMyButtonClicked(Widget::MyButton*);
private:
	Widget::MyButton m_hide;
	Widget::MyButton m_show;
	Widget::MyButton m_replace;
	Widget::MyButton m_copy;
	Widget::MyButton m_cut;
	Widget::MyButton m_paste;
};

SubModeSelectComponent* getSubModeSelectComponent();
}//UI
}//MinePlanner
#endif