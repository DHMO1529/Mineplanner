#ifndef MINEPLANNER_UI_WIDGET_NECESSARYMATERIALTABLE
#define MINEPLANNER_UI_WIDGET_NECESSARYMATERIALTABLE
#include <vector>
#include <juce.h>
#include "MinePlanner/UI/Widget/MyButton.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
class NecessaryMaterialTable : public Component,
												       public TableListBoxModel,
															 public MyButton::MyListener
{
public:
	NecessaryMaterialTable();

	struct Record
	{
		Record(int id,int num):blockId(id),blockNum(num){}
		int blockId;
		int blockNum;
	};

	virtual int getNumRows();
	virtual void paintRowBackground(Graphics& g, int /*rowNumber*/, int /*width*/, int /*height*/, bool rowIsSelected);
	virtual void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected);
	virtual void sortOrderChanged(int newSortColumnId, bool isForwards);

	virtual void onMyButtonClicked(MyButton*);
private:
	String getBlockNameColurmString(int row);
	String getBlockNumColurmString(int row);
	String getAdditionalColurmString(int row);

	std::vector<Record> m_table;
	TableListBox m_tableListBox;

	Label m_sum;
	Widget::MyButton m_save;
};
}//Widget
}//UI
}//MinePlanner
#endif