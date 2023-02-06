#ifndef MINEPLANNER_UI_WIDGET_BLOCKTYPECOMBOBOX
#define MINEPLANNER_UI_WIDGET_BLOCKTYPECOMBOBOX
#include <juce.h>
namespace MinePlanner{
namespace UI{
namespace Widget{
class BlockTypeComboBox
	: public Component
{
public:
	BlockTypeComboBox();
	void setText(const String& text);
	void referTo(const Value& value_int);
	void setBlockType(int type);
	int getBlockType()const;
private:
	Label m_label;
	ComboBox m_comboBox;
};
}//Widget
}//UI
}//MinePlanner
#endif