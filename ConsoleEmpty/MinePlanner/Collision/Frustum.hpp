#ifndef MINEPLANNER_COLLISION_FRUSTUM_HPP
#define MINEPLANNER_COLLISION_FRUSTUM_HPP
#include <boost/array.hpp>
#include "MinePlanner/Rect.hpp"
#include "MinePlanner/Collision/Plane.hpp"
namespace MinePlanner{
namespace Collision{
class Frustum
{
public:
	Frustum();

	//ÇªÇÃì_Ç™óÃàÊÇ…ä‹Ç‹ÇÍÇÈÅH
	bool is_contain(const glm::vec3& point)const;

	static Frustum make_frustum(const Rect& screenRect);
private:
	boost::array<Plane,6> m_planes;
};
}//Collision
}//MinePlanner
#endif