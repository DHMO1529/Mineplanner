#ifndef MINEPRANNER_UI_SHAPE_PREVCANVAS_HPP
#define MINEPRANNER_UI_SHAPE_PREVCANVAS_HPP
#include <juce.h>
#include "MinePlanner/BlockSet.hpp"
#include "MinePlanner/graphic/Texture.hpp"
namespace MinePlanner{
namespace UI{
namespace Shape{
class PrevCanvas : public OpenGLComponent
{
public:
	PrevCanvas();
	virtual void newOpenGLContextCreated();
	virtual void releaseOpenGLContext();
	virtual void renderOpenGL();
	virtual void mouseWheelMove(const MouseEvent &e, float wheelIncrementX, float wheelIncrementY);
	virtual void mouseMove(const MouseEvent &e);
	virtual void mouseDrag(const MouseEvent &e);
	virtual void mouseDown(const MouseEvent& e);
	virtual void mouseUp(const MouseEvent &e);
	
	void setPrevBlocks(BlockSet blocks);
private:
	BlockSet m_prev_blocks;
	float m_camera_distance;
	float m_rotatex;
	float m_rotatey;
	int m_mousex,m_mousey;
};
}//Shape
}//UI
}//MinePlanner
#endif