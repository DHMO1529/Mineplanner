#ifndef MINEPLANNER_COLLISION_RAYCASTRESULT_HPP
#define MINEPLANNER_COLLISION_RAYCASTRESULT_HPP
#include <string>
#include "MinePlanner/Point.hpp"
namespace MinePlanner{
namespace Collision{
class RayCastResult
{
public:
	RayCastResult();

	bool is_intersect()const;
	Point getTarget()const;
	Point getNext()const;
	std::string toString()const;

	static RayCastResult make_intersect(const Point& target,const Point& next);
	static RayCastResult make_no_intersect();
private:
	Point m_target;
	Point m_next;
	bool m_is_intersect;
};
}//Collision
}//MinePlanner
#endif