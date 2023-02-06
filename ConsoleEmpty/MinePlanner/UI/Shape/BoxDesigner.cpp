#include "MinePlanner/UI/Shape/BoxDesigner.hpp"

#include "MinePlanner/UI/MainWindow.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/Shape/CreateBox.hpp"
namespace MinePlanner{
namespace UI{
namespace Shape{
BoxDesigner::BoxDesigner():
 DialogWindow(L"箱",Colours::lightgrey,false)
,m_component()
,m_blockType()
,m_sizex()
,m_sizey()
,m_sizez()
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
	m_sizex.setText(L"Ｘ");
	m_sizex.setValue(10);
	m_sizex.setTopLeftPosition(-45,h);
	m_sizex.setRange(0,100);
	m_sizex.setLabelColour(Label::textColourId,Colours::red);
	m_component.addAndMakeVisible(&m_sizex);
	h += m_sizex.getHeight();
	h += 5;

	m_sizey.setText(L"Ｙ");
	m_sizey.setValue(10);
	m_sizey.setTopLeftPosition(-45,h);
	m_sizey.setRange(0,100);
	m_sizey.setLabelColour(Label::textColourId,Colours::green);
	m_component.addAndMakeVisible(&m_sizey);
	h += m_sizey.getHeight();

	h += 5;
	m_sizez.setText(L"Ｚ");
	m_sizez.setValue(10);
	m_sizez.setTopLeftPosition(-45,h);
	m_sizez.setRange(0,100);
	m_sizez.setLabelColour(Label::textColourId,Colours::blue);
	m_component.addAndMakeVisible(&m_sizez);
	h += m_sizez.getHeight();

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
BoxDesigner::~BoxDesigner()
{
}
void BoxDesigner::closeButtonPressed()
{
	this->setVisible(false);
}
void BoxDesigner::onMyButtonClicked(Widget::MyButton* button)
{
	if(button == &m_preview)
	{
		//プレビュー
		BlockSet blocks = MinePlanner::Shape::CreateBox(getxsize(),getysize(),getzsize(),getBlockID());
		m_canvas.setPrevBlocks(blocks);
	}
	else
	{
		//決定
		m_decided = true;
		this->setVisible(false);
	}
}
bool BoxDesigner::show()
{
	const int x = UI::getWindowX();
	const int y = UI::getWindowY();
	this->setTopLeftPosition(x+200,y+100);

	this->runModalLoop();
	
	return m_decided;
}
int BoxDesigner::getxsize()const
{
	return m_sizex.getValue();
}
int BoxDesigner::getysize()const
{
	return m_sizey.getValue();
}
int BoxDesigner::getzsize()const
{
	return m_sizez.getValue();
}
int BoxDesigner::getBlockID()const
{
	return m_blockType.getBlockType();
}
}//Shape
}//UI
}//MinePlanner