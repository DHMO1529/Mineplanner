#include "MinePlanner/World.hpp"
namespace MinePlanner{
World::World()
{
	m_blockSet = BlockSet::create();
	m_detector = Collision::Detector::create(512);
}
bool World::add(const Point& point,int blockId,const Pose& pose)
{
	if(!m_detector.isAddAble(point))
	{
		return false;
	}
	if(m_blockSet.isExist(point))
	{
		return false;
	}
	m_blockSet.add(point,blockId,pose);
	m_detector.add(point);
	return true;
}
bool World::remove(const Point& point)
{
	if(!m_blockSet.isExist(point))
	{
		return false;
	}
	m_blockSet.remove(point);
	m_detector.remove(point);
	return true;
}

bool World::isExist(const Point& target)const
{
	return m_blockSet.isExist(target);
}
Pose World::getPose(const Point& target)const
{
	return m_blockSet.getPose(target);
}
int World::getBlockID(const Point& target)const
{
	return m_blockSet.getBlockID(target);
}
int World::getBlockNum()const
{
	return m_blockSet.getBlockNum();
}
void World::clear()
{
	m_blockSet.clear();
	m_detector.clear();
}
void World::for_each(Callback callback)const
{
	m_blockSet.for_each(callback);
}
void World::update_collision(const PointSet hide_points)
{
	m_detector.clear();
	auto each = [&hide_points,this](const Point& point,int blockId,const Pose& pose)
	{
		if(!hide_points.isContain(point))
		{
			//âBÇµÉuÉçÉbÉNÇ≈ÇÕÇ»Ç¢
			m_detector.add(point);
		}
	};
	m_blockSet.for_each(each);
}
const Collision::Detector World::getDetector()const
{
	return m_detector;
}
}//MinePlanner