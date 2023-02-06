#include "MinePlanner/Collision/Plane.hpp"
namespace MinePlanner{
namespace Collision{
Plane::Plane():m_n(),m_d(0){}

glm::vec3 Plane::get_n()const
{
	return m_n;
}
float Plane::get_d()const
{
	return m_d;
}
float Plane::calc_dist_point(const glm::vec3 point)const
{
	return glm::dot( point , m_n ) - m_d;
}
Plane Plane::make_plane(const glm::vec3& a,const glm::vec3& b,const glm::vec3& c)
{
	Plane p;
	p.m_n = glm::normalize( glm::cross( b - a , c - a ) );
	p.m_d = glm::dot( p.m_n , a );
	return p;
}
}//Collision
}//MinePlanner
