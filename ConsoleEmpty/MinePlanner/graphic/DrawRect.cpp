#include "MinePlanner/graphic/DrawRect.hpp"

#include <limits>
#include <boost/scope_exit.hpp>

#include "MinePlanner/Rect.hpp"
#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/ScopedAttribPush.hpp"
#include "MinePlanner/graphic/GetResolution.hpp"

namespace MinePlanner{
namespace graphic{
void DrawRect(const Rect& rect)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	Resolution r = GetResolution();
	glOrtho(0,r.getWidth(),0,r.getHeight(),-1.0,1.0);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	int unused = 0;
	BOOST_SCOPE_EXIT((&unused))
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	BOOST_SCOPE_EXIT_END

	ScopedAttribPush sap(GL_CURRENT_BIT);
	glColor3f(1.f,1.f,1.f);
	//•`‰æ
	struct{
		float operator()(int v){
			return static_cast<float>(v);
		}
	}cast;
	glBegin(GL_LINE_LOOP);
	  const float z = 1.f - std::numeric_limits<float>::epsilon();
		glVertex3f(cast(rect.getX()),cast(rect.getY()),z);
		glVertex3f(cast(rect.getX() + rect.getWidth()),cast(rect.getY()),z);
		glVertex3f(cast(rect.getX() + rect.getWidth()),cast(rect.getY() + rect.getHeight()),z);
		glVertex3f(cast(rect.getX()),cast(rect.getY() + rect.getHeight()),z);
	glEnd();
}
}//graphic
}//MinePlanner