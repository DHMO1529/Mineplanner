#include "MinePlanner/Collision/Frustum.hpp"
#include <boost/foreach.hpp>
#include "MinePlanner/graphic/Camera.hpp"
namespace MinePlanner{
namespace Collision{
enum{
	PLANE_TOP = 0,
	PLANE_BOTTOM,
	PLANE_LEFT,
	PLANE_RIGHT,
	PLANE_BACK,
	PLANE_FRONT,

	PLANE_NUM
};
Frustum::Frustum():m_planes(){}

bool Frustum::is_contain(const glm::vec3& point)const
{
	BOOST_FOREACH(const Plane& plane,m_planes)
	{
		if(plane.calc_dist_point(point) > 0)
		{
			return false;
		}
	}
	return true;
}
Frustum Frustum::make_frustum(const Rect& screenRect)
{
	graphic::Camera::ray left_bottom = g_camera->getMouseRay(screenRect.getX(),screenRect.getY());
	graphic::Camera::ray right_bottom = g_camera->getMouseRay(screenRect.getX() + screenRect.getWidth(),screenRect.getY());
	graphic::Camera::ray right_top = g_camera->getMouseRay(screenRect.getX() + screenRect.getWidth(),screenRect.getY() + screenRect.getHeight());
	graphic::Camera::ray left_top = g_camera->getMouseRay(screenRect.getX(),screenRect.getY() + screenRect.getHeight());

	const glm::vec3 a = left_bottom.first;
	const glm::vec3 b = right_bottom.first;
	const glm::vec3 c = right_top.first;
	const glm::vec3 d = left_top.first;
	const glm::vec3 e = left_bottom.first + left_bottom.second;
	const glm::vec3 f = right_bottom.first + right_bottom.second;
	const glm::vec3 g = right_top.first + right_top.second;
	const glm::vec3 h = left_top.first + left_top.second;

	Frustum frustum;
	frustum.m_planes[PLANE_TOP] = Plane::make_plane(d,c,g);
	frustum.m_planes[PLANE_BOTTOM] = Plane::make_plane(a,e,f);
	frustum.m_planes[PLANE_LEFT] = Plane::make_plane(a,d,h);
	frustum.m_planes[PLANE_RIGHT] = Plane::make_plane(c,b,f);
	frustum.m_planes[PLANE_BACK] = Plane::make_plane(h,g,f);
	frustum.m_planes[PLANE_FRONT] = Plane::make_plane(a,b,c);
	return frustum;
}
}//Collision
}//MinePlanner