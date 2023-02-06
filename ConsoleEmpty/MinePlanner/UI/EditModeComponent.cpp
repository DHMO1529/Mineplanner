#include "MinePlanner/UI/EditModeComponent.hpp"


#include "MinePlanner/Operation/EditManager.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/UI/RepaintOpenGL.hpp"

#include "MinePlanner/graphic/graphic.hpp"
#include "MinePlanner/Operation/BatchWork.hpp"

namespace MinePlanner{
namespace UI{
EditModeComponent::EditModeComponent():
 m_blockContourEnable()
,m_lightEnable()
,m_cameraMode()
,m_cameraReset()
,m_separatorHeight(0)
,m_subModeTab()
,m_undo()
,m_redo()
{
	this->setBounds(0,0,200,530);
	const int LEFT = 5;
	int h = 5;

	//�u���b�N�̗֊s
	m_blockContourEnable.setText(L"�u���b�N�̗֊s");
	m_blockContourEnable.setTopLeftPosition(LEFT,h);
	m_blockContourEnable.referTo( g_config->getBlockContourEnableValueObject() );
	this->addAndMakeVisible(&m_blockContourEnable);
	h += m_blockContourEnable.getHeight();

	//���C�g
	m_lightEnable.setText(L"���C�g");
	m_lightEnable.setTopLeftPosition(LEFT,h);
	m_lightEnable.referTo( g_config->getLightEnableValueObject() );
	this->addAndMakeVisible(&m_lightEnable);
	h += m_lightEnable.getHeight();

	//�J�������[�h
	m_cameraMode.setTopLeftPosition(20,h);
	m_cameraMode.referTo( g_config->getCameraModeValueObject() );
	this->addAndMakeVisible(&m_cameraMode);
	h += m_cameraMode.getHeight();
  h += 5;

	//�J�������Z�b�g
	m_cameraReset.setText(L"�J�������Z�b�g");
	m_cameraReset.setTopLeftPosition(32,h);
	m_cameraReset.addListener(this);
	this->addAndMakeVisible(&m_cameraReset);
	h += m_cameraReset.getHeight();

	h += 5;
	m_separatorHeight = h;
	h += 5;

	//�T�u���[�h�^�u
	m_subModeTab.setTopLeftPosition(LEFT,h);
	m_subModeTab.referTo( g_config->getSubModeValueObject() );
	this->addAndMakeVisible(&m_subModeTab);
	h += m_subModeTab.getHeight();

	//��蒼��
	int unredo_height = this->getHeight()-m_redo.getHeight()-10;

	m_redo.setText(L"��蒼��");
	m_redo.setToolTip(L"�V���[�g�J�b�g : Ctrl + Y");
	m_redo.setTopLeftPosition(LEFT,unredo_height);
	m_redo.addListener(this);
	m_redo.addShortCut(KeyPress('Y',ModifierKeys::ctrlModifier,L''));
	this->addAndMakeVisible(&m_redo);

	unredo_height -= 5;

	//���ɖ߂�
	m_undo.setText(L"���ɖ߂�");
	m_undo.setToolTip(L"�V���[�g�J�b�g : Ctrl + Z");
	m_undo.setTopLeftPosition(LEFT,unredo_height - m_undo.getHeight());
	m_undo.addListener(this);
	m_undo.addShortCut(KeyPress('Z',ModifierKeys::ctrlModifier,L''));
	this->addAndMakeVisible(&m_undo);
	h += m_undo.getHeight();
	h += 5;
}
void EditModeComponent::paint(Graphics &g)
{
	Colour c = Colours::lightgreen;
	g.fillAll(c.withAlpha(0.4f));
	g.setColour(Colours::green);
	g.drawRect(0,0,this->getWidth(),this->getHeight(),3);

	const float Y = static_cast<float>( m_separatorHeight );
	g.drawLine(0,Y,static_cast<float>(this->getWidth()),Y);
}
void EditModeComponent::onMyButtonClicked(Widget::MyButton* arg)
{
	if(&m_cameraReset == arg)
	{
		g_camera->reset();
	}
	else if(&m_undo == arg)
	{
		g_pEditManager()->undo();
	}
	else if(&m_redo == arg)
	{
		g_pEditManager()->redo();
	}

	RepaintOpenGL();
}
}//UI
}//MinePlanner