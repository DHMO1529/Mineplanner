#include "MinePlanner/Operation/ClipBoard.hpp"

#include "MinePlanner/World.hpp"
#include "MinePlanner/Operation/ArrangementManager.hpp"
#include "MinePlanner/Operation/SelectionManager.hpp"
#include "MinePlanner/Operation/EditManager.hpp"
#include "MinePlanner/Operation/BatchWork.hpp"

#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"

#include "MinePlanner/UI/SubModeSelectComponent.hpp"

namespace MinePlanner{
namespace Operation{
ClipBoard::ClipBoard()
{
	m_clipBuffer = BlockSet::create();
}
ClipBoard::~ClipBoard()
{
}
void ClipBoard::copy()
{
	if(g_config->getSubMode() != SUBMODE_SELECT)
	{
		return;
	}
	if(g_pSelectionManager()->isSelecting())
	{
		PointSet selected_points = g_pSelectionManager()->getSelectedPoints();

		BlockSet clip_buffer = BlockSet::create();
		auto get_clip_buffer = [&clip_buffer](const Point& point)
		{
			if(World::instance().isExist(point))
			{
				clip_buffer.add(point,World::instance().getBlockID(point),World::instance().getPose(point));
			}
		};
		selected_points.for_each(get_clip_buffer);

		m_clipBuffer = clip_buffer;//クリップボードに保存

		UI::getSubModeSelectComponent()->updateDisplay();//有効、無効状態を更新
	}
}
void ClipBoard::cut()
{
	if(g_pSelectionManager()->isSelecting())
	{
		PointSet selected_points = g_pSelectionManager()->getSelectedPoints();
		BlockSet clip_buffer = BlockSet::create();
		auto get_clip_buffer = [&clip_buffer](const Point& point)
		{
			if(World::instance().isExist(point))
			{
				clip_buffer.add(point,World::instance().getBlockID(point),World::instance().getPose(point));
			}
		};
		selected_points.for_each(get_clip_buffer);

		m_clipBuffer = clip_buffer;//クリップボードに保存

		g_pEditManager()->dowork(BatchWork::createBatchDelete(selected_points));
		g_pSelectionManager()->clearSelect();

		UI::getSubModeSelectComponent()->updateDisplay();//有効、無効状態を更新
	}
}
void ClipBoard::paste()
{
	if(m_clipBuffer.hasInstance())
	{
		g_pArrangementManager()->arrange(m_clipBuffer.clone());
	}
}
bool ClipBoard::hasData()const
{
	if(m_clipBuffer.hasInstance())
	{
		if(m_clipBuffer.getBlockNum() > 0)
		{
			return true;
		}
	}
	return false;
}
}//Operation
}//MinePlanner