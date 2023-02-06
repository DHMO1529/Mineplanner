#include "MinePlanner/graphic/ScopedAttribPush.hpp"

#include "MinePlanner/graphic/gl.hpp"
namespace MinePlanner{
namespace graphic{
ScopedAttribPush::ScopedAttribPush(unsigned mask)
{
	glPushAttrib(mask);
}
ScopedAttribPush::~ScopedAttribPush()
{
	glPopAttrib();
}
}//graphic
}//MinePlanner