#include "MinePlanner/graphic/SetResolution.hpp"
#include "MinePlanner/graphic/gl.hpp"
namespace MinePlanner{
namespace graphic{
void setResolution(int w,int h)
{
	glViewport(0,0,w,h);
}
}//graphic
}//MinePlanner