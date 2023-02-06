#include "MinePlanner/UI/SubModeBasicComponent.hpp"

#include "MinePlanner/GlobalConfig.hpp"
namespace MinePlanner{
namespace UI{
SubModeBasicComponent::SubModeBasicComponent():
 Component()
,m_editGridHeight(true)
{
	const int LEFT = 0;
	int h = 5;
	//�ҏW�^�C�v
	m_editType.setTopLeftPosition(LEFT,h);
	m_editType.referTo( g_config->getEditTypeValueObject() );
	this->addAndMakeVisible(&m_editType);
	h += m_editType.getHeight();

	//�u���b�N�^�C�v
	h += 10;
	m_blockType.setText(L"�u���b�N");
	m_blockType.setTopLeftPosition(LEFT,h);
	m_blockType.referTo( g_config->getSelectBlockValueObject() );
	this->addAndMakeVisible(&m_blockType);
	h += m_blockType.getHeight();

	//����
	h += 10;
	m_blockHistory.setTopLeftPosition(5,h);
	this->addAndMakeVisible(&m_blockHistory);
	h += m_blockHistory.getHeight();

	//�ҏW�O���b�h
	h += 10;
	m_editGridEnable.setText(L"�ҏW�O���b�h");
	m_editGridEnable.setTopLeftPosition(LEFT,h);
	m_editGridEnable.referTo( g_config->getEditGridEnableValueObject() );
	this->addAndMakeVisible(&m_editGridEnable);
	h += m_editGridEnable.getHeight();
	
	//�ҏW�O���b�h�̍���
	m_editGridHeight.setText(L"�ҏW�O���b�h�̍���");
	m_editGridHeight.setToolTip(L"�V���[�g�J�b�g : �㉺�L�[");
	m_editGridHeight.setTopLeftPosition(LEFT,h);
	m_editGridHeight.referTo( g_config->getEditGridHeightValueObject() );
	this->addAndMakeVisible(&m_editGridHeight);
	h += m_editGridHeight.getHeight();
	h += 5;
}

}//UI
}//MinePlanner