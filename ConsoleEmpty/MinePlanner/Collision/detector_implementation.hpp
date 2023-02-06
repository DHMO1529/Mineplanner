#ifndef MINEPLANNER_COLLISION_DETECTOR_IMPLEMENTATION_HPP
#define MINEPLANNER_COLLISION_DETECTOR_IMPLEMENTATION_HPP
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/foreach.hpp>
#include "MinePlanner/PointSet.hpp"
#include "MinePlanner/Collision/Frustum.hpp"
#include "MinePlanner/Collision/RayCastResult.hpp"
#include "MinePlanner/Collision/OctNode.hpp"
#include "MinePlanner/Collision/Intersect.hpp"
namespace MinePlanner{
namespace Collision{
inline Point getNextPoint(const Point& target,glm::vec3 intersect_point)
{
	glm::vec3 origin(
		static_cast<float>(target.getX()),
		static_cast<float>(target.getY()),
		static_cast<float>(target.getZ()));
	const float epsilon = 0.0001f;
	if(glm::equalEpsilon(origin.x - 0.5f,intersect_point.x,epsilon))
	{
		return Point::move(target,-1,0,0);
	}
	if(glm::equalEpsilon(origin.x + 0.5f,intersect_point.x,epsilon))
	{
		return Point::move(target,1,0,0);
	}
	if(glm::equalEpsilon(origin.y - 0.5f,intersect_point.y,epsilon))
	{
		return Point::move(target,0,-1,0);
	}
	if(glm::equalEpsilon(origin.y + 0.5f,intersect_point.y,epsilon))
	{
		return Point::move(target,0,1,0);
	}
	if(glm::equalEpsilon(origin.z - 0.5f,intersect_point.z,epsilon))
	{
		return Point::move(target,0,0,-1);
	}
	if(glm::equalEpsilon(origin.z + 0.5f,intersect_point.z,epsilon))
	{
		return Point::move(target,0,0,1);
	}
	std::cout << "getNextPoint unhit" << std::endl;
	return target;
}

class detector_implementation
{
public:
	detector_implementation(int block_maximum_size)
	{
		int m = -(block_maximum_size / 2 - 1);
		Point min(m,m,m);
		m_root = OctNode::create(min,block_maximum_size);
	}
	void add(const Point& point)
	{
		m_root->addBlock(point);
	}
	void remove(const Point& point)
	{
		m_root->removeBlock(point);
	}
	void clear()
	{
		m_root->clear();
	}
	bool isAddAble(const Point& point)const
	{
		return m_root->isAddAble(point);
	}
	RayCastResult rayCast(const glm::vec3& begin,const glm::vec3& dir)const
	{
		std::vector<OctNode::ray_cast_data> ray_cast_datas;
		m_root->ray_cast(ray_cast_datas,begin,dir);

		if(ray_cast_datas.empty())
		{
			return RayCastResult::make_no_intersect();
		}

		float nearest_dist = std::numeric_limits<float>::max();
		const OctNode* nearest_node = 0;
		glm::vec3 nearest_intersect_point;
		BOOST_FOREACH(const OctNode::ray_cast_data& data,ray_cast_datas)
		{
			const float dist = glm::length( data.node->getOrigin() - begin );
			if(nearest_dist >= dist)
			{
				nearest_dist = dist;
				nearest_node = data.node;
				nearest_intersect_point = data.intersect_point;
			}
		}
		Point next = getNextPoint(nearest_node->getBlockPoint(),nearest_intersect_point);
		return RayCastResult::make_intersect(nearest_node->getBlockPoint(),next);
	}
	RayCastResult rayCast(const glm::vec3& begin,const glm::vec3& dir,int edit_plane)const
	{
		//まず普通にレイキャスト
		RayCastResult result = rayCast(begin,dir);

		const glm::vec3 direction = glm::normalize( dir ); //レイの向き
		const glm::vec3 end = begin + direction * 1000.f;  //レイの終点
		const float h = static_cast<float>(edit_plane) - 0.5f; //編集プレーンの高さ
		const Plane plane = Plane::make_plane(glm::vec3(0,h,0),glm::vec3(10.f,h,0),glm::vec3(0,h,-10.f)); //編集プレーン
		
		//編集プレーンへレイキャスト
		Intersect::SegmentPlaneResult segment_plane_result = Intersect::test_segment_plane(begin,end,plane);

		//プレーンへの衝突位置からワールドの位置を算出
		auto get_point_from_colpos = 
			[](const glm::vec3& pos,const glm::vec3& ray_dir) -> Point
			{
				const int x = static_cast<int>( boost::math::round(pos.x) );
				const int y = static_cast<int>( boost::math::round(pos.y + 0.5f) );
				const int z = static_cast<int>( boost::math::round(pos.z) );
				if(ray_dir.y > 0)
				{
					return Point(x,y-1,z);
				}
				return Point(x,y,z);
			};

		if(segment_plane_result.is_intersect())
		{
			if(result.is_intersect())
			{
				//普通レイキャストにもプレーンにも当たっている
				const Point plane_point = get_point_from_colpos( segment_plane_result.get_intersect_point() , direction );
				const Point block_point = result.getNext();

				auto cast = [](int v){return static_cast<float>(v);};

				glm::vec3 plane_pointf(cast(plane_point.getX()),cast(plane_point.getY()),cast(plane_point.getZ()));
				glm::vec3 block_pointf(cast(block_point.getX()),cast(block_point.getY()),cast(block_point.getZ()));
				if(glm::length(begin - plane_pointf) > glm::length(begin - block_pointf))
				{
					//ブロックの方が近い
					return result;
				}
				else
				{
					//プレーンの方が近い
					return RayCastResult::make_intersect(plane_point,plane_point);
				}
			}
			else
			{
				//プレーンにだけ当たってる
				const Point point = get_point_from_colpos( segment_plane_result.get_intersect_point() , direction );
				return RayCastResult::make_intersect(point,point);
			}
		}
		else
		{
			//プレーンには当たらなかったので　普通のレイキャスト結果を返す
			return result;
		}
		assert(0);
		return RayCastResult();
	}
	PointSet frustumQuery(const Frustum& frustum)const
	{
		PointSet points = PointSet::create();
		m_root->frustumQuery(points,frustum);
		return points;
	}
private:
	OctNode::ptr m_root;
};

}//Collision
}//MinePlanner
#endif