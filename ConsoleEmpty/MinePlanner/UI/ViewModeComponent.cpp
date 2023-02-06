#include "MinePlanner/UI/ViewModeComponent.hpp"

#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/UI/RepaintOpenGL.hpp"
#include "MinePlanner/graphic/graphic.hpp"

namespace MinePlanner{
namespace UI{
ViewModeComponent::ViewModeComponent():
 m_sliceModeEnable()
,m_sliceModeEnableValue()
,m_sliceHeight(true)
,m_upBlockEnable()
,m_downBlockEnable()
,m_blockContourEnable()
,m_lightEnable()
,m_cameraMode()
,m_cameraReset()
{
	this->setBounds(0,0,200,250);

	const int LEFT = 5;
	int h = 5;

	//スライス表示
	m_sliceModeEnable.setText(L"スライス表示");
	m_sliceModeEnable.setToolTip(L"ショートカット : スペースキー");
	m_sliceModeEnable.setTopLeftPosition(LEFT,h);
	m_sliceModeEnable.setShortCut(KeyPress(KeyPress::spaceKey));
	m_sliceModeEnable.referTo( g_config->getSliceModeEnableValueObject() );
	m_sliceModeEnableValue.referTo( g_config->getSliceModeEnableValueObject() );
	m_sliceModeEnableValue.addListener(this);
	this->addAndMakeVisible(&m_sliceModeEnable);
	h += m_sliceModeEnable.getHeight();

	//スライスの高さ
	m_sliceHeight.setText(L"スライスの高さ");
	m_sliceHeight.setTopLeftPosition(LEFT,h);
	m_sliceHeight.setToolTip(L"ショートカット : 上下キー");
	m_sliceHeight.referTo( g_config->getSliceHeightValueObject() );
	this->addAndMakeVisible(&m_sliceHeight);
	h += m_sliceHeight.getHeight();

	//上ブロック描画
	m_upBlockEnable.setText(L"上ブロック表示");
	m_upBlockEnable.setTopLeftPosition(LEFT,h);
	m_upBlockEnable.referTo( g_config->getUpBlockEnableValueObject() );
	this->addAndMakeVisible(&m_upBlockEnable);
	h += m_upBlockEnable.getHeight();
	//下ブロック描画
	m_downBlockEnable.setText(L"下ブロック表示");
	m_downBlockEnable.setTopLeftPosition(LEFT,h);
	m_downBlockEnable.referTo( g_config->getDownBlockEnableValueObject() );
	this->addAndMakeVisible(&m_downBlockEnable);
	h += m_downBlockEnable.getHeight();

	//ブロックの輪郭
	m_blockContourEnable.setText(L"ブロックの輪郭");
	m_blockContourEnable.setTopLeftPosition(LEFT,h);
	m_blockContourEnable.referTo( g_config->getBlockContourEnableValueObject() );
	this->addAndMakeVisible(&m_blockContourEnable);
	h += m_blockContourEnable.getHeight();

	//ライト
	m_lightEnable.setText(L"ライト");
	m_lightEnable.setTopLeftPosition(LEFT,h);
	m_lightEnable.referTo( g_config->getLightEnableValueObject() );
	this->addAndMakeVisible(&m_lightEnable);
	h += m_lightEnable.getHeight();
	h += 5;

	//カメラモード
	m_cameraMode.setTopLeftPosition(20,h);
	m_cameraMode.referTo( g_config->getCameraModeValueObject() );
	this->addAndMakeVisible(&m_cameraMode);
	h += m_cameraMode.getHeight();
  h += 10;

	//カメラリセット
	m_cameraReset.setText(L"カメラリセット");
	m_cameraReset.setTopLeftPosition(32,h);
	m_cameraReset.addListener(this);
	this->addAndMakeVisible(&m_cameraReset);
	h += m_cameraReset.getHeight();
}
ViewModeComponent::~ViewModeComponent()
{
}
void ViewModeComponent::paint(Graphics &g)
{
	Colour c = Colours::lightblue;
	g.fillAll(c.withAlpha(0.4f));

	g.setColour(Colours::blue);
	g.drawRect(0,0,this->getWidth(),this->getHeight(),3);
}
void ViewModeComponent::valueChanged(Value& value)
{
	bool isSlice = g_config->getSliceModeEnable();
	m_upBlockEnable.setEnabled( isSlice );
	m_downBlockEnable.setEnabled( isSlice );
}
void ViewModeComponent::onMyButtonClicked(Widget::MyButton*)
{
	g_camera->reset();
	RepaintOpenGL();
}
}//UI
}//MinePlanner