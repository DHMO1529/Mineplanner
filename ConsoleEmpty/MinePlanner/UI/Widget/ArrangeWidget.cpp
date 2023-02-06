#include "MinePlanner/UI/Widget/ArrangeWidget.hpp"

#include "MinePlanner/Operation/ArrangementManager.hpp"
#include "MinePlanner/Operation/EditManager.hpp"

#include "MinePlanner/Operation/BatchWork.hpp"
#include "MinePlanner/UI/RepaintOpenGL.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
ArrangeWidget::ArrangeWidget():
 m_tab(TabbedButtonBar::TabsAtTop)
,m_movex()
,m_movey()
,m_movez()
,m_nowx(0)
,m_nowy(0)
,m_nowz(0)
,m_moveXValue()
,m_moveYValue()
,m_moveZValue()
,m_rotateX()
,m_rotateY()
,m_rotateZ()
,m_reverseX()
,m_reverseY()
,m_reverseZ()
,m_target()
{
	this->setSize(150,220);

	m_tab.setSize(140,170);
	m_tab.setTopLeftPosition(5,0);
	Component* move_component = new Component();
	Component* rotate_component = new Component();
	Component* reverse_component = new Component();
	m_tab.addTab(L"ˆÚ“®",Colours::azure,move_component,true);
	m_tab.addTab(L"‰ñ“]",Colours::azure,rotate_component,true);
	m_tab.addTab(L"”½“]",Colours::azure,reverse_component,true);
	this->addAndMakeVisible(&m_tab);

	int h = 10;
	const int NLEFT = -60;
	m_movex.setText(L"ˆÚ“® X");
	m_movex.setTopLeftPosition(NLEFT,h);
	m_movex.setLabelColour(Label::textColourId,Colours::red);
	m_moveXValue.setValue(0.0);
	m_moveXValue.addListener(this);
	m_movex.referTo(m_moveXValue);
	move_component->addAndMakeVisible(&m_movex);
	h += m_movex.getHeight();

	m_movey.setText(L"ˆÚ“® Y");
	m_movey.setTopLeftPosition(NLEFT,h);
	m_movey.setLabelColour(Label::textColourId,Colours::green);
	m_moveYValue.setValue(0.0);
	m_moveYValue.addListener(this);
	m_movey.referTo(m_moveYValue);
	move_component->addAndMakeVisible(&m_movey);
	h += m_movey.getHeight();

	m_movez.setText(L"ˆÚ“® Z");
	m_movez.setTopLeftPosition(NLEFT,h);
	m_movez.setLabelColour(Label::textColourId,Colours::blue);
	m_moveZValue.setValue(0.0);
	m_moveZValue.addListener(this);
	m_movez.referTo(m_moveZValue);
	move_component->addAndMakeVisible(&m_movez);
	h += m_movez.getHeight();

	h = 10;
	const int BLEFT = 25;
	m_rotateX.setText(L"X Ž²‰ñ“]");
	m_rotateX.setColour(TextButton::buttonColourId,Colours::pink);
	m_rotateX.setTopLeftPosition(BLEFT,h);
	m_rotateX.addListener(this);
	rotate_component->addAndMakeVisible(&m_rotateX);
	h += m_rotateX.getHeight();
	h += 10;

	m_rotateY.setText(L"Y Ž²‰ñ“]");
	m_rotateY.setColour(TextButton::buttonColourId,Colours::lightgreen);
	m_rotateY.setTopLeftPosition(BLEFT,h);
	m_rotateY.addListener(this);
	rotate_component->addAndMakeVisible(&m_rotateY);
	h += m_rotateY.getHeight();
	h += 10;

	m_rotateZ.setText(L"Z Ž²‰ñ“]");
	m_rotateZ.setColour(TextButton::buttonColourId,Colours::lightblue);
	m_rotateZ.setTopLeftPosition(BLEFT,h);
	m_rotateZ.addListener(this);
	rotate_component->addAndMakeVisible(&m_rotateZ);
	h += m_rotateZ.getHeight();
	

	h = 10;
	m_reverseX.setText(L"X Ž²”½“]");
	m_reverseX.setColour(TextButton::buttonColourId,Colours::pink);
	m_reverseX.setTopLeftPosition(BLEFT,h);
	m_reverseX.addListener(this);
	reverse_component->addAndMakeVisible(&m_reverseX);
	h += m_reverseX.getHeight();
	h += 10;

	m_reverseY.setText(L"Y Ž²”½“]");
	m_reverseY.setColour(TextButton::buttonColourId,Colours::lightgreen);
	m_reverseY.setTopLeftPosition(BLEFT,h);
	m_reverseY.addListener(this);
	reverse_component->addAndMakeVisible(&m_reverseY);
	h += m_reverseY.getHeight();
	h += 10;

	m_reverseZ.setText(L"Z Ž²”½“]");
	m_reverseZ.setColour(TextButton::buttonColourId,Colours::lightblue);
	m_reverseZ.setTopLeftPosition(BLEFT,h);
	m_reverseZ.addListener(this);
	reverse_component->addAndMakeVisible(&m_reverseZ);
	h += m_reverseZ.getHeight();
	h += 10;


	m_decide.setText(L"  Šm’è  ");
	m_decide.setTopLeftPosition(BLEFT+5,180);
	m_decide.addListener(this);
	this->addAndMakeVisible(&m_decide);
	h += m_decide.getHeight();
}
ArrangeWidget::~ArrangeWidget()
{
}
void ArrangeWidget::init(BlockSet target)
{
	m_target = target;
	m_movex.setValue(0);
	m_movey.setValue(0);
	m_movez.setValue(0);

	m_nowx = m_nowy = m_nowz = 0;
}
void ArrangeWidget::fin()
{
	m_target = BlockSet();
}
void ArrangeWidget::valueChanged(Value& value)
{
	if(m_nowx != m_movex.getValue())
	{
		const int diff = m_movex.getValue() - m_nowx;
		m_nowx += diff;
		m_target.move(diff,0,0);
	}
	if(m_nowy != m_movey.getValue())
	{
		const int diff = m_movey.getValue() - m_nowy;
		m_nowy += diff;
		m_target.move(0,diff,0);
	}
	if(m_nowz != m_movez.getValue())
	{
		const int diff = m_movez.getValue() - m_nowz;
		m_nowz += diff;
		m_target.move(0,0,diff);
	}

	RepaintOpenGL();
}
void ArrangeWidget::onMyButtonClicked(MyButton* arg)
{
	if(&m_rotateX == arg)
	{
		m_target.rotate(1,0,0);
	}
	else if(&m_rotateY == arg)
	{
		m_target.rotate(0,1,0);
	}
	else if(&m_rotateZ == arg)
	{
		m_target.rotate(0,0,1);
	}

	else if(&m_reverseX == arg)
	{
		m_target.reverse(true,false,false);
	}
	else if(&m_reverseY == arg)
	{
		m_target.reverse(false,true,false);
	}
	else if(&m_reverseZ == arg)
	{
		m_target.reverse(false,false,true);
	}

	else if(&m_decide == arg)
	{
		//Šm’è
		g_pEditManager()->dowork(Operation::BatchWork::createBatchAdd(m_target));

		fin();

		g_pArrangementManager()->arrangeFinish();
	}
	RepaintOpenGL();
}
}//Widget
}//UI
}//MinePlanner
