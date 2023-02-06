#include "MinePlanner/UI/BlockHistory.hpp"

#ifdef Rectangle
#undef Rectangle
#endif
#include <clx/unzip.h>
#include <boost/tuple/tuple.hpp>
#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace UI{
BlockHistory::BlockHistory():
 ListBox()
,ListBoxModel()
,m_image()
,m_selectedBlock()
,m_block_list()
{
	this->setSize(180,120);
	this->setModel(this);

	clx::unzip unzip(ApplicationConstant::ZIP_ARCHIVE,ApplicationConstant::ZIP_PASSWORD);
	clx::unzip::iterator it = unzip.find("BlockTexture.png");
	clx::unzip::stream_type& stream = *it;

	std::vector<char> bin_buffer;
	bin_buffer.reserve(33000);
	while(true)
	{
		char d = stream.get();
		if(stream.eof())
		{
			break;
		}
		bin_buffer.push_back(d);
	}

	m_image = ImageFileFormat::loadFrom(&bin_buffer[0],bin_buffer.size());

	m_selectedBlock.referTo( g_config->getSelectBlockValueObject() );
	m_selectedBlock.addListener(this);
}
int BlockHistory::getNumRows()
{
	return m_block_list.size();
}
void BlockHistory::paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
  if(rowIsSelected)
    g.fillAll (Colours::lightblue);

  g.setColour(Colours::black);
  g.setFont(height * 0.7f);

	const int blockId = m_block_list[ rowNumber ];
	String text = string_cast<String,std::string>( DataBase::getNameJp(blockId) );
  g.drawText(text,
              5, 0, width, height,
              Justification::centredLeft, true);

	int x,y;
	boost::tie(x,y) = DataBase::getMiniPictureXY(blockId);
	g.setColour(Colours::white);
	const int size = 16;//texture
	g.drawImage(m_image,width-height - 10,0,height,height,
		x,y,size,size,false);
}
void BlockHistory::valueChanged(Value& value)
{
	const int blockId = static_cast<int>(value.getValue()) - 1;

	std::vector<int>::iterator it = std::find(m_block_list.begin(),m_block_list.end(),blockId);
	if(it != m_block_list.end())
	{
		//Šù‚É‚ ‚é
		m_block_list.erase(it);
		m_block_list.insert(m_block_list.begin(),blockId);
	}
	else
	{
		m_block_list.insert(m_block_list.begin(),blockId);
		if(m_block_list.size() > 5)
		{
			m_block_list.pop_back();
		}
	}
	this->updateContent();
	int num = m_block_list.size();
	for(int i = 0 ; i < num ; ++i)
	{
		this->repaintRow(i);
	}
}
void BlockHistory::selectedRowsChanged(int lastRowSelected)
{
	const int now_selected = this->getSelectedRow();
	if(now_selected == 0){
		return;
	}
	const int blockId = m_block_list[now_selected];
	std::vector<int>::iterator it = std::find(m_block_list.begin(),m_block_list.end(),blockId);
	m_block_list.erase(it);
	m_block_list.insert(m_block_list.begin(),blockId);
	m_selectedBlock.setValue(blockId + 1);
	this->selectRow(0);

	this->updateContent();
	int num = m_block_list.size();
	for(int i = 0 ; i < num ; ++i)
	{
		this->repaintRow(i);
	}
}
}//UI
}//MinePlanner
