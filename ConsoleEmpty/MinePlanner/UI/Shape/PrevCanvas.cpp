#include "MinePlanner/UI/Shape/PrevCanvas.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Util/Lerp.hpp"
#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/DrawGrid.hpp"
#include "MinePlanner/graphic/DrawXYZAxis.hpp"
#include "MinePlanner/graphic/DrawBlock.hpp"
#include "MinePlanner/graphic/DrawContour.hpp"
#include "MinePlanner/UI/Widget/OpenglScreen.hpp"
namespace MinePlanner{
namespace UI{
namespace Shape{
PrevCanvas::PrevCanvas():
 m_prev_blocks()
,m_camera_distance(50.f)
,m_rotatex(-45.f)
,m_rotatey(45.f)
,m_mousex(0),m_mousey(0)
{
	this->setSize(250,250);
	m_prev_blocks = BlockSet::create();
	//コンテキストを共有（借りる
	this->shareWith( Widget::OpenGLScreen::getInstance()->getCurrentContext() );
}
void PrevCanvas::newOpenGLContextCreated()
{
	glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}
void PrevCanvas::releaseOpenGLContext()
{
}
void PrevCanvas::renderOpenGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f,1.f,5.f,300.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glm::vec3 eye = glm::vec3(0,0,1.f) * m_camera_distance;
	eye = glm::rotateX(eye,m_rotatex);
	eye = glm::rotateY(eye,m_rotatey);
	glm::vec3 lookat = glm::vec3(0,0,0);
	glm::vec3 up = glm::vec3(0,1.f,0);
	glm::mat4x4 view = glm::lookAt(eye,lookat,up);
	glLoadMatrixf(&view[0][0]);

	glClearColor(0.15f,0.15f,0.15f,1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.f,1.f,1.f);

	struct{
		void operator()(const Point& point,int blockId,const Pose& pose){
			graphic::drawBlock(point,blockId,pose);
		}
	}draw;

	graphic::beginBlockDraw();
	m_prev_blocks.for_each(draw);
	graphic::endBlockDraw();

	struct{
		void operator()(const Point& point,int blockId,const Pose& pose){
			graphic::DrawBlackContour(point);
		}
	}draw_contour;
	m_prev_blocks.for_each(draw_contour);

	graphic::DrawXYZAxis();
	graphic::DrawGrid(40,0);
}
void PrevCanvas::mouseWheelMove(const MouseEvent &e, float wheelIncrementX, float wheelIncrementY)
{
	Util::Lerpf lerp(1.f,0.1f,500.f,100.f);
	m_camera_distance -= wheelIncrementY * lerp(m_camera_distance);
	m_camera_distance = glm::clamp(m_camera_distance,5.f,500.f);

	this->repaint();
}
void PrevCanvas::mouseMove(const MouseEvent &e)
{
	m_mousex = e.x;
	m_mousey = e.y;
}
void PrevCanvas::mouseDrag(const MouseEvent &e)
{
	const int dx = e.x - m_mousex;
	const int dy = e.y - m_mousey;
	m_mousex = e.x;
	m_mousey = e.y;

	if(e.mods.isRightButtonDown())
	{
		m_rotatex -= 0.5f * dy;
		m_rotatey -= 0.5f * dx;
		m_rotatex = glm::clamp(m_rotatex,-89.f,89.f);
		this->repaint();
	}
}
void PrevCanvas::setPrevBlocks(BlockSet blocks)
{
	if(!blocks.hasInstance()){ return; }
	m_prev_blocks = blocks;

	this->repaint();
}
void PrevCanvas::mouseDown(const MouseEvent& e)
{
	if(e.mods.isRightButtonDown())
	{
		this->setMouseCursor(MouseCursor(MouseCursor::DraggingHandCursor));
	}
}
void PrevCanvas::mouseUp(const MouseEvent& e)
{
	if(e.mods.isRightButtonDown())
	{
		this->setMouseCursor(MouseCursor(MouseCursor::NormalCursor));
	}
}
}//Shape
}//UI
}//MinePlanner
