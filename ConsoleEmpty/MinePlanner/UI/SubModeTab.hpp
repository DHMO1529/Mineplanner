#ifndef MINEPLANNER_UI_SUBMODETAB_HPP
#define MINEPLANNER_UI_SUBMODETAB_HPP
#include <juce.h>
#include <boost/scoped_ptr.hpp>
namespace MinePlanner{
namespace UI{
class SubModeTab
	: public TabbedComponent,
	  public Value::Listener
{
public:
	SubModeTab();
	void referTo(const Value& value);
	virtual void currentTabChanged(int newCurrentTabIndex,const String &newCurrentTabName);
	virtual void valueChanged(Value &value);
private:
	Value m_tab_index;
};
}//UI
}//MinePlanner
#endif