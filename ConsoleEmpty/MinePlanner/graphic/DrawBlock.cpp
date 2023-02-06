#include "MinePlanner/graphic/DrawBlock.hpp"
#include "MinePlanner/graphic/Resource.hpp"
#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/Cube.hpp"
#include "MinePlanner/graphic/ScopedMatPush.hpp"
#include "MinePlanner/graphic/ScopedAttribPush.hpp"
#include "MinePlanner/graphic/BrendMode.hpp"
#include "MinePlanner/graphic/Resource.hpp"
#include "MinePlanner/World.hpp"

#include "MinePlanner/DataBase/DataBase.hpp"
namespace MinePlanner{
namespace graphic{
void beginBlockDraw()
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.05f);
	getTexture()->bind();
}
void endBlockDraw()
{
	getTexture()->unbind();
	glDisable(GL_ALPHA_TEST);
}
inline void draw(const Point& point,int blockId,const Pose& pose,float size)
{
	ScopedMatPush smp;
	//à íu
	glTranslatef(static_cast<float>(point.getX()),
								static_cast<float>(point.getY()),
								static_cast<float>(point.getZ()));
	//âÒì] x Å® y
	if(pose.get_rotatey()) /* y */
	{
		float rot = 90.f * pose.get_rotatey();
		glRotatef(rot,0,1.f,0);
	}
	if(pose.get_rotatex()) /* x */
	{
		float rot = 90.f * pose.get_rotatex();
		glRotatef(rot,1.f,0,0);
	}
	glScalef(size,size,size);
	DisplayList list = getBlockDisplayList(blockId);
	list.call();
}
void drawBlock(const Point& point,int blockId,const Pose& pose)
{
	draw(point,blockId,pose,1.f);
}
void drawBlock(const Point& point,int blockId,const Pose& pose,float alpha)
{
	ScopedBrendMode sbm(BLEND_LINEAR);
	ScopedAttribPush sap(GL_CURRENT_BIT);
	glColor4f(1.f,1.f,1.f,alpha);

	draw(point,blockId,pose,1.f);
}
void drawBlock(const Point& point,int blockId,const Pose& pose,float alpha,float size)
{
	ScopedBrendMode sbm(BLEND_LINEAR);
	ScopedAttribPush sap(GL_CURRENT_BIT);
	glColor4f(1.f,1.f,1.f,alpha);

	draw(point,blockId,pose,size);
}
}//graphic
}//MinePlanner
