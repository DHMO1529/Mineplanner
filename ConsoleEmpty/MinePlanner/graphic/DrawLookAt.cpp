#include "MinePlanner/graphic/DrawLookAt.hpp"

#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/ScopedAttribPush.hpp"
#include "MinePlanner/graphic/ScopedMatPush.hpp"
#include "MinePlanner/graphic/BrendMode.hpp"
#include "MinePlanner/graphic/Camera.hpp"
namespace MinePlanner{
namespace graphic{
void DrawLookAt()
{
	ScopedAttribPush sap(GL_CURRENT_BIT);

	glm::vec3 lookAt = g_camera->getLookAt();
	glTranslatef(lookAt.x,lookAt.y,lookAt.z);

	glColor4f(0,1.f,1.f,0.3f);

	ScopedBrendMode sbm(BLEND_LINEAR);

	const float WIDTH = 7.f;
	glBegin(GL_LINES);
		glVertex3f(-WIDTH*0.5f,0,0);
		glVertex3f(WIDTH*0.5f,0,0);

		glVertex3f(0,-WIDTH*0.5f,0);
		glVertex3f(0,WIDTH*0.5f,0);

		glVertex3f(0,0,-WIDTH*0.5f);
		glVertex3f(0,0,WIDTH*0.5f);
	glEnd();
}
}//graphic
}//MinePlanner