#include "MinePlanner/UI/MainComponent.hpp"
#include <boost/cast.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/unordered_set.hpp>
#include <boost/assign.hpp>

#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"

#include "MinePlanner/graphic/graphic.hpp"

#include "MinePlanner/UI/RepaintOpenGL.hpp"
#include "MinePlanner/string_cast.hpp"

namespace MinePlanner{
namespace UI{
MainComponent::MainComponent():
 m_modeButton()
,m_mode()
,m_viewModeComponent()
,m_editModeComponent()
,m_openglScreen()
,m_fpsLabel(String::empty,L"FPS:0")
{
	this->setSize(ApplicationConstant::WINDOW_WIDTH,ApplicationConstant::WINDOW_HEIGHT);

	this->startTimer(1000);

	int h = 0;

	m_modeButton.setTopLeftPosition(0,0);
	m_modeButton.referTo( g_config->getModeValueObject() );
	m_mode.referTo( g_config->getModeValueObject() );
	m_mode.addListener(this);
	this->addAndMakeVisible(&m_modeButton);
	h += m_modeButton.getHeight();

	//ビューコンポーネント
	m_viewModeComponent.setBounds(0,h,m_viewModeComponent.getWidth(),m_viewModeComponent.getHeight());
	this->addAndMakeVisible(&m_viewModeComponent);

	//エディットコンポーネント
	m_editModeComponent.setBounds(0,h,m_editModeComponent.getWidth(),m_editModeComponent.getHeight());
	this->addAndMakeVisible(&m_editModeComponent);

	this->addAndMakeVisible(&m_openglScreen);

	m_fpsLabel.setSize(200,30);
	this->addAndMakeVisible(&m_fpsLabel);

	valueChanged(g_config->getModeValueObject());
}
void MainComponent::resized()
{
	m_openglScreen.setBounds(200,0,this->getWidth()-200,this->getHeight());
	m_fpsLabel.setTopLeftPosition(5,this->getHeight() - 30);
}
void MainComponent::valueChanged(Value& value)
{
	if(g_config->getMode() == MODE_VIEW)
	{
		m_viewModeComponent.setVisible(true);
		m_viewModeComponent.setEnabled(true);
		m_editModeComponent.setVisible(false);
		m_editModeComponent.setEnabled(false);
	}
	else
	{
		m_viewModeComponent.setVisible(false);
		m_viewModeComponent.setEnabled(false);
		m_editModeComponent.setVisible(true);
		m_editModeComponent.setEnabled(true);
	}
}
void MainComponent::timerCallback()
{
	m_fpsLabel.setText(String::formatted("FPS:%d",graphic::getFps()),false);
}

//ドラッグアンドドロップのサポート
void MainComponent::filesDropped(const StringArray &files, int x, int y)
{
	EventHandler::filesDropped(files,x,y);
}
bool MainComponent::isInterestedInFileDrag(const StringArray &files)
{
	return EventHandler::isInterestedInFileDrag(files);
}
}//UI
}//MinePlanner