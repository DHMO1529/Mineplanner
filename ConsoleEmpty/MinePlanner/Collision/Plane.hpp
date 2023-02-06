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

	//点との距離を算出
	float calc_dist_point(const glm::vec3 point)const;

	//３つの一直線上にない点から平面方程式を計算 法線に対して右手座標系順
	static Plane make_plane(const glm::vec3& a,const glm::vec3& b,const glm::vec3& c);
private:
	glm::vec3 m_n; //法線
	float m_d;
};
}//Collision
}//MinePlanner
#endif