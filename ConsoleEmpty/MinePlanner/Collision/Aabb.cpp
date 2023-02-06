#include "MinePlanner/Collision/Aabb.hpp"
namespace MinePlanner{
namespace Collision{
Aabb::Aabb():m_min(),m_max(){}

glm::vec3 Aabb::getMin()const
{
	return m_min;
}
glm::vec3 Aabb::getMax()const
{
	return m_max;
}

Aabb Aabb::make_aabb(const glm::vec3& min,const glm::vec3& max)
{
	Aabb aabb;
	aabb.m_min = min;
	aabb.m_max = max;
	return aabb;
}
}//Collision
}//MinePlanner
