#ifndef MINEPLANNER_COLLISION_INTERSECT_HPP
#define MINEPLANNER_COLLISION_INTERSECT_HPP
#include "MinePlanner/Collision/Aabb.hpp"
#include "MinePlanner/Collision/Plane.hpp"
namespace MinePlanner{
namespace Collision{
class Intersect
{
private:
	Intersect();
public:
	class RayAabbResult
	{
	public:
		RayAabbResult();

		bool is_intersect()const;
		glm::vec3 get_intersect_point()const;

		static RayAabbResult make_intersect(const glm::vec3& collision_point);
		static RayAabbResult make_no_intersect();
	private:
		bool m_is_intersect;
		glm::vec3 m_intersect_point;
	};

	static RayAabbResult test_ray_aabb(const glm::vec3& ray_begin,const glm::vec3& ray_dir,const Aabb& aabb);

	typedef RayAabbResult SegmentPlaneResult;

	static SegmentPlaneResult test_segment_plane(const glm::vec3& segment_begin,const glm::vec3& segment_end, const Plane& plane);
};
}//Collision
}//MinePlanner
#endif