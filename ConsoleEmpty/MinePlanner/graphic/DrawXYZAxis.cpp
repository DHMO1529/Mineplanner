#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/ScopedAttribPush.hpp"
#include "MinePlanner/graphic/ScopedMatPush.hpp"
const float XYZAXIS_LENGTH = 50.f;
namespace MinePlanner{
namespace graphic{
namespace{
void draw()
{
	ScopedAttribPush Att(GL_CURRENT_BIT);

	glBegin(GL_LINES);
		glColor3f(1.f, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(1.f, 0, 0);
				
		glColor3f(0, 1.f, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1.f, 0);

		glColor3f(0, 0, 1.f);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1.f);
	glEnd();
}
}
void DrawXYZAxis()
{
	ScopedMatPush smp;
	glScalef(XYZAXIS_LENGTH,XYZAXIS_LENGTH,XYZAXIS_LENGTH);
	draw();
}
}//graphic
}//MinePlanner
