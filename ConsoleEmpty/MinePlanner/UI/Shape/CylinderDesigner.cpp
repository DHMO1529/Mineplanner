#include "MinePlanner/UI/Shape/CylinderDesigner.hpp"

#include "MinePlanner/UI/MainWindow.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/Shape/CreateCylinder.hpp"
namespace MinePlanner{
namespace UI{
namespace Shape{
CylinderDesigner::CylinderDesigner():
 DialogWindow(L"円柱",Colours::lightgrey,false)
,m_component()
,m_blockType()
,m_size()
,m_height()
,m_preview()
,m_decide()
,m_canvas()
,m_decided(false)
{
	m_component.setSize(450,250);

	int h = 0;

	h += 10;
	m_blockType.setText(L"ブロック");
	m_blockType.setTopLeftPosition(0,h);
	m_blockType.setBlockType( g_config->getSelectBlock() );
	m_component.addAndMakeVisible(&m_blockType);
	h += m_blockType.getHeight();

	h += 5;
	m_size.setText(L"直径");
	m_size.setValue(10);
	m_size.setTopLeftPosition(-40,h);
	m_size.setRange(0,100);
	m_component.addAndMakeVisible(&m_size);
	h += m_size.getHeight();

	h += 10;
	m_height.setText(L"高さ");
	m_height.setValue(10);
	m_height.setTopLeftPosition(-40,h);
	m_height.setRange(0,100);
	m_component.addAndMakeVisible(&m_height);
	h += m_height.getHeight();

	const int bottom = m_component.getHeight();

	m_preview.setText(L"プレビュー");
	m_preview.addListener(this);
	m_preview.setTopLeftPosition(45,bottom - m_preview.getHeight() - 50);
	m_component.addAndMakeVisible(&m_preview);

	m_decide.setText(L" 作成 ");
	m_decide.addListener(this);
	m_decide.setTopLeftPosition(60,bottom - m_decide.getHeight() - 15);
	m_component.addAndMakeVisible(&m_decide);

	m_canvas.setTopLeftPosition(200,0);
	m_component.addAndMakeVisible(&m_canvas);

	this->setContentOwned(&m_component,true);
}
CylinderDesigner::~CylinderDesigner()
{
}
void CylinderDesigner::closeButtonPressed()
{
	this->setVisible(false);
}
void CylinderDesigner::onMyButtonClicked(Widget::MyButton* button)
{
	if(button == &m_preview)
	{
		//プレビュー
		BlockSet blocks = MinePlanner::Shape::CreateSylinder(getDiameter(),getHeight(),getBlockID());
		m_canvas.setPrevBlocks(blocks);
	}
	else
	{
		//決定
		m_decided = true;
		this->setVisible(false);
	}
}
bool CylinderDesigner::show()
{
	const int x = UI::getWindowX();
	const int y = UI::getWindowY();
	this->setTopLeftPosition(x+200,y+100);

	this->runModalLoop();
	
	return m_decided;
}
int CylinderDesigner::getDiameter()const
{
	return m_size.getValue();
}
int CylinderDesigner::getHeight()const
{
	return m_height.getValue();
}
int CylinderDesigner::getBlockID()const
{
	return m_blockType.getBlockType();
}
}//Shape
}//UI
}//MinePlanner