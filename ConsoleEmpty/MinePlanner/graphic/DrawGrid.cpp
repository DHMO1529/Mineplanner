#include "MinePlanner/graphic/DrawGrid.hpp"

#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/ScopedAttribPush.hpp"
#include "MinePlanner/graphic/ScopedMatPush.hpp"
#include "MinePlanner/graphic/BrendMode.hpp"

namespace MinePlanner{
namespace graphic{
void DrawGrid(int size,int height)
{
	const float sizef = static_cast<float>(size);
	const float heightf = static_cast<float>(height);

	ScopedMatPush smp;
	glTranslatef(0,heightf,0);
	glTranslatef(-(sizef / 2.f),0,-(sizef / 2.f));
	glTranslatef(-0.5f,-0.5f,-0.5f);

	const float LINE_LENGTH = sizef;
	ScopedAttribPush sap(GL_CURRENT_BIT);
	glColor4f(0.5f,0.5f,0.5f,1.f);
	glBegin(GL_LINES);
		for(int i = 0 ; i < size + 1 ; ++i)
		{
			glVertex3f(1.0f * i,0,0);
			glVertex3f(1.0f * i,0,LINE_LENGTH);
		}
		for(int i = 0 ; i < size + 1 ; ++i)
		{
			glVertex3f(0,0,1.0f * i);
			glVertex3f(LINE_LENGTH,0,1.0f * i);
		}
	glEnd();
}
}//graphic
}//MinePlanner