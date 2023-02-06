#ifndef MINEPLANNER_UI_SHAPE_CONEDESIGNER_HPP
#define MINEPLANNER_UI_SHAPE_CONEDESIGNER_HPP
#include <juce.h>
#include "MinePlanner/UI/Widget/MyNumericUpDown.hpp"
#include "MinePlanner/UI/Widget/MyButton.hpp"
#include "MinePlanner/UI/Widget/BlockTypeComboBox.hpp"
#include "MinePlanner/UI/Shape/PrevCanvas.hpp"
namespace MinePlanner{
namespace UI{
namespace Shape{
class ConeDesigner
	: public DialogWindow,
	  public Widget::MyButton::MyListener
{
public:
	ConeDesigner();
	~ConeDesigner();

	virtual void closeButtonPressed();
	virtual void onMyButtonClicked(Widget::MyButton*);

	bool show();//Œˆ’è‚È‚çtrue

	int getDiameter()const;
	int getHeight()const;
	int getBlockID()const;
private:
	Component m_component;
	Widget::BlockTypeComboBox m_blockType;
	Widget::MyNumericUpDown m_size;
	Widget::MyNumericUpDown m_height;

	Widget::MyButton m_preview;
	Widget::MyButton m_decide;
	Shape::PrevCanvas m_canvas;
	bool m_decided;
};
}//Shape
}//UI
}//MinePlanner
#endif