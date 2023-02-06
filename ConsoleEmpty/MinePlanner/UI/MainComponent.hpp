#ifndef MINEPLANNER_UI_MAINCOMPONENT
#define MINEPLANNER_UI_MAINCOMPONENT
#include <vector>
#include <juce.h>
#include <boost/noncopyable.hpp>

#include "MinePlanner/UI/ViewModeComponent.hpp"
#include "MinePlanner/UI/EditModeComponent.hpp"
#include "MinePlanner/UI/Widget/OpenglScreen.hpp"
#include "MinePlanner/UI/Widget/ModeButton.hpp"

#include "MinePlanner/UI/EventHandler/Functions.hpp"
namespace MinePlanner{
namespace UI{
/**
* コンポーネントのルートオブジェクト
*/
class MainComponent
	: public Component,
		public Value::Listener,
		public Timer,
		public FileDragAndDropTarget,
		private boost::noncopyable
{
public:
	MainComponent();
  virtual void resized();

	virtual void timerCallback();
	
	void filesDropped(const StringArray &files, int x, int y);
	bool isInterestedInFileDrag (const StringArray &files);

	virtual void valueChanged(Value& value);//mode
private:
	Widget::ModeButton m_modeButton;
	Value m_mode;

	ViewModeComponent m_viewModeComponent;
	EditModeComponent m_editModeComponent;
	Widget::OpenGLScreen m_openglScreen;
	Label m_fpsLabel;
};
}//UI
}//MinePlanner
#endif