#ifndef MINEPLANNER_UI_MYMENUBAR
#define MINEPLANNER_UI_MYMENUBAR

#include <juce.h>
#include <boost/noncopyable.hpp>
namespace MinePlanner{
namespace UI{
/**
* ���j���[�o�[���`
*/
class MyMenuBar : public MenuBarModel,private boost::noncopyable
{
public:
	MyMenuBar(){}
	virtual const StringArray getMenuBarNames();
	virtual const PopupMenu getMenuForIndex(int topLevelMenuIndex,const String& menuName);

	//�C�x���g
	virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex);
};
}//UI
}//MinePlanner
#endif
