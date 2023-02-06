#include "MinePlanner/Shape/CreateCylinder.hpp"

#include <boost/foreach.hpp>
#include <boost/unordered_set.hpp>
#include <glm/glm.hpp>

#include "MinePlanner/Shape/Optimize.hpp"
#include "MinePlanner/Point.hpp"
namespace MinePlanner{
namespace Shape{
BlockSet CreateSylinder(int diameter,int height,int blockId)
{
	if(diameter <= 0)
	{
		return BlockSet::create();
	}

	BlockSet returnValue = BlockSet::create();

	//ƒƒWƒbƒN
	boost::unordered_set<Point> points;

	//‹ô”‚ÆŠï”‚Å‚¸‚ç‚·‚ÆãY—í‚È‰~‚É‚È‚é
	const glm::vec3 center = (diameter % 2 == 1)? glm::vec3() : glm::vec3(0.5f,0,0.5f);
	const float radius = static_cast<float>(diameter) * 0.5f;

	const int min = -diameter / 2;
	const int max = diameter / 2;
	
	boost::unordered_set<Point> tmp;
	for(int z = min ; z <= max ; ++z)
	{
		for(int x = min ; x <= max ; ++x)
		{
			const glm::vec3 posf(
				static_cast<float>(x),
				static_cast<float>(0),
				static_cast<float>(z));
			float distance = glm::length(posf - center);
			if(distance < radius)
			{
				tmp.insert(Point(x,0,z));
			}
		}
	}

	for(int i = 0 ; i < height ; ++i)
	{
		BOOST_FOREACH(const Point& p,tmp)
		{
			points.insert(Point::move(p,0,i,0));
		}
	}

	Optimize(points);

	BOOST_FOREACH(const Point& p,points)
	{
		returnValue.add(p,blockId,Pose());
	}
	return returnValue;
}
}//Shape
}//MinePlanner
