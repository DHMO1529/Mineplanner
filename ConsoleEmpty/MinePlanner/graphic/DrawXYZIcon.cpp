#include "MinePlanner/graphic/DrawXYZIcon.hpp"

#include "MinePlanner/graphic/DrawArrangeXYZ.hpp"
#include "MinePlanner/Point.hpp"
#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/Camera.hpp"
#include "MinePlanner/graphic/GetResolution.hpp"
namespace MinePlanner{
namespace graphic{
void DrawXYZIcon()
{
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f,1.f,1.f,100.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glm::vec3 eye = g_camera->getEye() - g_camera->getLookAt();
	eye = glm::normalize( eye );
	eye = eye * 10.f;
	gluLookAt(eye.x,eye.y,eye.z, 0,0,0, 0,1.0,0);

	const int ICON_SIZE = 130;
	Resolution r = GetResolution();
	int x = r.getWidth() - ICON_SIZE;
	int y = r.getHeight() - ICON_SIZE;

	glViewport(x,y,ICON_SIZE,ICON_SIZE);

	DrawArrangeXYZ(Point(),4.f,1.f);

	glViewport(0,0,r.getWidth(),r.getHeight());
}
}//graphic
}//MinePlanner