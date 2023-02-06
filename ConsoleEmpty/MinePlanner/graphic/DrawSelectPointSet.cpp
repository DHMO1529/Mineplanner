#include "MinePlanner/graphic/DrawSelectPointSet.hpp"

#include "MinePlanner/graphic/DrawContour.hpp"

namespace MinePlanner{
namespace graphic{
void DrawSelectPointSet(PointSet points)
{
	if(!points.hasInstance())return;

	struct{
		void operator()(const Point& point){
			DrawRedContour(point);
		}
	}draw_func;
	points.for_each(draw_func);
}
}//graphic
}//MinePlanner