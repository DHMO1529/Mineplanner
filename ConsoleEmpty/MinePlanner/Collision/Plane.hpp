#ifndef MINEPLANNER_COLLISION_PLANE_HPP
#define MINEPLANNER_COLLISION_PLANE_HPP
#include <glm/glm.hpp>
namespace MinePlanner{
namespace Collision{
class Plane
{
public:
	Plane();

	glm::vec3 get_n()const;
	float get_d()const;

	//�_�Ƃ̋������Z�o
	float calc_dist_point(const glm::vec3 point)const;

	//�R�̈꒼����ɂȂ��_���畽�ʕ��������v�Z �@���ɑ΂��ĉE����W�n��
	static Plane make_plane(const glm::vec3& a,const glm::vec3& b,const glm::vec3& c);
private:
	glm::vec3 m_n; //�@��
	float m_d;
};
}//Collision
}//MinePlanner
#endif