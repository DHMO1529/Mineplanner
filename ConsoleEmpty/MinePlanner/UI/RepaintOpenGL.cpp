#include "MinePlanner/UI/RepaintOpenGL.hpp"

#include "MinePlanner/UI/Widget/OpenglScreen.hpp"
namespace MinePlanner{
namespace UI{
void RepaintOpenGL()
{
	if(UI::Widget::OpenGLScreen::getInstance())
	{
		UI::Widget::OpenGLScreen::getInstance()->repaint();
	}
}
}//UI
}//MinePlanner