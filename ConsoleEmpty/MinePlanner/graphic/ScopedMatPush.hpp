#ifndef MINEPLANNER_GRAPHIC_SCOPEDMATPUSH
#define MINEPLANNER_GRAPHIC_SCOPEDMATPUSH
#include <boost/noncopyable.hpp>
namespace MinePlanner{
namespace graphic{
class ScopedMatPush : private boost::noncopyable
{
public:
	ScopedMatPush();
	~ScopedMatPush();
};
}//graphic
}//MinePlanner
#endif