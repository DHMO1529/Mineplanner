#include "MinePlanner/UI/Widget/EditTypeButton.hpp"
#include <boost/cast.hpp>
#include "MinePlanner/GlobalConfigEnumDef.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
EditTypeButton::EditTypeButton():
 m_label(String::empty,L"編集タイプ")
,m_add(L"追加")
,m_swap(L"置換")
,m_delete(L"削除")
,m_type()
{
	this->setSize(200,50);

	const int EDITTYPE_BUTTON_W = 60;
	const int LEFT = 4;

	m_label.setBounds(0,0,120,25);
	this->addAndMakeVisible(&m_label);

	int h = 25;

	const String tooltip = L"ショートカットキー : 1,2,3キー";
	m_add.setTooltip(tooltip);
	m_add.setClickingTogglesState(true);
	m_add.setBounds(LEFT,h,EDITTYPE_BUTTON_W,25);
	m_add.setConnectedEdges(Button::ConnectedOnRight);
	m_add.setColour(TextButton::buttonColourId,Colours::lightcyan);
	m_add.setColour(TextButton::buttonOnColourId,Colours::cyan);
	m_add.addListener(this);
	this->addAndMakeVisible(&m_add);

	m_swap.setTooltip(tooltip);
	m_swap.setClickingTogglesState(true);
	m_swap.setBounds(LEFT + EDITTYPE_BUTTON_W,h,EDITTYPE_BUTTON_W,25);
	m_swap.setConnectedEdges(Button::ConnectedOnRight | Button::ConnectedOnLeft);
	m_swap.setColour(TextButton::buttonColourId,Colours::lightcyan);
	m_swap.setColour(TextButton::buttonOnColourId,Colours::cyan);
	m_swap.addListener(this);
	this->addAndMakeVisible(&m_swap);

	m_delete.setTooltip(tooltip);
	m_delete.setClickingTogglesState(true);
	m_delete.setBounds(LEFT + EDITTYPE_BUTTON_W * 2,h,EDITTYPE_BUTTON_W,25);
	m_delete.setConnectedEdges(Button::ConnectedOnLeft);
	m_delete.setColour(TextButton::buttonColourId,Colours::lightcyan);
	m_delete.setColour(TextButton::buttonOnColourId,Colours::cyan);
	m_delete.addListener(this);
	this->addAndMakeVisible(&m_delete);

	{
		const int RADIO_GROUP_ID = String(L"ほむほむあいしてる").hashCode();
		m_add.setRadioGroupId(RADIO_GROUP_ID);
		m_swap.setRadioGroupId(RADIO_GROUP_ID);
		m_delete.setRadioGroupId(RADIO_GROUP_ID);
	}

	//ショートカットキー設定
	m_add.addShortcut(KeyPress('1'));
	m_swap.addShortcut(KeyPress('2'));
	m_delete.addShortcut(KeyPress('3'));

	m_type.addListener(this);
}
void EditTypeButton::referTo(const Value& value_int)
{
	m_type.referTo(value_int);
	valueChanged(m_type);
}
void EditTypeButton::valueChanged(Value& value)
{
	int type = static_cast<int>(value.getValue());
	if(type == EDITTYPE_ADD)
	{
		m_add.setToggleState(true,false);
	}
	if(type == EDITTYPE_SWAP)
	{
		m_swap.setToggleState(true,false);
	}
	if(type == EDITTYPE_DELETE)
	{
		m_delete.setToggleState(true,false);
	}
}
void EditTypeButton::buttonClicked(Button* button)
{
	TextButton* arg = boost::polymorphic_downcast<TextButton*>(button);

	int editType = -1;

	if(&m_add == arg)
	{
		editType = EDITTYPE_ADD;
	}
	else if(&m_swap == arg)
	{
		editType = EDITTYPE_SWAP;
	}
	else if(&m_delete == arg)
	{
		editType = EDITTYPE_DELETE;
	}
	else
	{
		assert(0);
	}
	m_type.setValue(editType);
}
}//Widget
}//UI
}//MinePlanner