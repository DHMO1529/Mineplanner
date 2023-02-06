#include "MinePlanner/Operation/BasicWork.hpp"

#include "MinePlanner/World.hpp"
namespace MinePlanner{
namespace Operation{
namespace{
class AddWork : public Work
{
public:
	AddWork(const Point& point,int blockId,const Pose& pose):
	 m_point(point)
	,m_blockId(blockId)
	,m_pose(pose)
	{
	}
	virtual bool exe()
	{
		return World::instance().add(m_point,m_blockId,m_pose);
	}
	virtual void undo()
	{
		World::instance().remove(m_point);
	}
	virtual void redo()
	{
		if(!exe())
		{
			assert(0);
		}
	}
private:
	Point m_point;
	int m_blockId;
	Pose m_pose;
};

class SwapWork : public Work
{
public:
	SwapWork(const Point& dstpos,int blockId,const Pose& pose):
	 m_dstpos(dstpos)
	,m_to_blockId(blockId)
	,m_to_pose(pose)
	,m_from_blockId(0)
	,m_from_pose()
	{
	}
	virtual bool exe()
	{
		if(!World::instance().isExist(m_dstpos))
		{
			return false;
		}
		m_from_blockId = World::instance().getBlockID(m_dstpos);
		m_from_pose = World::instance().getPose(m_dstpos);
		if(m_from_blockId == m_to_blockId)
		{
			if(m_to_pose == m_from_pose)
			{
				return false;
			}
		}
		World::instance().remove(m_dstpos);
		World::instance().add(m_dstpos,m_to_blockId,m_to_pose);
		return true;
	}
	virtual void undo()
	{
		World::instance().remove(m_dstpos);
		World::instance().add(m_dstpos,m_from_blockId,m_from_pose);
	}
	virtual void redo()
	{
		if(!exe())
		{
			assert(0);
		}
	}
private:
	Point m_dstpos;
	int m_to_blockId;
	Pose m_to_pose;

	int m_from_blockId;
	Pose m_from_pose;
};

class DeleteWork : public Work
{
public:
	DeleteWork(const Point& target):
	 m_target(target)
	,m_blockId(0)
	,m_pose()
	{
	}

	virtual bool exe()
	{
		m_blockId = World::instance().getBlockID(m_target);
		m_pose = World::instance().getPose(m_target);
		return World::instance().remove(m_target);
	}
	virtual void undo()
	{
		World::instance().add(m_target,m_blockId,m_pose);
	}
	virtual void redo()
	{
		if(!exe())
		{
			assert(0);
		}
	}
private:
	Point m_target;

	int m_blockId;//çÌèúÇµÇΩid
	Pose m_pose;//çÌèúÇµÇΩépê®
};
}

Work::ptr BasicWork::createAdd(const Point& point,int blockId,const Pose& pose)
{
	return Work::ptr(new AddWork(point,blockId,pose));
}
Work::ptr BasicWork::createSwap(const Point& dstpos,int blockId,const Pose& pose)
{
	return Work::ptr(new SwapWork(dstpos,blockId,pose));
}
Work::ptr BasicWork::createDelete(const Point& target)
{
	return Work::ptr(new DeleteWork(target));
}
}//Operation
}//MinePlanner