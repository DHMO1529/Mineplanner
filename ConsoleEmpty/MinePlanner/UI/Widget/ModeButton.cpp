#include "MinePlanner/UI/Widget/ModeButton.hpp"

#include "MinePlanner/GlobalConfigEnumDef.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
ModeButton::ModeButton():
 m_ViewButton(L"ビュー")
,m_EditButton(L"エディット")
{
	this->setSize(200,40);

	const int WIDTH = 100;
	m_ViewButton.setClickingTogglesState(true);
	m_ViewButton.setBounds(0,10,WIDTH,25);
	m_ViewButton.setConnectedEdges(Button::ConnectedOnRight);
	m_ViewButton.setColour(TextButton::buttonColourId,Colours::lightblue);
	m_ViewButton.setColour(TextButton::buttonOnColourId,Colours::blue);
	m_ViewButton.addListener(this);
		
	m_EditButton.setClickingTogglesState(true);
	m_EditButton.setBounds(WIDTH,10,WIDTH,25);
	m_EditButton.setConnectedEdges(Button::ConnectedOnLeft);
	m_EditButton.setColour(TextButton::buttonColourId,Colours::lightgreen);
	m_EditButton.setColour(TextButton::buttonOnColourId,Colours::green);
	m_EditButton.addListener(this);
	{
		const int RADIO_GROUP_ID = String(L"まどかあいしてる").hashCode();
		m_ViewButton.setRadioGroupId(RADIO_GROUP_ID);
		m_EditButton.setRadioGroupId(RADIO_GROUP_ID);
	}
	this->addAndMakeVisible(&m_ViewButton);
	this->addAndMakeVisible(&m_EditButton);

	m_ViewButton.setName(L"ModeButton");
	m_EditButton.setName(L"ModeButton");

	m_mode.addListener(this);
}
void ModeButton::buttonClicked(Button* button)
{
	int value = -1;
	if(m_ViewButton.getToggleState())
	{
		value = MODE_VIEW;
	}
	else
	{
		value = MODE_EDIT;
	}
	m_mode.setValue(value);
}
void ModeButton::valueChanged(Value& value)
{
	int val = static_cast<int>(value.getValue());
	if(val == MODE_VIEW)
	{
		m_ViewButton.setToggleState(true,false);
	}
	else
	{
		m_EditButton.setToggleState(true,false);
	}
}
void ModeButton::referTo(const Value& value_int)
{
	m_mode.referTo(value_int);
	valueChanged(m_mode);
}
}//Widget
}//UI
}//MinePlner