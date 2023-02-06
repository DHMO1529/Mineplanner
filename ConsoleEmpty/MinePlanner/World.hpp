#ifndef MINEPLANNER_WORLD_HPP
#define MINEPLANNER_WORLD_HPP
#include <boost/function.hpp>
#include "MinePlanner/Point.hpp"
#include "MinePlanner/PointSet.hpp"
#include "MinePlanner/Pose.hpp"
#include "MinePlanner/BlockSet.hpp"
#include "MinePlanner/Collision/Detector.hpp"
namespace MinePlanner{
class World
{
public:
	typedef boost::function<void(const Point& point,int blockId,const Pose& pose)> Callback;
public:
	bool add(const Point& point,int blockId,const Pose& pose);
	bool remove(const Point& point);
	bool isExist(const Point& target)const;
	Pose getPose(const Point& target)const;
	int getBlockID(const Point& target)const;
	int getBlockNum()const;
	void clear();

	void for_each(Callback callback)const;

	void update_collision(const PointSet hide_points);
	const Collision::Detector getDetector()const;
public:
	static World& instance()
	{
		static World instance;
		return instance;
	}
private:
	World();
private:
	BlockSet m_blockSet;
	Collision::Detector m_detector;
};
}//MinePlanner
#endif