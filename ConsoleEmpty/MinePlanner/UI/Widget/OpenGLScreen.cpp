#include "MinePlanner/UI/Widget/OpenglScreen.hpp"

#include "MinePlanner/graphic/graphic.hpp"
#include "MinePlanner/UI/EventHandler/Functions.hpp"

namespace MinePlanner{
namespace UI{
namespace Widget{
OpenGLScreen::OpenGLScreen()
{
	this->setPixelFormat(OpenGLPixelFormat(8, 8, 24, 0));
}
OpenGLScreen::~OpenGLScreen()
{
}
void OpenGLScreen::newOpenGLContextCreated()
{
	graphic::init();
}
void OpenGLScreen::releaseOpenGLContext()
{
	graphic::fin();
}
void OpenGLScreen::renderOpenGL()
{
	this->makeCurrentContextActive();
	graphic::Rendering();
}
void OpenGLScreen::resized()
{
	graphic::setResolution(this->getWidth(),this->getHeight());
}
void OpenGLScreen::mouseMove(const MouseEvent& e)
{
	EventHandler::mouseMove(e);
	this->repaint();
}
void OpenGLScreen::mouseDown(const MouseEvent& e)
{
	if(e.mods.isRightButtonDown())
	{
		this->setMouseCursor(MouseCursor(MouseCursor::DraggingHandCursor));
	}
	if(e.mods.isMiddleButtonDown())
	{
		this->setMouseCursor(MouseCursor(MouseCursor::UpDownLeftRightResizeCursor));
	}

	EventHandler::mouseDown(e);
	this->repaint();
}
void OpenGLScreen::mouseUp(const MouseEvent &e)
{
	if(e.mods.isRightButtonDown() || e.mods.isMiddleButtonDown())
	{
		this->setMouseCursor(MouseCursor(MouseCursor::NormalCursor));
	}

	EventHandler::mouseUp(e);
	this->repaint();
}
void OpenGLScreen::mouseDrag(const MouseEvent& e)
{
	EventHandler::mouseDrag(e);
	this->repaint();
}
void OpenGLScreen::mouseWheelMove(const MouseEvent &e, float wheelIncrementX, float wheelIncrementY)
{
	EventHandler::mouseWheelMove(e,wheelIncrementX,wheelIncrementY);
	this->repaint();
}
}//Widget
}//UI
}//MinePlanner