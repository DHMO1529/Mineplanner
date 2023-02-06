#include "MinePlanner/graphic/DrawContour.hpp"
#include "MinePlanner/Point.hpp"

#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/ScopedAttribPush.hpp"
#include "MinePlanner/graphic/ScopedMatPush.hpp"
#include "MinePlanner/graphic/Resource.hpp"
namespace MinePlanner{
namespace graphic{
inline void DrawContour(const Point& position,float sizeRatio)
{
	ScopedMatPush smp;
	glTranslatef(static_cast<float>(position.getX()),
		           static_cast<float>(position.getY()),
							 static_cast<float>(position.getZ()));
	glScalef(sizeRatio,sizeRatio,sizeRatio);

	glLineWidth(2.0f);
		getContourDisplayList().call();
	glLineWidth(1.0f);
}
void DrawBlackContour(const Point& position)
{
	ScopedAttribPush sap(GL_CURRENT_BIT);
	glColor3f(0,0,0);
	DrawContour(position,1.01f);
}
void DrawRedContour(const Point& position)
{
	ScopedAttribPush sap(GL_CURRENT_BIT);
	glColor3f(1.f,0,0);
	DrawContour(position,1.02f);
}
}//graphic
}//MinePlanner