#include "MinePlanner/Shape/CreateBox.hpp"

#include <boost/foreach.hpp>
#include <boost/unordered_set.hpp>

#include "MinePlanner/Point.hpp"
namespace MinePlanner{
namespace Shape{
BlockSet CreateBox(int x,int y,int z,int blockId)
{
	if(x <= 0 || y <= 0 || z <= 0)
	{
		return BlockSet::create();
	}

	boost::unordered_set<Point> points;

	//下、上
	for(int i = 0 ; i < z ; ++i)
	{
		for(int j = 0 ; j < x ; ++j)
		{
			points.insert(Point(j,0,i));
			points.insert(Point(j,y-1,i));
		}
	}

	//左、右
	for(int i = 0 ; i < z ; ++i)
	{
		for(int j = 0 ; j < y ; ++j)
		{
			points.insert(Point(0,j,i));
			points.insert(Point(x-1,j,i));
		}
	}

	//奥、手前
	for(int i = 0 ; i < y ; ++i)
	{
		for(int j = 0 ; j < x ; ++j)
		{
			points.insert(Point(j,i,0));
			points.insert(Point(j,i,z-1));
		}
	}

	BlockSet returnValue = BlockSet::create();
	BOOST_FOREACH(const Point& p,points)
	{
		returnValue.add(p,blockId,Pose());
	}
	return returnValue;
}
}//Shape
}//MinePlanner
