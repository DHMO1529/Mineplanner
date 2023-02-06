#include "MinePlanner/Operation/BasicEditor.hpp"

#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/World.hpp"
#include "MinePlanner/graphic/graphic.hpp"

#include "MinePlanner/GlobalConfigEnumDef.hpp"
#include "MinePlanner/Operation/BasicWork.hpp"
#include "MinePlanner/Operation/EditManager.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"
#include "MinePlanner/getBlockPose.hpp"
namespace MinePlanner{
namespace Operation{
BasicEditor::BasicEditor():
 m_rayCastResult()
{
}
BasicEditor::~BasicEditor()
{
}
void BasicEditor::draw()const
{
	if(m_rayCastResult.is_intersect())
	{
		switch(g_config->getEditType())
		{
		case EDITTYPE_ADD:
			graphic::DrawRedContour(m_rayCastResult.getNext());//枠
			//半透明にエディット後を
			{
				graphic::beginBlockDraw();
				const int blockId = g_config->getSelectBlock();
				graphic::drawBlock(m_rayCastResult.getNext(),blockId,getBlockPose(blockId),0.5f);
				graphic::endBlockDraw();
			}
			break;
		case EDITTYPE_SWAP:
			graphic::DrawRedContour(m_rayCastResult.getTarget());
			//半透明にエディット後を
			{
				graphic::beginBlockDraw();
				const int blockId = g_config->getSelectBlock();
				graphic::drawBlock(m_rayCastResult.getTarget(),blockId,getBlockPose(blockId),0.5f,1.01f);
				graphic::endBlockDraw();
			}
			break;
		case EDITTYPE_DELETE:
			graphic::DrawRedContour(m_rayCastResult.getTarget());
			break;
		}
	}
}
void BasicEditor::mouseMove(const MouseEvent& e)
{
	graphic::Resolution r = graphic::GetResolution();
	const int x = e.x;
	const int y = r.getHeight() - e.y;

	graphic::Camera::ray ray =  g_camera->getMouseRay(x,y);

	Collision::Detector detector = World::instance().getDetector();

	//編集グリッド
	bool isPlaneEnable = g_config->getEditGridEnable() && g_config->getEditType() == EDITTYPE_ADD;
	if(isPlaneEnable)
	{
		m_rayCastResult = detector.rayCast(ray.first,ray.second, g_config->getEditGridHeight());
	}
	else
	{
		m_rayCastResult = detector.rayCast(ray.first,ray.second);
	}
}
void BasicEditor::mouseDown(const MouseEvent& e)
{
	if(e.mods.isLeftButtonDown())
	{
		if(m_rayCastResult.is_intersect())
		{
			Work::ptr work;
			switch(g_config->getEditType())
			{
			case EDITTYPE_ADD:
				work = BasicWork::createAdd(m_rayCastResult.getNext(),g_config->getSelectBlock(),getBlockPose( g_config->getSelectBlock() ));
				break;
			case EDITTYPE_SWAP:
				work = BasicWork::createSwap(m_rayCastResult.getTarget(),g_config->getSelectBlock(),getBlockPose( g_config->getSelectBlock() ));
				break;
			case EDITTYPE_DELETE:
				work = BasicWork::createDelete(m_rayCastResult.getTarget());
				break;
			}

			if(work)
			{
				g_pEditManager()->dowork(work);
			}
		}
	}

	mouseMove(e);
}
void BasicEditor::mouseDrag(const MouseEvent& e)
{
	mouseMove(e);

	//塗り
	if(e.mods.isLeftButtonDown())
	{
		if(g_config->getEditType() == EDITTYPE_SWAP)
		{
			Work::ptr work = BasicWork::createSwap(m_rayCastResult.getTarget(),g_config->getSelectBlock(),getBlockPose( g_config->getSelectBlock() ));
			g_pEditManager()->dowork(work);
		}
	}
}
}//Operation
}//MinePlanner
