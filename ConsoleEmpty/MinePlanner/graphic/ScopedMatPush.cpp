#include "MinePlanner/graphic/ScopedMatPush.hpp"

#include "MinePlanner/graphic/gl.hpp"
namespace MinePlanner{
namespace graphic{
ScopedMatPush::ScopedMatPush()
{
	glPushMatrix();
}
ScopedMatPush::~ScopedMatPush()
{
	glPopMatrix();
}
}//graphic
}//MinePlanner