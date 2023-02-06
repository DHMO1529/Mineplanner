#include "MinePlanner/graphic/DrawFullBlocks.hpp"

#include "MinePlanner/World.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/graphic/DrawBlock.hpp"
#include "MinePlanner/graphic/Light.hpp"
#include "MinePlanner/graphic/DrawContour.hpp"
namespace MinePlanner{
namespace graphic{
void DrawFullBlocks()
{
	if(g_config->getLightEnable())
	{
		EnbaleLight();
	}

	//ƒƒCƒ“
	beginBlockDraw();
		auto draw = [](const Point& point,int blockId,const Pose& pose)
		{
			drawBlock(point,blockId,pose);
		};
		World::instance().for_each(draw);
	endBlockDraw();

	if(g_config->getLightEnable())
	{
		DisableLight();
	}

	//—ÖŠs
	if(g_config->getBlockContourEnable())
	{
		auto contour_draw = [](const Point& point,int blockId,const Pose& pose)
		{
			DrawBlackContour(point);
		};
		World::instance().for_each(contour_draw);
	}
}
}//graphic
}//MinePlanner
