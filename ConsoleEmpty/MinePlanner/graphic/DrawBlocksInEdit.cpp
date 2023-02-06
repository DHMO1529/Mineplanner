#include "MinePlanner/graphic/DrawBlocksInEdit.hpp"

#include "MinePlanner/World.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/graphic/Light.hpp"
#include "MinePlanner/graphic/DrawBlock.hpp"
#include "MinePlanner/graphic/DrawContour.hpp"

#include "MinePlanner/Operation/HideBuffer.hpp"
namespace MinePlanner{
namespace graphic{
void DrawBlocksInEdit()
{
	//メイン
	if(g_config->getLightEnable())
	{
		EnbaleLight();
	}

	PointSet hide_buffer = g_pHideBuffer()->getHideBuffer();

	//ブロック
	beginBlockDraw();
	auto draw_block = [&hide_buffer](const Point& point,int blockId,const Pose& pose)
	{
		if( !hide_buffer.isContain(point) )
		{
			drawBlock(point,blockId,pose);
		}
	};
	World::instance().for_each(draw_block);
	endBlockDraw();

	if(g_config->getLightEnable())
	{
		DisableLight();
	}

	//輪郭
	if(g_config->getBlockContourEnable())
	{
		auto draw_contour = [&hide_buffer](const Point& point,int blockId,const Pose& pose)
		{
			if( !hide_buffer.isContain(point) )
			{
				DrawBlackContour(point);
			}
		};
		World::instance().for_each(draw_contour);
	}
}
}//graphic
}//MinePlanner
