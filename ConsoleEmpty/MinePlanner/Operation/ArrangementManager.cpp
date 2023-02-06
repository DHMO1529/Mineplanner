#include "MinePlanner/Operation/ArrangementManager.hpp"

#include "MinePlanner/graphic/graphic.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"
namespace MinePlanner{
namespace Operation{
ArrangementManager::ArrangementManager():
 m_arrangeTarget()
,m_arrangeUI()
{
	m_arrangeTarget = BlockSet::create();
}
ArrangementManager::~ArrangementManager()
{
	this->arrangeFinish();
}
bool ArrangementManager::isArranging()const
{
	return m_arrangeTarget.getBlockNum() > 0;
}
void ArrangementManager::onModeChanged()
{
	if(g_config->getMode() != MODE_EDIT)
	{
		this->arrangeFinish();
	}
}
void ArrangementManager::arrange(BlockSet arrangeTarget)
{
	if(!arrangeTarget.hasInstance())
	{
		assert(0);
	}
	this->arrangeFinish();

	if(!m_arrangeUI)
	{
		m_arrangeUI.reset(new UI::ArrangeUI());
	}

	m_arrangeTarget = arrangeTarget;

	m_arrangeUI->startArrange( m_arrangeTarget );
}
void ArrangementManager::arrangeFinish()
{
	if(m_arrangeUI)
	{
		m_arrangeUI->finishArrange();
	}
	m_arrangeTarget = BlockSet::create();
}
void ArrangementManager::draw()const
{
	if(m_arrangeTarget.getBlockNum() > 0)
	{
		graphic::DrawTransparentBlockSet( m_arrangeTarget );
		graphic::DrawArrangeXYZ( m_arrangeTarget.getOrigin(), static_cast<float>(m_arrangeTarget.getMaxWidth()) );
	}
}
}//Operation
}//MinePlanner
