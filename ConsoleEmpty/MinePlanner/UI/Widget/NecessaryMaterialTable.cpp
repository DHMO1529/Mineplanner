#include "MinePlanner/UI/Widget/NecessaryMaterialTable.hpp"

#include <fstream>
#include <sstream>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>

#include "MinePlanner/World.hpp"
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"
#include "Platform/FileDialog.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
NecessaryMaterialTable::NecessaryMaterialTable():
 m_table()
,m_tableListBox()
,m_save()
,m_sum()
{
	this->setSize(500,400);
	
	typedef int blockId;
	typedef int blockNum;

	boost::unordered_map<blockId,blockNum> block_count_buf;
	auto count = [&block_count_buf](const Point& point,int blockId,const Pose& pose)
	{
		if(block_count_buf.find(blockId) == block_count_buf.end())
		{
			block_count_buf[blockId] = 1;
		}
		else
		{
			block_count_buf[blockId]++;
		}
	};
	World::instance().for_each(count);

	typedef boost::unordered_map<blockId,blockNum>::value_type type;
	int sum = 0;
	BOOST_FOREACH(const type& val,block_count_buf)
	{
		sum += val.second;
		m_table.push_back(Record(val.first,val.second));
	}

	auto cmp = [](const Record& lhs,const Record& rhs){return lhs.blockId < rhs.blockId;};
	std::sort(m_table.begin(),m_table.end(),cmp);

	m_tableListBox.setModel(this);
	m_tableListBox.getHeader().addColumn(L"ブロック",1,240);
	m_tableListBox.getHeader().addColumn(L"個数",2,60);
	m_tableListBox.getHeader().addColumn(L"補足",3,180);

	this->addAndMakeVisible(&m_tableListBox);
	m_tableListBox.setBoundsInset(BorderSize<int>(0,0,45,0));

	std::stringstream ss;
	ss << "計 " << sum << " block";
	m_sum.setText(string_cast<String,std::string>(ss.str()),false);
	m_sum.setSize(250,30);
	m_sum.setTopLeftPosition(15,m_tableListBox.getHeight() + 10);
	this->addAndMakeVisible(&m_sum);

	m_save.setText(L"　ファイルへ保存　");
	m_save.addListener(this);
	m_save.setTopLeftPosition(320,m_tableListBox.getHeight() + 10);
	this->addAndMakeVisible(&m_save);
}
int NecessaryMaterialTable::getNumRows()
{
	return m_table.size();
}
void NecessaryMaterialTable::paintRowBackground(Graphics& g, int /*rowNumber*/, int /*width*/, int /*height*/, bool rowIsSelected)
{
  if(rowIsSelected)
    g.fillAll(Colours::lightblue);
}
void NecessaryMaterialTable::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
  g.setColour (Colours::black);

	String text;
	if(columnId == 1)
	{
		text = getBlockNameColurmString(rowNumber);
	}
	else if(columnId == 2)
	{
		text = getBlockNumColurmString(rowNumber);
	}
	else
	{
		text = getAdditionalColurmString(rowNumber);
	}
  g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);

  g.setColour(Colours::black.withAlpha (0.2f));
  g.fillRect(width - 1, 0, 1, height);
}
void NecessaryMaterialTable::sortOrderChanged(int newSortColumnId, bool isForwards)
{
	switch(newSortColumnId)
	{
	case 1:
		if(isForwards)
		{
			auto cmp = [](const Record& lhs,const Record& rhs){return lhs.blockId < rhs.blockId;};
			std::sort(m_table.begin(),m_table.end(),cmp);
		}
		else
		{
			auto cmp = [](const Record& lhs,const Record& rhs){return lhs.blockId > rhs.blockId;};
			std::sort(m_table.begin(),m_table.end(),cmp);
		}
		break;
	case 2:
		if(isForwards)
		{
			auto cmp = [](const Record& lhs,const Record& rhs){return lhs.blockNum < rhs.blockNum;};
			std::sort(m_table.begin(),m_table.end(),cmp);
		}
		else
		{
			auto cmp = [](const Record& lhs,const Record& rhs){return lhs.blockNum > rhs.blockNum;};
			std::sort(m_table.begin(),m_table.end(),cmp);
		}
		break;
	}
}
void NecessaryMaterialTable::onMyButtonClicked(MyButton*)
{
	//セーブ
	Platform::FileDialog::Filters filters;
	filters.add("*.txt","必要素材(*.txt)");
	Platform::FileDialog fd("必要素材の保存","必要素材1",filters);

	if(fd.show_save())
	{
		//ロジック
		std::ofstream ofs(fd.get_filename());
		int sum = 0;
		BOOST_FOREACH(const Record& r,m_table)
		{
			sum += r.blockNum;
			const int ONE_STACK_NUM = 64;
			std::string name = DataBase::getNameJp(r.blockId) + "(" + DataBase::getName(r.blockId) + ")";
			ofs << name << " が " << r.blockNum << " 個";

			if(r.blockNum > ONE_STACK_NUM)
			{
				const int STACK_NUM = r.blockNum / ONE_STACK_NUM;
				const int MOD_NUM = r.blockNum % ONE_STACK_NUM;

				ofs << "( " << STACK_NUM << " スタックと " << MOD_NUM << " 個 )";
			}
			ofs << std::endl;
		}
		ofs << std::endl;
		ofs << "合計 " << sum << " 個 必要です" << std::endl;
		ofs << "がんばってね！(｀・ω・´)" << std::endl;
	}
}
//private
String NecessaryMaterialTable::getBlockNameColurmString(int row)
{
	const int id = m_table[row].blockId;
	std::string name = DataBase::getNameJp(id) + "(" + DataBase::getName(id) + ")";
	return string_cast<String,std::string>(name);
}
String NecessaryMaterialTable::getBlockNumColurmString(int row)
{
	const int num = m_table[row].blockNum;
	return String(num) + String(L" 個");
}
String NecessaryMaterialTable::getAdditionalColurmString(int row)
{
	const int ONE_STACK_NUM = 64;
	const int num = m_table[row].blockNum;
	const int STACK_NUM = num / ONE_STACK_NUM;
	const int MOD_NUM = num % ONE_STACK_NUM;

	std::stringstream ss;
	ss << STACK_NUM << " スタックと " << MOD_NUM << " 個";

	return string_cast<String,std::string>(ss.str());
}
}//Widget
}//UI
}//MinePlanner