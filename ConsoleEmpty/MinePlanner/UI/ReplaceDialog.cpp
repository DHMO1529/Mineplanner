#include "MinePlanner/UI/ReplaceDialog.hpp"

#include <map>
#include <boost/foreach.hpp>

#include "MinePlanner/UI/MainWindow.hpp"
#include "MinePlanner/Operation/SelectionManager.hpp"
#include "MinePlanner/World.hpp"
#include "MinePlanner/GlobalConfig.hpp"
namespace MinePlanner{
namespace UI{
inline int get_most_block(PointSet selected_points)
{
	typedef int BlockType;
	std::map<BlockType,int> count;
	auto check = [&count](const Point& point)
	{
		if(World::instance().isExist(point))
		{
			int type = World::instance().getBlockID(point);
			if(count.find(type) != count.end())
			{
				count[type]++;
			}
			else
			{
				count[type] = 1;
			}
		}
	};
	selected_points.for_each(check);

	int max = 0;
	BlockType type = 0;
	BOOST_FOREACH(const auto& v,count)
	{
		if(max < v.second)
		{
			max = v.second;
			type = v.first;
		}
	}
	return type;
}
ReplaceDialog::ReplaceDialog():
 DialogWindow(L"一斉置換",Colours::lightgrey,false)
,m_component()
,m_blockTypeFrom()
,m_fill()
,m_isFill()
,m_blockTypeTo()
,m_delete()
,m_isDelete()
,m_decide()
,m_decided(false)
{
	m_component.setSize(200,180);

	m_isFill.setValue((bool)false);
	m_isFill.addListener(this);
	m_isDelete.setValue((bool)false);
	m_isDelete.addListener(this);

	int h = 0;

	h += 10;
	m_blockTypeFrom.setText(L"置換対象");
	m_blockTypeFrom.setTopLeftPosition(0,h);
	m_component.addAndMakeVisible(&m_blockTypeFrom);
	h += m_blockTypeFrom.getHeight();

	h += 10;
	m_fill.setText(L"塗りつぶし");
	m_fill.setTopLeftPosition(40,h);
	m_fill.referTo( m_isFill );
	m_component.addAndMakeVisible(&m_fill);
	h += m_fill.getHeight();

	h += 10;
	m_blockTypeTo.setText(L"置換後　");
	m_blockTypeTo.setTopLeftPosition(0,h);
	m_component.addAndMakeVisible(&m_blockTypeTo);
	h += m_blockTypeTo.getHeight();

	h += 10;
	m_delete.setText(L"削除する");
	m_delete.setTopLeftPosition(40,h);
	m_delete.referTo( m_isDelete );
	m_component.addAndMakeVisible(&m_delete);
	h += m_fill.getHeight();
	
	h += 15;
	m_decide.setText(L" 実行 ");
	m_decide.addListener(this);
	m_decide.setTopLeftPosition(60,h);
	m_component.addAndMakeVisible(&m_decide);

	this->setContentOwned(&m_component,true);

	//ここに来るのは必ず選択されてる
	PointSet selected_points = g_pSelectionManager()->getSelectedPoints();

	m_blockTypeFrom.setBlockType( get_most_block(selected_points) );
	m_blockTypeTo.setBlockType( g_config->getSelectBlock() );
	valueChanged(m_isFill);
}
ReplaceDialog::~ReplaceDialog()
{
}
void ReplaceDialog::closeButtonPressed()
{
	this->setVisible(false);
}
void ReplaceDialog::onMyButtonClicked(Widget::MyButton*)
{
	m_decided = true;
	this->setVisible(false);
}
void ReplaceDialog::show()
{
	const int x = UI::getWindowX();
	const int y = UI::getWindowY();
	this->setTopLeftPosition(x+200,y+100);

	this->runModalLoop();
}
bool ReplaceDialog::isDecided()const
{
	return m_decided;
}
bool ReplaceDialog::isFill()const
{
	return static_cast<bool>(m_isFill.getValue());
}
bool ReplaceDialog::isDelete()const
{
	return static_cast<bool>(m_isDelete.getValue());
}
int ReplaceDialog::getFrom()const
{
	return m_blockTypeFrom.getBlockType();
}
int ReplaceDialog::getTo()const
{
	return m_blockTypeTo.getBlockType();
}
void ReplaceDialog::valueChanged(Value& value)
{
	m_blockTypeFrom.setEnabled( !isFill() );
	m_blockTypeTo.setEnabled( !isDelete() );
}
}//UI
}//MinePlanner