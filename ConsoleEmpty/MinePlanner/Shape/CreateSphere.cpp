#include "MinePlanner/Shape/CreateSphere.hpp"

#include <boost/foreach.hpp>
#include <boost/unordered_set.hpp>
#include <glm/glm.hpp>

#include "MinePlanner/Shape/Optimize.hpp"
#include "MinePlanner/Point.hpp"
namespace MinePlanner{
namespace Shape{
BlockSet CreateSphere(int diameter,int blockId)
{
	if(diameter <= 0)
	{
		return BlockSet::create();
	}

	BlockSet returnValue = BlockSet::create();

	//ƒƒWƒbƒN
	boost::unordered_set<Point> points;

	//‹ô”‚ÆŠï”‚Å‚¸‚ç‚·‚ÆãY—í‚É‹…‚É‚È‚é
	const glm::vec3 center = (diameter % 2 == 1)? glm::vec3() : glm::vec3(0.5f,0.5f,0.5f);
	const float radius = static_cast<float>(diameter) * 0.5f;

	const int min = -diameter / 2;
	const int max = diameter / 2;

	for(int x = min ; x <= max ; ++x)
	{
		for(int z = min ; z <= max ; ++z)
		{
			for(int y = min ; y <= max ; ++y)
			{
				const glm::vec3 posf(
					static_cast<float>(x),
					static_cast<float>(y),
					static_cast<float>(z));

				float distance = glm::length(posf - center);
				if(distance < radius)
				{
					points.insert(Point(x,y,z));
				}
			}
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
