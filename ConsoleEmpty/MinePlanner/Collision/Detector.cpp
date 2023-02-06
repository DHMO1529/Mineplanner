#include "MinePlanner/Collision/Detector.hpp"
#include "MinePlanner/Collision/detector_implementation.hpp"
namespace MinePlanner{
namespace Collision{
Detector::Detector():m_impl(){}
Detector::~Detector(){}

bool is_power_2(int x)
{
	return (x & (x-1)) == 0;
}
Detector Detector::create(int block_maximum_size)
{
	if(!is_power_2(block_maximum_size))
	{
		assert(0);
		return Detector();
	}
	Detector detector;
	detector.m_impl.reset(new detector_implementation(block_maximum_size));
	return detector;
}

bool Detector::hasInstance()const
{
	return m_impl;
}
void Detector::add(const Point& point)
{
	m_impl->add(point);
}
void Detector::remove(const Point& point)
{
	m_impl->remove(point);
}
void Detector::clear()
{
	m_impl->clear();
}
bool Detector::isAddAble(const Point& point)const
{
	return m_impl->isAddAble(point);
}
RayCastResult Detector::rayCast(const glm::vec3& begin,const glm::vec3& dir)const
{
	return m_impl->rayCast(begin,dir);
}
RayCastResult Detector::rayCast(const glm::vec3& begin,const glm::vec3& dir,int edit_plane)const
{
	return m_impl->rayCast(begin,dir,edit_plane);
}
PointSet Detector::frustumQuery(const Frustum& frustum)const
{
	return m_impl->frustumQuery(frustum);
}
}//Collision
}//MinePlanner