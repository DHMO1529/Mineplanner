#include "MinePlanner/Operation/BatchWork.hpp"

#include <vector>
#include <boost/foreach.hpp>
#include "MinePlanner/World.hpp"
namespace MinePlanner{
namespace Operation{
namespace{
class BatchAdd : public Work
{
public:
	BatchAdd(BlockSet blockSet):m_add_blocks(blockSet)
	{
	}
	virtual bool exe()
	{
		auto add = [this](const Point& point,int blockId,const Pose& pose)
		{
			if(!World::instance().isExist(point))
			{
				//ブロックが存在しないときだけ
				const block_container added_block = {point, blockId, pose};
				m_added.push_back(added_block);
				World::instance().add(point,blockId,pose);
			}
		};
		m_add_blocks.for_each(add);
		m_add_blocks = BlockSet();
		return true;
	}
	virtual void undo()
	{
		BOOST_FOREACH(const block_container& b,m_added)
		{
			World::instance().remove(b.point);
		}
	}
	virtual void redo()
	{
		BOOST_FOREACH(const block_container& b,m_added)
		{
			World::instance().add(b.point,b.blockId,b.pose);
		}
	}
private:
	BlockSet m_add_blocks;
	
	struct block_container{
		Point point;
		int blockId;
		Pose pose;
	};
	std::vector<block_container> m_added;
};

class BatchDelete : public Work
{
public:
	BatchDelete(PointSet pointSet):
	 m_delete_target(pointSet)
	,m_deleted()
	{
	}
	virtual bool exe()
	{
		auto delete_op = [this](const Point& point)
		{
			if(World::instance().isExist(point))
			{
				//削除できるときだけ
				const block_container deleted_block = {
					point,
					World::instance().getBlockID(point),
					World::instance().getPose(point),
				};
				m_deleted.push_back(deleted_block);
				World::instance().remove(point);
			}
		};
		m_delete_target.for_each(delete_op);
		m_delete_target = PointSet();
		return true;
	}
	virtual void undo()
	{
		BOOST_FOREACH(const block_container& b,m_deleted)
		{
			World::instance().add(b.point,b.blockId,b.pose);
		}
	}
	virtual void redo()
	{
		BOOST_FOREACH(const block_container& b,m_deleted)
		{
			World::instance().remove(b.point);
		}
	}
private:
	PointSet m_delete_target;
	
	struct block_container{
		Point point;
		int blockId;
		Pose pose;
	};
	std::vector<block_container> m_deleted;
};

//塗りつぶし
class BatchFill : public Work
{
public:
	BatchFill(PointSet pointSet,int blockId,const Pose& pose):
	 m_target_points(pointSet)
	,m_to_blockId(blockId)
	,m_to_pose(pose)
	{
	}
	virtual bool exe()
	{
		auto fill = [this](const Point& point)
		{
			if(World::instance().isExist(point))
			{
				//塗りつぶせるときだけ
				block_container deleted_block = {
					point,
					World::instance().getBlockID(point),
					World::instance().getPose(point),
				};
				m_deleted.push_back(deleted_block);
				World::instance().remove(point);

				block_container added_block = {point, m_to_blockId, m_to_pose};
				m_added.push_back(added_block);
				World::instance().add(point,m_to_blockId,m_to_pose);
			}
		};
		m_target_points.for_each(fill);

		m_target_points = PointSet();
		return true;
	}
	virtual void undo()
	{
		BOOST_FOREACH(const block_container& b,m_added)
		{
			World::instance().remove(b.point);
		}
		BOOST_FOREACH(const block_container& b,m_deleted)
		{
			World::instance().add(b.point,b.blockId,b.pose);
		}
	}
	virtual void redo()
	{
		BOOST_FOREACH(const block_container& b,m_deleted)
		{
			World::instance().remove(b.point);
		}
		BOOST_FOREACH(const block_container& b,m_added)
		{
			World::instance().add(b.point,b.blockId,b.pose);
		}
	}
private:
	PointSet m_target_points;
	int m_to_blockId;
	Pose m_to_pose;

	struct block_container{
		Point point;
		int blockId;
		Pose pose;
	};
	std::vector<block_container> m_deleted;
	std::vector<block_container> m_added;
};

//置換
class BatchReplace : public Work
{
public:
	BatchReplace(PointSet pointSet,int targetId,int blockId,const Pose& pose):
	 m_target_points(pointSet)
	,m_target_blockId(targetId)
	,m_to_blockId(blockId)
	,m_to_pose(pose)
	{
	}
	virtual bool exe()
	{
		auto replace = [this](const Point& point)
		{
			if(World::instance().isExist(point))
			{
				if(World::instance().getBlockID(point) == m_target_blockId)
				{
					//おきかえれるときだけ
					block_container deleted_block = {
						point,
						m_target_blockId,
						World::instance().getPose(point),
					};
					m_deleted.push_back(deleted_block);
					World::instance().remove(point);

					block_container added_block = {
						point,
						m_to_blockId,
						m_to_pose
					};
					m_added.push_back(added_block);
					World::instance().add(point,m_to_blockId,m_to_pose);
				}
			}
		};
		m_target_points.for_each(replace);
		m_target_points = PointSet();
		return true;
	}
	virtual void undo()
	{
		BOOST_FOREACH(const block_container& b,m_added)
		{
			World::instance().remove(b.point);
		}
		BOOST_FOREACH(const block_container& b,m_deleted)
		{
			World::instance().add(b.point,b.blockId,b.pose);
		}
	}
	virtual void redo()
	{
		BOOST_FOREACH(const block_container& b,m_deleted)
		{
			World::instance().remove(b.point);
		}
		BOOST_FOREACH(const block_container& b,m_added)
		{
			World::instance().add(b.point,b.blockId,b.pose);
		}
	}
private:
	PointSet m_target_points;
	int m_target_blockId;
	int m_to_blockId;
	Pose m_to_pose;

	struct block_container{
		Point point;
		int blockId;
		Pose pose;
	};
	std::vector<block_container> m_deleted;
	std::vector<block_container> m_added;
};
}
Work::ptr BatchWork::createBatchAdd(BlockSet blockSet)
{
	return Work::ptr(new BatchAdd(blockSet));
}
Work::ptr BatchWork::createBatchDelete(PointSet pointSet)
{
	return Work::ptr(new BatchDelete(pointSet));
}
Work::ptr BatchWork::createBatchFill(PointSet pointSet,int blockId,const Pose& pose)
{
	return Work::ptr(new BatchFill(pointSet,blockId,pose));
}
Work::ptr BatchWork::createBatchReplace(PointSet pointSet,int targetId,int blockId,const Pose& pose)
{
	return Work::ptr( new BatchReplace(pointSet,targetId,blockId,pose) );
}
}//Operation
}//MinePlanner