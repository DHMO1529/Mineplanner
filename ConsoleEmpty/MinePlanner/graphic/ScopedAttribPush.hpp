#ifndef MINEPLANNER_GRAPHIC_SCOPEDATTRIBPUSH
#define MINEPLANNER_GRAPHIC_SCOPEDATTRIBPUSH
#include <boost/noncopyable.hpp>
namespace MinePlanner{
namespace graphic{
class ScopedAttribPush : private boost::noncopyable
{
public:
	ScopedAttribPush(unsigned mask);
	~ScopedAttribPush();
};
}//graphic
}//MinePlanner
#endif