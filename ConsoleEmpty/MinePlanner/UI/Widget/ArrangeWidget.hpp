#ifndef MINEPLANNER_UI_WIDGET_ARRANGEWIDGET
#define MINEPLANNER_UI_WIDGET_ARRANGEWIDGET
#include <juce.h>
#include "MinePlanner/UI/Widget/MyNumericUpDown.hpp"
#include "MinePlanner/UI/Widget/MyButton.hpp"
#include "MinePlanner/BlockSet.hpp"

namespace MinePlanner{
namespace UI{
namespace Widget{
class ArrangeWidget : public Component,
											public Widget::MyButton::MyListener,
											public Value::Listener
{
public:
	ArrangeWidget();
	~ArrangeWidget();
	void init(BlockSet target);
	void fin();

  virtual void valueChanged(Value& value);
	virtual void onMyButtonClicked(MyButton* arg);
private:
	TabbedComponent m_tab;

	Widget::MyNumericUpDown m_movex;
	Widget::MyNumericUpDown m_movey;
	Widget::MyNumericUpDown m_movez;
	int m_nowx,m_nowy,m_nowz;
	Value m_moveXValue,m_moveYValue,m_moveZValue;

	Widget::MyButton m_rotateX;
	Widget::MyButton m_rotateY;
	Widget::MyButton m_rotateZ;

	Widget::MyButton m_reverseX;
	Widget::MyButton m_reverseY;
	Widget::MyButton m_reverseZ;

	Widget::MyButton m_decide;

	BlockSet m_target;
};
}//Widget
}//UI
}//MinePlanner
#endif