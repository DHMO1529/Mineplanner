#ifndef MINEPLANNER_UI_WIDGET_OPENGLSCREEN
#define MINEPLANNER_UI_WIDGET_OPENGLSCREEN
#include <juce.h>
#include "Util/SingleInstanceAndGlobalAcess.hpp"
namespace MinePlanner{
namespace UI{
namespace Widget{
class OpenGLScreen : public OpenGLComponent,public Util::SingleInstanceAndGlobalAcess<OpenGLScreen>
{
public:
	OpenGLScreen();
	~OpenGLScreen();

	virtual void newOpenGLContextCreated();
	virtual void releaseOpenGLContext();
	virtual void renderOpenGL();

	virtual void resized();
	virtual void mouseMove(const MouseEvent& e);
	virtual void mouseDown(const MouseEvent& e);
	virtual void mouseUp(const MouseEvent &e);
	virtual void mouseDrag(const MouseEvent& e);
	virtual void mouseWheelMove(const MouseEvent &e, float wheelIncrementX, float wheelIncrementY);
};
}//Widget
}//UI
}//MinePlanner
#endif