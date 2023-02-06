#ifndef MINEPLANNER_UI_SUBMODEBASICCOMPONENT_HPP
#define MINEPLANNER_UI_SUBMODEBASICCOMPONENT_HPP
#include <juce.h>
#include "MinePlanner/UI/Widget/EditTypeButton.hpp"
#include "MinePlanner/UI/Widget/BlockTypeComboBox.hpp"
#include "MinePlanner/UI/Widget/MyCheckButton.hpp"
#include "MinePlanner/UI/Widget/MyNumericUpDown.hpp"
#include "MinePlanner/UI/BlockHistory.hpp"
namespace MinePlanner{
namespace UI{
class SubModeBasicComponent
	: public Component
{
public:
	SubModeBasicComponent();

private:
	Widget::EditTypeButton m_editType;
	Widget::BlockTypeComboBox m_blockType;
	BlockHistory m_blockHistory;

	Widget::MyCheckButton m_editGridEnable;
	Widget::MyNumericUpDown m_editGridHeight;
};
}//UI
}//MinePlanner
#endif