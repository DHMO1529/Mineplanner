#include "MinePlanner/Shape/Optimize.hpp"
#include <vector>
#include <boost/foreach.hpp>
namespace MinePlanner{
namespace Shape{
namespace{
inline bool IsExist(boost::unordered_set<Point>& points,const Point& point)
{
	if(points.find(point) == points.end())
	{
		return false;
	}
	return true;
}
inline bool IsMustDraw(boost::unordered_set<Point>& points,const Point& point)
{
	if(!IsExist(points,Point::move(point,-1,0,0)))
		return true;

	if(!IsExist(points,Point::move(point,+1,0,0)))
		return true;

	if(!IsExist(points,Point::move(point,0,-1,0)))
		return true;

	if(!IsExist(points,Point::move(point,0,+1,0)))
		return true;

	if(!IsExist(points,Point::move(point,0,0,-1)))
		return true;

	if(!IsExist(points,Point::move(point,0,0,+1)))
		return true;

	return false;
}
}//unnamed
void Optimize(boost::unordered_set<Point>& points)
{
	std::vector<Point> deleteList;

	BOOST_FOREACH(const Point& p,points)
	{
		if(!IsMustDraw(points,p))
		{
			deleteList.push_back(p);
		}
	}

	BOOST_FOREACH(const Point& p,deleteList)
	{
		points.erase(p);
	}
}
}//Shape
}//MinePlanner