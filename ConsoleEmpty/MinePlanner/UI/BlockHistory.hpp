#ifndef MINEPLANNER_UI_BLOCKHISTORY_HPP
#define MINEPLANNER_UI_BLOCKHISTORY_HPP
#include <vector>
#include <juce.h>
namespace MinePlanner{
namespace UI{
class BlockHistory
	: public ListBox,
    public ListBoxModel,
		public Value::Listener
{
public:
	BlockHistory();

	virtual int getNumRows();
	virtual void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected);
	virtual void valueChanged(Value& value);
	virtual void selectedRowsChanged(int lastRowSelected);
	virtual bool keyPressed(const KeyPress &key){return false;}
private:
	Image m_image;
	Value m_selectedBlock;
	std::vector<int> m_block_list;
};
}//UI
}//MinePlanner
#endif