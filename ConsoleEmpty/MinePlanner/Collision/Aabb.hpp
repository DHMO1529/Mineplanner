#ifndef MINEPLANNER_COLLISION_AABB_HPP
#define MINEPLANNER_COLLISION_AABB_HPP
#include <glm/glm.hpp>
namespace MinePlanner{
namespace Collision{
class Aabb
{
public:
	Aabb();

	glm::vec3 getMin()const;
	glm::vec3 getMax()const;

	static Aabb make_aabb(const glm::vec3& min,const glm::vec3& max);
private:
	glm::vec3 m_min;
	glm::vec3 m_max;
};
}//Collision
}//MinePlanner
#endif