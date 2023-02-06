#include "MinePlanner/Operation/SelectionManager.hpp"

#include "MinePlanner/graphic/graphic.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"
#include "MinePlanner/World.hpp"
#include "MinePlanner/Operation/HideBuffer.hpp"

#include "MinePlanner/UI/SubModeSelectComponent.hpp"
#include "MinePlanner/graphic/Camera.hpp"
#include "MinePlanner/Collision/Frustum.hpp"

namespace MinePlanner{
namespace Operation{
SelectionManager::SelectionManager():
 m_selectingRect()
,m_selectedPoints()
{
	m_selectedPoints = PointSet::create();
}
SelectionManager::~SelectionManager()
{
}
void SelectionManager::draw()const
{
	if(!m_selectingRect.empty())
	{
		graphic::DrawRect(m_selectingRect);
	}

	graphic::DrawSelectPointSet( m_selectedPoints );
}
void SelectionManager::mouseDown(const MouseEvent& e)
{
	if(e.mods.isLeftButtonDown())
	{
		if(e.mods.isCtrlDown())
		{
			graphic::Resolution r = graphic::GetResolution();
			const int x = e.x;
			const int y = r.getHeight() - e.y;
			graphic::Camera::ray ray = g_camera->getMouseRay(x,y);
			Collision::RayCastResult result = World::instance().getDetector().rayCast(ray.first,ray.second);
			
			if(result.is_intersect())
			{
				if(m_selectedPoints.isContain(result.getTarget()))
				{
					m_selectedPoints.remove(result.getTarget());
				}
				else
				{
					m_selectedPoints.add(result.getTarget());
				}
			}
		}
		else
		{
			this->clearSelect();
		}
	}
}
void SelectionManager::mouseDrag(const MouseEvent& e)
{
	if(!e.mods.isCtrlDown())
	{
		if(e.mods.isLeftButtonDown())
		{
			graphic::Resolution r = graphic::GetResolution();
			m_selectingRect = Rect::fromPoints(
				e.getMouseDownX(),
				r.getHeight() - e.getMouseDownY(),
				e.x,
				r.getHeight() - e.y);
		}
	}
	else
	{
		m_selectingRect = Rect();
	}
}
void SelectionManager::mouseUp(const MouseEvent& e)
{
	if(!e.mods.isCtrlDown())
	{
		if(e.mods.isLeftButtonDown())
		{
			if(!m_selectingRect.empty())
			{
				Collision::Frustum frustum = Collision::Frustum::make_frustum( m_selectingRect );
				m_selectedPoints = World::instance().getDetector().frustumQuery( frustum );
				UI::getSubModeSelectComponent()->updateDisplay();//有効、無効状態を更新
			}
		}
	}
	m_selectingRect = Rect();
}
bool SelectionManager::isSelecting()const
{
	return m_selectedPoints.getNum() != 0;
}
PointSet SelectionManager::getSelectedPoints()
{
	return m_selectedPoints.clone();
}
void SelectionManager::clearSelect()
{
	m_selectingRect = Rect();
	m_selectedPoints.clear();
	UI::getSubModeSelectComponent()->updateDisplay();//有効、無効状態を更新
}
void SelectionManager::selectAll()
{
	if(g_config->getMode() != MODE_EDIT)
	{
		return;
	}
	if(g_config->getSubMode() == SUBMODE_BASIC)
	{
		return;
	}
	PointSet hide_buffer = g_pHideBuffer()->getHideBuffer();
	PointSet selected_points = PointSet::create();
	auto select_all = [&hide_buffer,&selected_points](const Point& point,int blockId,const Pose& pose)
	{
		if(!hide_buffer.isContain(point))
		{
			selected_points.add(point);
		}
	};

	World::instance().for_each(select_all);

	m_selectedPoints = selected_points;
	UI::getSubModeSelectComponent()->updateDisplay();//有効、無効状態を更新
}
}//Operation
}//MinePlanner
