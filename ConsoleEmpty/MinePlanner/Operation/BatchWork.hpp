#ifndef MINEPLANNER_OPERATION_BATCHWORK
#define MINEPLANNER_OPERATION_BATCHWORK
#include <boost/noncopyable.hpp>
#include "MinePlanner/Operation/Work.hpp"
#include "MinePlanner/BlockSet.hpp"
#include "MinePlanner/PointSet.hpp"
#include "MinePlanner/Pose.hpp"

namespace MinePlanner{
class BlockInfo;
namespace Operation{
class BatchWork : private boost::noncopyable
{
private:
	BatchWork();
public:
	static Work::ptr createBatchAdd(BlockSet blockSet);
	static Work::ptr createBatchDelete(PointSet pointSet);
	static Work::ptr createBatchFill(PointSet pointSet,int blockId,const Pose& pose);
	static Work::ptr createBatchReplace(PointSet pointSet,int targetId,int blockId,const Pose& pose);
};
}//Operation
}//MinePlanner
#endif