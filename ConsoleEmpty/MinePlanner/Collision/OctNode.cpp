#include "MinePlanner/Collision/OctNode.hpp"
#include <boost/pool/object_pool.hpp>
#include <boost/foreach.hpp>
#include "MinePlanner/Collision/Intersect.hpp"
namespace MinePlanner{
namespace Collision{
static boost::object_pool<OctNode> g_allocator;
OctNode* OctNode::alloc(const Point& min,int size)
{
	return g_allocator.construct(min,size);
}
void OctNode::free(OctNode* p)
{
	g_allocator.destroy(p);
}
OctNode::ptr OctNode::create(const Point& min,int size)
{
	return OctNode::ptr( OctNode::alloc(min,size) , deleter() );
}
OctNode::OctNode(const Point& min,int size):
 m_children()
,m_min(min)
,m_size(size)
{
}
void OctNode::addBlock(const Point& point)
{
	if(isBlock())
	{
		//I—¹
	}
	else
	{
		int index = getSpaceIndex(point);
		if(!m_children[index])
		{
			const int child_width = m_size / 2;
			const int& cw = child_width;
			OctNode::ptr new_node;
			switch(index)
			{
			case 0:
				new_node = OctNode::create(m_min,child_width);
				break;
			case 1:
				new_node = OctNode::create(Point::move(m_min, cw, 0, 0 ),cw);
				break;
			case 2:
				new_node = OctNode::create(Point::move(m_min, 0 , 0, cw),cw);
				break;
			case 3:
				new_node = OctNode::create(Point::move(m_min, cw, 0, cw),cw);
				break;
			case 4:
				new_node = OctNode::create(Point::move(m_min, 0, cw, 0 ),cw);
				break;
			case 5:
				new_node = OctNode::create(Point::move(m_min, cw,cw, 0 ),cw);
				break;
			case 6:
				new_node = OctNode::create(Point::move(m_min, 0, cw, cw),cw);
				break;
			case 7:
				new_node = OctNode::create(Point::move(m_min, cw,cw, cw),cw);
				break;
			}
			m_children[index] = new_node;
		}
		m_children[index]->addBlock(point);
	}
}
bool OctNode::removeBlock(const Point& point)
{
	if(isBlock())
	{
		return true;
	}
	const int index = getSpaceIndex(point);
	if(m_children[index])
	{
		if(m_children[index]->removeBlock(point))
		{
			m_children[index] = ptr();
			bool is_empty = true;
			BOOST_FOREACH(ptr child,m_children)
			{
				if(child)
				{
					is_empty = false;
				}
			}
			if(is_empty)
			{
				return true;
			}
		}
	}
	return false;
}
void OctNode::clear()
{
	for(int i = 0 ; i < 8 ; ++i)
	{
		m_children[i] = ptr();
	}
}
bool OctNode::isBlock()const
{
	return m_size == 1;
}
Point OctNode::getBlockPoint()const
{
	if(isBlock())
	{
		return m_min;
	}
	assert(0);
	return Point();
}
glm::vec3 OctNode::getOrigin()const
{
	Point p = getBlockPoint();
	return glm::vec3(static_cast<float>(p.getX()),static_cast<float>(p.getY()),static_cast<float>(p.getZ()));
}

void OctNode::ray_cast(std::vector<ray_cast_data>& intersect_objects,const glm::vec3& ray_begin,const glm::vec3& ray_dir)
{
	BOOST_FOREACH(ptr child,m_children)
	{
		if(child)
		{
			Intersect::RayAabbResult result = Intersect::test_ray_aabb(ray_begin,ray_dir,child->getAabb());
			if(result.is_intersect())
			{
				if(child->isBlock())
				{
					ray_cast_data data;
					data.node = child.get();
					data.intersect_point = result.get_intersect_point();
					intersect_objects.push_back( data );
				}
				else
				{
					child->ray_cast(intersect_objects,ray_begin,ray_dir);
				}
			}
		}
	}
}

void OctNode::frustumQuery(PointSet points,const Frustum& frustum)
{
	if(this->isBlock())
	{
		if(frustum.is_contain(this->getOrigin()))
		{
			points.add(this->getBlockPoint());
		}
	}
	else
	{
		BOOST_FOREACH(ptr child,m_children)
		{
			if(child)
			{
				child->frustumQuery(points,frustum);
			}
		}
	}
}
bool OctNode::isAddAble(const Point& point)const
{
	const Point& min = m_min;
	const Point max = Point::move(m_min,m_size-1,m_size-1,m_size-1);
	
	const int x = point.getX();
	const int y = point.getY();
	const int z = point.getZ();
	if(x < min.getX() || max.getX() < x){
		return false;
	}
	if(y < min.getY() || max.getY() < y){
		return false;
	}
	if(z < min.getZ() || max.getZ() < z){
		return false;
	}
	return true;
}
//private
Aabb OctNode::getAabb()const
{
	glm::vec3 aabb_min(
		static_cast<float>(m_min.getX()) - 0.5f,
		static_cast<float>(m_min.getY()) - 0.5f,
		static_cast<float>(m_min.getZ()) - 0.5f);

	const int offset = m_size - 1;
	Point aabb_min_i = Point::move(m_min,offset,offset,offset);
	glm::vec3 aabb_max(
		static_cast<float>(aabb_min_i.getX()) + 0.5f,
		static_cast<float>(aabb_min_i.getY()) + 0.5f,
		static_cast<float>(aabb_min_i.getZ()) + 0.5f);

	return Aabb::make_aabb(aabb_min,aabb_max);
}
int OctNode::getSpaceIndex(const Point& point)
{
	Point center(m_min.getX() + m_size / 2, m_min.getY() + m_size / 2, m_min.getZ() + m_size / 2);
	if(point.getY() < center.getY())
	{
		//0`3
		if(point.getZ() < center.getZ())
		{
			if(point.getX() < center.getX())
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			if(point.getX() < center.getX())
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
	else
	{
		//4`7
		if(point.getZ() < center.getZ())
		{
			if(point.getX() < center.getX())
			{
				return 4;
			}
			else
			{
				return 5;
			}
		}
		else
		{
			if(point.getX() < center.getX())
			{
				return 6;
			}
			else
			{
				return 7;
			}
		}
	}
	return -1;
}
}//Collision
}//MinePlanner
