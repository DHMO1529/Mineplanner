#include "MinePlanner/Shape/CreateCone.hpp"

#include <boost/foreach.hpp>
#include <boost/unordered_set.hpp>
#include <glm/glm.hpp>

#include "MinePlanner/Shape/Optimize.hpp"
#include "MinePlanner/Point.hpp"
#include "Util/Lerp.hpp"
namespace MinePlanner{
namespace Shape{
BlockSet CreateCone(int diameter,int height,int blockId)
{
	if(diameter <= 0)
	{
		return BlockSet::create();
	}

	BlockSet returnValue = BlockSet::create();

	//ÉçÉWÉbÉN
	boost::unordered_set<Point> points;

	//ãÙêîÇ∆äÔêîÇ≈Ç∏ÇÁÇ∑Ç∆„YóÌÇ»â~Ç…Ç»ÇÈ
	const glm::vec3 center = (diameter % 2 == 1)? glm::vec3() : glm::vec3(0.5f,0,0.5f);
	const float radius = static_cast<float>(diameter) * 0.5f;
	Util::Lerpf lerp(0,radius,static_cast<float>(height-1),1.f);

	const int min = -diameter / 2;
	const int max = diameter / 2;
	
	for(int y = 0 ; y < height ; ++y)
	{
		for(int z = min ; z <= max ; ++z)
		{
			for(int x = min ; x <= max ; ++x)
			{
				const glm::vec3 posf(
					static_cast<float>(x),
					0,
					static_cast<float>(z));

				const glm::vec3 c(center.x,0,center.z);
				float distance = glm::length(posf - c);
				float d = lerp(static_cast<float>(y));
				if( distance < lerp(static_cast<float>(y)) )
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