#ifndef MINEPLANNER_UI_ARRANGEUI
#define MINEPLANNER_UI_ARRANGEUI
#include <juce.h>
#include "MinePlanner/BlockSet.hpp"
#include "MinePlanner/UI/Widget/ArrangeWidget.hpp"

namespace MinePlanner{
namespace UI{
class ArrangeUI : public DialogWindow
{
public:
	ArrangeUI();
	~ArrangeUI();
	virtual void closeButtonPressed();

	void startArrange(BlockSet arrangeTarget);
	void finishArrange();
private:
	Widget::ArrangeWidget m_arrangeWidget;
};
}//UI
}//MinePlanner
#endif