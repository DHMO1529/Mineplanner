#ifndef MINEPLANNER_OPERATION_BASICWORK
#define MINEPLANNER_OPERATION_BASICWORK
#include <boost/noncopyable.hpp>
#include "MinePlanner/Operation/Work.hpp"
#include "MinePlanner/Point.hpp"
#include "MinePlanner/Pose.hpp"
namespace MinePlanner{
namespace Operation{
class BasicWork : private boost::noncopyable
{
private:
	BasicWork();
public:
	static Work::ptr createAdd(const Point& point,int blockId,const Pose& pose);
	static Work::ptr createSwap(const Point& dstpos,int blockId,const Pose& pose);
	static Work::ptr createDelete(const Point& target);
};
}//Operation
}//MinePlanner
#endif