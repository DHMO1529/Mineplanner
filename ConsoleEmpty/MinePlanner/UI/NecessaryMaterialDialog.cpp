#include "MinePlanner/UI/NecessaryMaterialDialog.hpp"
#include "MinePlanner/UI/MainWindow.hpp"
namespace MinePlanner{
namespace UI{
NecessaryMaterialDialog::NecessaryMaterialDialog():
 DialogWindow(L"•K—v‘fÞ",Colours::lightgrey,false)
,m_table()
{
	this->setContentOwned(&m_table,true);
}
NecessaryMaterialDialog::~NecessaryMaterialDialog()
{
}
void NecessaryMaterialDialog::closeButtonPressed()
{
	this->setVisible(false);
}
void NecessaryMaterialDialog::show()
{
	const int x = UI::getWindowX();
	const int y = UI::getWindowY();
	this->setTopLeftPosition(x+200,y+100);

	this->runModalLoop();
}
}//UI
}//MinePlanner