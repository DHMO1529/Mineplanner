#ifndef MINEPLANNER_UI_NECESSARYMATERIALDIALOG
#define MINEPLANNER_UI_NECESSARYMATERIALDIALOG
#include <juce.h>
#include "MinePlanner/UI/Widget/NecessaryMaterialTable.hpp"
namespace MinePlanner{
namespace UI{
class NecessaryMaterialDialog : public DialogWindow
{
public:
	NecessaryMaterialDialog();
	~NecessaryMaterialDialog();

	virtual void closeButtonPressed();
	void show();
private:
	Widget::NecessaryMaterialTable m_table;
};
}//UI
}//MinePlanner
#endif