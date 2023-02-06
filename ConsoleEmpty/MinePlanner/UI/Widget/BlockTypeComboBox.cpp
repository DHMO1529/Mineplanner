#include "MinePlanner/UI/Widget/BlockTypeComboBox.hpp"

#include <boost/foreach.hpp>
#include "MinePlanner/DataBase/DataBase.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
BlockTypeComboBox::BlockTypeComboBox():
 m_label(String::empty,String::empty)
,m_comboBox()
{
	this->setSize(190,20);

	m_label.attachToComponent(&m_comboBox,true);
	this->addAndMakeVisible(&m_label);

	m_comboBox.setSize(130,this->getHeight());
	m_comboBox.setTopRightPosition(this->getWidth(),0);
	m_comboBox.setWantsKeyboardFocus(false);

	std::vector<int> combobox_order = DataBase::getComboboxOrder();
	BOOST_FOREACH(int id,combobox_order)
	{
		if(id == 0)
		{
			m_comboBox.addSeparator();
		}
		String namejp = string_cast<String,std::string>( DataBase::getNameJp(id) );
		m_comboBox.addItem(namejp,id + 1);
	}
	this->addAndMakeVisible(&m_comboBox);
}
void BlockTypeComboBox::setText(const String& text)
{
	m_label.setText(text,false);
}
void BlockTypeComboBox::referTo(const Value& value_int)
{
	m_comboBox.getSelectedIdAsValue().referTo( value_int);
}
int BlockTypeComboBox::getBlockType()const
{
	return m_comboBox.getSelectedId() - 1;
}
void BlockTypeComboBox::setBlockType(int type)
{
	m_comboBox.setSelectedId(type + 1);
}
}//Widget
}//UI
}//MinePlanner