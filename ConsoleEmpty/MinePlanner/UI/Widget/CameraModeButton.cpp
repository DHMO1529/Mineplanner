#include "MinePlanner/UI/Widget/CameraModeButton.hpp"

#include "MinePlanner/GlobalConfigEnumDef.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
CameraModeButton::CameraModeButton():
 m_normal(L"通常カメラ")
,m_ortho(L"平行カメラ")
,m_mode()
{
	this->setSize(160,25);

	const int BUTTON_WIDTH = 80;

	m_normal.setClickingTogglesState(true);
	m_normal.setBounds(0,0,BUTTON_WIDTH,25);
	m_normal.setConnectedEdges(Button::ConnectedOnRight);
	m_normal.setColour(TextButton::buttonColourId,Colours::lightcyan);
	m_normal.setColour(TextButton::buttonOnColourId,Colours::cyan);
	m_normal.addListener(this);
	this->addAndMakeVisible(&m_normal);

	m_ortho.setClickingTogglesState(true);
	m_ortho.setBounds(BUTTON_WIDTH,0,BUTTON_WIDTH,25);
	m_ortho.setConnectedEdges(Button::ConnectedOnLeft);
	m_ortho.setColour(TextButton::buttonColourId,Colours::lightcyan);
	m_ortho.setColour(TextButton::buttonOnColourId,Colours::cyan);
	m_ortho.addListener(this);
	this->addAndMakeVisible(&m_ortho);

	{
		const int RADIO_GROUP_ID = String(L"ティロフィナーレ").hashCode();
		m_normal.setRadioGroupId(RADIO_GROUP_ID);
		m_ortho.setRadioGroupId(RADIO_GROUP_ID);
	}
}
void CameraModeButton::referTo(const Value& value_int)
{
	m_mode.referTo(value_int);
	valueChanged(m_mode);
}
void CameraModeButton::buttonClicked(Button* button)
{
	int val = -1;
	if(m_normal.getToggleState())
	{
		val = CAMERA_MODE_NORMAL;
	}
	else
	{
		val = CAMERA_MODE_ORTHO;
	}
	m_mode.setValue( val );
}
void CameraModeButton::valueChanged(Value& value)
{
	int val = static_cast<int>(value.getValue());
	if(val == CAMERA_MODE_NORMAL)
	{
		m_normal.setToggleState(true,false);
	}
	else
	{
		m_ortho.setToggleState(true,false);
	}
}
void CameraModeButton::enablementChanged()
{
	valueChanged(m_mode);
}
}//Widget
}//UI
}//MinePlanner