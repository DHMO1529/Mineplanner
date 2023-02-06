#ifndef MINEPLANNER_UI_EDITMODECOMPONENT
#define MINEPLANNER_UI_EDITMODECOMPONENT
#include <juce.h>
#include <boost/noncopyable.hpp>

#include "MinePlanner/UI/Widget/MyCheckButton.hpp"
#include "MinePlanner/UI/Widget/CameraModeButton.hpp"
#include "MinePlanner/UI/Widget/MyButton.hpp"
#include "MinePlanner/UI/SubModeTab.hpp"
namespace MinePlanner{
namespace UI{
/**
* ビューモード時のインターフェース
*/
class EditModeComponent
	: public Component,
		public Widget::MyButton::MyListener,
	  public boost::noncopyable
{
public:
	EditModeComponent();
	virtual void paint(Graphics &g);

	virtual void onMyButtonClicked(Widget::MyButton*);
private:
	Widget::MyCheckButton m_blockContourEnable;
	Widget::MyCheckButton m_lightEnable;
	Widget::CameraModeButton m_cameraMode;
	Widget::MyButton m_cameraReset;

	int m_separatorHeight;
	SubModeTab m_subModeTab;

	Widget::MyButton m_undo;
	Widget::MyButton m_redo;
};
}//UI
}//MinePlanner
#endif