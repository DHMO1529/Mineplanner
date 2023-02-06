#ifndef MINEPLANNER_COLLISION_DETECTOR_OCTNODE_HPP
#define MINEPLANNER_COLLISION_DETECTOR_OCTNODE_HPP
#include <vector>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include "MinePlanner/Point.hpp"
#include "MinePlanner/Collision/Aabb.hpp"
#include "MinePlanner/Collision/Frustum.hpp"
#include "MinePlanner/PointSet.hpp"
namespace MinePlanner{
namespace Collision{
class OctNode
{
public:
	OctNode(const Point& min,int size);

	static OctNode* alloc(const Point& min,int size);
	static void free(OctNode* p);
	struct deleter{
		void operator()(OctNode* p){
			OctNode::free(p);
		}
	};
	typedef boost::shared_ptr<OctNode> ptr;
	typedef boost::shared_ptr<const OctNode> cptr;

	static ptr create(const Point& min,int size);

	void addBlock(const Point& point);
	bool removeBlock(const Point& point);//@return is_remove_this
	void clear();

	bool isBlock()const;
	Point getBlockPoint()const;

	//è’ìÀîªíËÇÃÇΩÇﬂ
	glm::vec3 getOrigin()const;

	struct ray_cast_data{
		OctNode* node;
		glm::vec3 intersect_point;
	};
	void ray_cast(std::vector<ray_cast_data>& intersect_objects,const glm::vec3& ray_begin,const glm::vec3& ray_dir);

	void frustumQuery(PointSet points,const Frustum& frustum);

	bool isAddAble(const Point& point)const;
private:
	//é©ï™ÇÃãÛä‘ÇÃAABB
	Aabb getAabb()const;

	//ÇªÇÃèÍèäÇ™Ç«ÇÃéqãÛä‘Ç…ëÆÇ∑ÇÈÇ©ÅH
	int getSpaceIndex(const Point& point);

	boost::array<ptr,8> m_children;
	Point m_min;
	int m_size;
};
}//Collision
}//MinePlanner
#endif