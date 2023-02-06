#include "MinePlanner/graphic/DrawArrangeXYZ.hpp"
#include "MinePlanner/Point.hpp"
#include "MinePlanner/graphic/DisplayList.hpp"

#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/ScopedMatPush.hpp"
#include "MinePlanner/graphic/ScopedAttribPush.hpp"
#include "MinePlanner/graphic/BrendMode.hpp"
#include "MinePlanner/graphic/Resource.hpp"
namespace MinePlanner{
namespace graphic{

void DrawXYZArrow(float alpha)
{	
	ScopedAttribPush sap(GL_CURRENT_BIT);
	ScopedBrendMode sbm(BLEND_LINEAR);
	DisplayList display_list = getArrowDisplayList();

	glColor4f(1.f,0,0,alpha);
	display_list.call();//x

	{
		ScopedMatPush smp;
		glRotatef(90.f,0,0,1.f);
		glColor4f(0,1.f,0,alpha);
		display_list.call();//y
	}
	{
		ScopedMatPush smp;
		glRotatef(-90.f,0,1.f,0);
		glColor4f(0,0,1.f,alpha);
		display_list.call();//z
	}
}
void DrawArrangeXYZ(const Point& origin,float size,float alpha)
{
	struct{
		float operator()(int v){
			return static_cast<float>(v);
		}
	}cast;
	ScopedMatPush smp;
	glTranslatef(cast(origin.getX()),cast(origin.getY()),cast(origin.getZ()));
	glScalef(size,size,size);

	DrawXYZArrow(alpha);
}
}//graphic
}//MinePlanner