#include "MinePlanner/UI/SubModeTab.hpp"

#include "MinePlanner/UI/SubModeBasicComponent.hpp"
#include "MinePlanner/UI/SubModeSelectComponent.hpp"
namespace MinePlanner{
namespace UI{
SubModeTab::SubModeTab():
 TabbedComponent(TabbedButtonBar::TabsAtTop)
{
	this->setSize(190,340);

	this->addTab(L"Šî–{",Colours::aliceblue,new SubModeBasicComponent(),true);
	this->addTab(L"‘I‘ð",Colours::azure,new SubModeSelectComponent(),true);

	m_tab_index.setValue(0);
	m_tab_index.addListener(this);
}
void SubModeTab::referTo(const Value& value)
{
	m_tab_index.referTo(value);
	valueChanged(m_tab_index);
}
void SubModeTab::currentTabChanged(int newCurrentTabIndex,const String &newCurrentTabName)
{
	m_tab_index.setValue(newCurrentTabIndex);
}
void SubModeTab::valueChanged(Value &value)
{
	this->setCurrentTabIndex(static_cast<int>(m_tab_index.getValue()),false);
}
}//UI
}//MinePlanner