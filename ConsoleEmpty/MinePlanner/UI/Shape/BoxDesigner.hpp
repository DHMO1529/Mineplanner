#ifndef MINEPLANNER_UI_SHAPE_BOXDESIGNER_HPP
#define MINEPLANNER_UI_SHAPE_BOXDESIGNER_HPP
#include <juce.h>
#include "MinePlanner/UI/Widget/MyNumericUpDown.hpp"
#include "MinePlanner/UI/Widget/MyButton.hpp"
#include "MinePlanner/UI/Widget/BlockTypeComboBox.hpp"
#include "MinePlanner/UI/Shape/PrevCanvas.hpp"
namespace MinePlanner{
namespace UI{
namespace Shape{
class BoxDesigner
	: public DialogWindow,
	  public Widget::MyButton::MyListener
{
public:
	BoxDesigner();
	~BoxDesigner();

	virtual void closeButtonPressed();
	virtual void onMyButtonClicked(Widget::MyButton*);

	bool show();//Œˆ’è‚È‚çtrue

	int getxsize()const;
	int getysize()const;
	int getzsize()const;
	int getBlockID()const;
private:
	Component m_component;
	Widget::BlockTypeComboBox m_blockType;
	Widget::MyNumericUpDown m_sizex;
	Widget::MyNumericUpDown m_sizey;
	Widget::MyNumericUpDown m_sizez;

	Widget::MyButton m_preview;
	Widget::MyButton m_decide;
	Shape::PrevCanvas m_canvas;
	bool m_decided;
};
}//Shape
}//UI
}//MinePlanner
#endif