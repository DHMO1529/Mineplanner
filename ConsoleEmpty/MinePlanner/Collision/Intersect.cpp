#include "MinePlanner/Collision/Intersect.hpp"

#include <algorithm>
#include <limits>
namespace MinePlanner{
namespace Collision{
//RayAabbResult
Intersect::RayAabbResult::RayAabbResult():m_is_intersect(false),m_intersect_point(){}
bool Intersect::RayAabbResult::is_intersect()const
{
	return m_is_intersect;
}
glm::vec3 Intersect::RayAabbResult::get_intersect_point()const
{
	return m_intersect_point;
}
Intersect::RayAabbResult Intersect::RayAabbResult::make_intersect(const glm::vec3& collision_point)
{
	RayAabbResult r;
	r.m_is_intersect = true;
	r.m_intersect_point = collision_point;
	return r;
}
Intersect::RayAabbResult Intersect::RayAabbResult::make_no_intersect()
{
	return Intersect::RayAabbResult();
}

//Ray-Aabb collision
Intersect::RayAabbResult Intersect::test_ray_aabb(const glm::vec3& ray_begin,const glm::vec3& ray_dir,const Aabb& aabb)
{
	const glm::vec3 dir = glm::normalize( ray_dir );
	const glm::vec3 min = aabb.getMin();
	const glm::vec3 max = aabb.getMax();

	//衝突する時間 時間１ : r
	
	//衝突最小時間 0にしておくことで、
	float t_min = std::numeric_limits<float>::min();
	//衝突最大時間
	float t_max = std::numeric_limits<float>::max();

	for(int i = 0 ; i < 3 ; ++i)
	{
		if(std::abs(dir[i]) < std::numeric_limits<float>::epsilon())
		{
			//レイはスラブに対して平行
			if(ray_begin[i] < min[i] || max[i] < ray_begin[i])
			{
				//さらにスラブの外にあるため、衝突しない
				return RayAabbResult::make_no_intersect();
			}
		}
		else
		{
			float t_in = (min[i] - ray_begin[i]) / dir[i];
			float t_out = (max[i] - ray_begin[i]) / dir[i];
			if(t_in > t_out)
			{
				//向きによっては時間が逆の時がある
				std::swap(t_in,t_out);
			}

			if(t_out < 0)
			{
				//t_out時間が-である→スラブの外でレイがスタートしている
				return RayAabbResult::make_no_intersect();
			}

			//範囲を狭めていく
			t_min = std::max( t_in , t_min );
			t_max = std::min( t_out , t_max );

			if(t_min > t_max)
			{
				//それぞれのスラブを通り抜けている時間に重なっている時間がない
				return RayAabbResult::make_no_intersect();
			}
		}
	}

	//それぞれのスラブを通り抜けている時間に、すべて重なっている時間がある
	return RayAabbResult::make_intersect( ray_begin + dir * t_min );
}

//ray-plane
Intersect::SegmentPlaneResult Intersect::test_segment_plane(const glm::vec3& segment_begin,const glm::vec3& segment_end, const Plane& plane)
{
	const glm::vec3& a = segment_begin;
	const glm::vec3& b = segment_end;
	const Plane& p = plane;

	const glm::vec3 ab = b - a;
	const float t = (p.get_d() - glm::dot( p.get_n() , a )) / glm::dot( p.get_n() , ab );
	if(0.f <= t && t <= 1.f)
	{
		return SegmentPlaneResult::make_intersect( a + ab * t );
	}

	return SegmentPlaneResult::make_no_intersect();
}
}//Collision
}//MinePlanner