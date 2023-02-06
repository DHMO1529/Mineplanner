#include "MinePlanner/Collision/RayCastResult.hpp"
#include "MinePlanner/Point.hpp"
#include <sstream>
namespace MinePlanner{
namespace Collision{
RayCastResult::RayCastResult():m_target(),m_next(),m_is_intersect(false)
{
}
bool RayCastResult::is_intersect()const
{
	return m_is_intersect;
}
Point RayCastResult::getTarget()const
{
	return m_target;
}
Point RayCastResult::getNext()const
{
	return m_next;
}
std::string RayCastResult::toString()const
{
	std::stringstream ss;
	ss << "RayCastResult(";
	ss << "target=" << m_target.toString() << ",";
	ss << "nex=" << m_next.toString() << ",";
	ss << "Collide=" << m_is_intersect << ")";
	return ss.str();
}

RayCastResult RayCastResult::make_intersect(const Point& target,const Point& next)
{
	RayCastResult r;
	r.m_target = target;
	r.m_next = next;
	r.m_is_intersect = true;
	return r;
}
RayCastResult RayCastResult::make_no_intersect()
{
	return RayCastResult();
}
}//Collision
}//MinePlanner