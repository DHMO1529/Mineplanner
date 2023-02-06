#include "MinePlanner/graphic/Light.hpp"
#include "MinePlanner/graphic/gl.hpp"

#include "MinePlanner/graphic/Camera.hpp"
namespace MinePlanner{
namespace graphic{
void EnbaleLight()
{
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	const glm::vec3 lookat = g_camera->getLookAt();
	const glm::vec3 eye = g_camera->getEye();

	const glm::vec3 dir = lookat - eye;

	const float lightDiffuse[3] = {1.0f, 1.0f, 1.0f};
	const float lightAmbient[3] = {0.45f, 0.45f, 0.45f};
	const float lightSpecular[3] = {1.0f, 1.0f, 1.0f};

	float LightPos[4] = {0};
	for(int i = 0 ; i < 3 ; ++i)
	{
		LightPos[i] = -dir[i];
	}
	LightPos[3] = 0;

	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}
void DisableLight()
{
	glPopAttrib();
}
}//graphic
}//MinePlanner