#include "MinePlanner/graphic/graphic.hpp"

#include <sstream>
#include <boost/format.hpp>
#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/Resource.hpp"
#include "MinePlanner/Log/LogManager.hpp"

namespace MinePlanner{
namespace graphic{
void init()
{
	glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

	g_pLogManager()->post("OpenGL ‰Šú‰»Š®—¹");

	if(true){
		std::stringstream ss;
		ss << boost::format("OpenGL Vender : %1%") % glGetString(GL_VENDOR);
		g_pLogManager()->post(ss.str());
	}
	if(true){
		std::stringstream ss;
		ss << boost::format("Graphics Board : %1%") % glGetString(GL_RENDERER);
		g_pLogManager()->post(ss.str());
	}
	if(true){
		std::stringstream ss;
		ss << boost::format("OpenGL Version : %1%\n") % glGetString(GL_VERSION);
		g_pLogManager()->post(ss.str());
	}

	InitResource();
}
void fin()
{
	FinResource();
}
}//graphic
}//MinePlanner