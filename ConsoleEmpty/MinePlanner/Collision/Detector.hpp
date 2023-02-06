#ifndef MINEPLANNER_COLLISION_DETECTOR_HPP
#define MINEPLANNER_COLLISION_DETECTOR_HPP
#include <boost/shared_ptr.hpp>
#include <glm/glm.hpp>
#include "MinePlanner/Point.hpp"
#include "MinePlanner/PointSet.hpp"
#include "MinePlanner/Collision/Frustum.hpp"
#include "MinePlanner/Collision/RayCastResult.hpp"
/**
* 選択範囲クエリは点で行う
*/
namespace MinePlanner{
namespace Collision{
class detector_implementation;
class Detector
{
public:
	Detector();
	~Detector();
	static Detector create(int block_maximum_size = 512);//2のべき乗でないのは未定義

	bool hasInstance()const;

	void add(const Point& point);
	void remove(const Point& point);
	void clear();

	bool isAddAble(const Point& point)const;

	RayCastResult rayCast(const glm::vec3& begin,const glm::vec3& dir)const;
	RayCastResult rayCast(const glm::vec3& begin,const glm::vec3& dir,int edit_plane)const;
	PointSet frustumQuery(const Frustum& frustum)const;
private:
	boost::shared_ptr<detector_implementation> m_impl;
};
}//Collision
}//MinePlanner
#endif