#include "MinePlanner/Operation/HideBuffer.hpp"

#include "MinePlanner/World.hpp"
#include "MinePlanner/Operation/SelectionManager.hpp"
#include "MinePlanner/UI/SubModeSelectComponent.hpp"
namespace MinePlanner{
namespace Operation{
HideBuffer::HideBuffer()
{
	m_hideBuffer = PointSet::create();
}
HideBuffer::~HideBuffer()
{
}
void HideBuffer::hide()
{
	PointSet selected_points = g_pSelectionManager()->getSelectedPoints();
	auto add_hide_buffer = [this](const Point& point)
	{
		m_hideBuffer.add(point);
	};
	selected_points.for_each(add_hide_buffer);
	 
	World::instance().update_collision(m_hideBuffer);
	g_pSelectionManager()->clearSelect();

	UI::getSubModeSelectComponent()->updateDisplay();//�L���A������Ԃ��X�V
}
void HideBuffer::show()
{
	m_hideBuffer.clear();
	World::instance().update_collision(m_hideBuffer);

	UI::getSubModeSelectComponent()->updateDisplay();//�L���A������Ԃ��X�V
}
PointSet HideBuffer::getHideBuffer()const
{
	return m_hideBuffer;
}
bool HideBuffer::isHide()const
{
	return m_hideBuffer.getNum() != 0;
}
}//Operation
}//MinePlanner