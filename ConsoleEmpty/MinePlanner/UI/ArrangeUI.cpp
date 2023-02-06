#include "MinePlanner/UI/ArrangeUI.hpp"
#include "MinePlanner/Operation/ArrangementManager.hpp"

#include "MinePlanner/UI/MainWindow.hpp"
namespace MinePlanner{
namespace UI{
ArrangeUI::ArrangeUI():
 DialogWindow(L"”z’u",Colours::lightgrey,false)
{
	this->setContentOwned(&m_arrangeWidget,true);
	this->setAlwaysOnTop(true);
}
ArrangeUI::~ArrangeUI()
{
	this->setVisible(false);
}
void ArrangeUI::closeButtonPressed()
{
	this->setVisible(false);

	m_arrangeWidget.fin();
	g_pArrangementManager()->arrangeFinish();
}
void ArrangeUI::startArrange(BlockSet arrangeTarget)
{
	m_arrangeWidget.init(arrangeTarget);

	const int x = UI::getWindowX();
	const int y = UI::getWindowY();
	this->setTopLeftPosition(x+200,y+50);
	this->setVisible(true);
}
void ArrangeUI::finishArrange()
{
	this->setVisible(false);
	m_arrangeWidget.fin();
}
}//UI
}//MinePlanner
