#include "MinePlanner/graphic/DrawTransparentBlockSet.hpp"
#include "MinePlanner/graphic/DrawBlock.hpp"
namespace MinePlanner{
namespace graphic{
void DrawTransparentBlockSet(BlockSet blockSet)
{
	if(!blockSet.hasInstance())return;

	graphic::beginBlockDraw();
	auto draw_func = [](const Point& point,int blockId,const Pose& pose)
	{
		graphic::drawBlock(point,blockId,pose,0.6f);
	};
	blockSet.for_each(draw_func);
	graphic::endBlockDraw();
}
}//graphic
}//MinePlanner
