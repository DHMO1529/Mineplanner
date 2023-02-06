#ifndef MINEPLANNER_OPERATION_UNREDOSYSTEM
#define MINEPLANNER_OPERATION_UNREDOSYSTEM
#include <boost/shared_ptr.hpp>
#include "MinePlanner/Operation/Work.hpp"
namespace MinePlanner{
namespace Operation{
class UnRedoSystem
{
public:
	virtual ~UnRedoSystem(){}
public:
	virtual void execute(Work::ptr work) = 0;
	virtual void undo() = 0;
	virtual void redo() = 0;

	virtual void clear() = 0;
public:
	typedef boost::shared_ptr<UnRedoSystem> ptr;
	static ptr create();
};
}//Operation
}//MinePlanner
#endif