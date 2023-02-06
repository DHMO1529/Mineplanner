#include "MinePlanner/graphic/GetResolution.hpp"

#include "MinePlanner/graphic/gl.hpp"
namespace MinePlanner{
namespace graphic{
Resolution GetResolution()
{
	int vpbuf[4] = {0};
	glGetIntegerv(GL_VIEWPORT, vpbuf);

	return Resolution(vpbuf[2],vpbuf[3]);
}
}//graphic
}//MinePlanner
