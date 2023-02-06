#include "MinePlanner/PointSet.hpp"
#include "MinePlanner/point_set_implementation.hpp"
namespace MinePlanner{
PointSet::PointSet():m_impl()
{
}
PointSet PointSet::create()
{
	PointSet instance;
	instance.m_impl.reset(new point_set_implementation());
	return instance;
}
bool PointSet::hasInstance()const
{
	return m_impl;
}
void PointSet::add(const Point& point)
{
	m_impl->add(point);
}
void PointSet::remove(const Point& point)
{
	m_impl->remove(point);
}
void PointSet::clear()
{
	m_impl->clear();
}
int PointSet::getNum()const
{
	return m_impl->getNum();
}

bool PointSet::isContain(const Point& point)const
{
	return m_impl->isContain(point);
}
void PointSet::for_each(Callback callback)const
{
	m_impl->for_each(callback);
}

PointSet PointSet::clone()const
{
	PointSet instance;
	instance.m_impl = m_impl->clone();
	return instance;
}
}//MinePlanner