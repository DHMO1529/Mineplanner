#include "MinePlanner/BlockSet.hpp"
#include "MinePlanner/block_set_implementation.hpp"
namespace MinePlanner{
BlockSet::BlockSet():m_impl(){}
BlockSet BlockSet::create()
{
	BlockSet instance;
	instance.m_impl.reset(new block_set_implementation());
	return instance;
}
bool BlockSet::hasInstance()const
{
	return m_impl;
}
void BlockSet::add(const Point& point,int blockId,const Pose& pose)
{
	m_impl->add(point,blockId,pose);
}
void BlockSet::remove(const Point& point)
{
	m_impl->remove(point);
}

void BlockSet::clear()
{
	m_impl->clear();
}

bool BlockSet::isExist(const Point& target)const
{
	return m_impl->isExist(target);
}
void BlockSet::setPose(const Point& target,const Pose& pose)
{
	m_impl->setPose(target,pose);
}
void BlockSet::setBlockID(const Point& target,int blockid)
{
	m_impl->setBlockID(target,blockid);
}
Pose BlockSet::getPose(const Point& target)const
{
	return m_impl->getPose(target);
}
int BlockSet::getBlockID(const Point& target)const
{
	return m_impl->getBlockID(target);
}
int BlockSet::getBlockNum()const
{
	return m_impl->getBlockNum();
}
Point BlockSet::getOrigin()const
{
	return m_impl->getOrigin();
}
int BlockSet::getMaxWidth()const
{
	return m_impl->getMaxWidth();
}
void BlockSet::move(int x,int y,int z)
{
	m_impl->move(x,y,z);
}
void BlockSet::rotate(int x,int y,int z)
{
	m_impl->rotate(x,y,z);
}
void BlockSet::reverse(bool x,bool y,bool z)
{
	m_impl->reverse(x,y,z);
}
void BlockSet::for_each(Callback callback)const
{
	m_impl->for_each(callback);
}
BlockSet BlockSet::clone()const
{
	BlockSet instance;
	instance.m_impl = m_impl->clone();
	return instance;
}
}//MinePlanner