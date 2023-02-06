#ifndef MINEPLANNER_UI_VIEWMODECOMPONENT
#define MINEPLANNER_UI_VIEWMODECOMPONENT
#include <juce.h>
#include <boost/noncopyable.hpp>
#include "MinePlanner/UI/Widget/MyCheckButton.hpp"
#include "MinePlanner/UI/Widget/MyNumericUpDown.hpp"
#include "MinePlanner/UI/Widget/MyButton.hpp"
#include "MinePlanner/UI/Widget/CameraModeButton.hpp"
namespace MinePlanner{
namespace UI{
/**
* ビューモード時のインターフェース
*/
class ViewModeComponent
	: public Component,
		public Value::Listener,
		public Widget::MyButton::MyListener,
		private boost::noncopyable
{
public:
	ViewModeComponent();
	~ViewModeComponent();

	virtual void paint(Graphics &g);
	virtual void valueChanged(Value& value);
	virtual void onMyButtonClicked(Widget::MyButton*);
private:
	Widget::MyCheckButton m_sliceModeEnable;
	Value m_sliceModeEnableValue;
	Widget::MyNumericUpDown m_sliceHeight;
 
	Widget::MyCheckButton m_upBlockEnable;
	Widget::MyCheckButton m_downBlockEnable;
	Widget::MyCheckButton m_blockContourEnable;
	Widget::MyCheckButton m_lightEnable;

	Widget::CameraModeButton m_cameraMode;
	Widget::MyButton m_cameraReset;
};
}//UI
}//MinePlanner
#endif