#include "MinePlanner/graphic/BrendMode.hpp"
#include <stack>
#include "MinePlanner/graphic/gl.hpp"
namespace MinePlanner{
namespace graphic{
void SetBrendMode(BrendMode BM)
{
	switch(BM)
	{
	case BLEND_OPAQUE:
		glDisable(GL_BLEND);
		break;
	case BLEND_LINEAR:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case BLEND_ADDITIVE:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		break;
	}
}
namespace{
std::stack<BrendMode> g_brendStack;
}
ScopedBrendMode::ScopedBrendMode(BrendMode brendMode)
{
	g_brendStack.push(brendMode);
	SetBrendMode(brendMode);
}
ScopedBrendMode::~ScopedBrendMode()
{
	g_brendStack.pop();
	if(g_brendStack.empty())
	{
		SetBrendMode(BLEND_OPAQUE);
	}
	else
	{
		SetBrendMode( g_brendStack.top() );
	}
}
}//graphic
}//MinePlanner