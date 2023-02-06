#include "MinePlanner/graphic/DrawSliceBlocks.hpp"

#include "MinePlanner/World.hpp"

#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/graphic/Light.hpp"
#include "MinePlanner/graphic/DrawContour.hpp"
#include "MinePlanner/graphic/DrawBlock.hpp"
namespace MinePlanner{
namespace graphic{
const float ALPHA = 0.25f;
void DrawSliceBlocks()
{
	//メイン
	if(g_config->getLightEnable())
	{
		EnbaleLight();
	}

	const int SLICE_HEIGHT = g_config->getSliceHeight();

	//不透明
	beginBlockDraw();
	auto slice_draw = [SLICE_HEIGHT](const Point& point,int blockId,const Pose& pose)
	{
		if(point.getY() == SLICE_HEIGHT)
		{
			drawBlock(point,blockId,pose);
		}
	};
	World::instance().for_each(slice_draw);
	endBlockDraw();

	if(g_config->getLightEnable())
	{
		DisableLight();
	}

	//輪郭 上、中、下
	const bool IS_UP = g_config->getUpBlockEnable();
	const bool IS_DOWN = g_config->getDownBlockEnable();
	if(g_config->getBlockContourEnable())
	{
		auto contour_draw = [SLICE_HEIGHT,IS_UP,IS_DOWN](const Point& point,int blockId,const Pose& pose)
		{
			if(point.getY() == SLICE_HEIGHT)
			{
				DrawBlackContour(point);
			}
			else if(point.getY() == SLICE_HEIGHT + 1)
			{
				if(IS_UP)
				{
					DrawBlackContour(point);
				}
			}
			else if(point.getY() == SLICE_HEIGHT - 1)
			{
				if(IS_DOWN)
				{
					DrawBlackContour(point);
				}
			}
		};
		World::instance().for_each(contour_draw);
	}

	//上下ブロック
	auto updown_draw = [SLICE_HEIGHT,IS_UP,IS_DOWN](const Point& point,int blockId,const Pose& pose)
	{
		if(point.getY() == SLICE_HEIGHT + 1)
		{
			if(IS_UP)
			{
				drawBlock(point,blockId,pose,ALPHA);
			}
		}
		else if(point.getY() == SLICE_HEIGHT - 1)
		{
			if(IS_DOWN)
			{
				drawBlock(point,blockId,pose,ALPHA);
			}
		}
	};
	beginBlockDraw();
		World::instance().for_each(updown_draw);
	endBlockDraw();
}
}//graphic
}//MinePlanner
