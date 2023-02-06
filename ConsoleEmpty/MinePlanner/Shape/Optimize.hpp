#ifndef MINEPLANNER_SHAPE_OPTIMIZE
#define MINEPLANNER_SHAPE_OPTIMIZE
#include <boost/unordered_set.hpp>
#include "MinePlanner/Point.hpp"
namespace MinePlanner{
namespace Shape{
void Optimize(boost::unordered_set<Point>& points);
}//Shape
}//MinePlanner
#endif