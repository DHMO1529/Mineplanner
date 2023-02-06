#include "MinePlanner/graphic/Cube.hpp"

#include <boost/array.hpp>
#include <glm/glm.hpp>
#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"

namespace MinePlanner{
namespace graphic{
void Cube::drawTop(int blockId)
{
	const float v = 0.5f;
	const float h = v;
	const boost::array<glm::vec3,4> vertices = 
	{
		glm::vec3(-v,h,-v),
		glm::vec3(-v,h,v),
		glm::vec3(v,h,v),
		glm::vec3(v,h,-v),
	};
	DataBase::TextureData texture = DataBase::getFaceUV(blockId,DataBase::FACE_TOP);

	glBegin(GL_QUADS);
	{
		glNormal3f(0,1.f,0);
		for(int i = 0 ; i < 4 ; ++i)
		{
			const DataBase::UV uv = texture.get_uv(i);
			glTexCoord2f(uv.get_u(),uv.get_v());
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
		}
	}
	glEnd();
}
void Cube::drawBottom(int blockId)
{
	const float v = 0.5f;
	const float h = -v;
	const boost::array<glm::vec3,4> vertices = 
	{
		glm::vec3(-v,h,v),
		glm::vec3(-v,h,-v),
		glm::vec3(v,h,-v),
		glm::vec3(v,h,v),
	};
	DataBase::TextureData texture = DataBase::getFaceUV(blockId,DataBase::FACE_BUTTOM);

	glBegin(GL_QUADS);
	{
		glNormal3f(0,-1.f,0);
		for(int i = 0 ; i < 4 ; ++i)
		{
			const DataBase::UV uv = texture.get_uv(i);
			glTexCoord2f(uv.get_u(),uv.get_v());
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
		}
	}
	glEnd();
}
void Cube::drawFront(int blockId)
{
	const float v = 0.5f;
	const float z = v;
	const boost::array<glm::vec3,4> vertices = 
	{
		glm::vec3(-v,v,z),
		glm::vec3(-v,-v,z),
		glm::vec3(v,-v,z),
		glm::vec3(v,v,z),
	};

	DataBase::TextureData texture = DataBase::getFaceUV(blockId,DataBase::FACE_FRONT);

	glBegin(GL_QUADS);
	{
		glNormal3f(0,0,1.f);
		for(int i = 0 ; i < 4 ; ++i)
		{
			const DataBase::UV uv = texture.get_uv(i);
			glTexCoord2f(uv.get_u(),uv.get_v());
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
		}
	}
	glEnd();
}
void Cube::drawLeft(int blockId)
{
	const float v = 0.5f;
	const float x = -v;
	const boost::array<glm::vec3,4> vertices = 
	{
		glm::vec3(x,v,-v),
		glm::vec3(x,-v,-v),
		glm::vec3(x,-v,v),
		glm::vec3(x,v,v),
	};

	DataBase::TextureData texture = DataBase::getFaceUV(blockId,DataBase::FACE_LEFT);

	glBegin(GL_QUADS);
	{
		glNormal3f(-1.f,0,0);
		for(int i = 0 ; i < 4 ; ++i)
		{
			const DataBase::UV uv = texture.get_uv(i);
			glTexCoord2f(uv.get_u(),uv.get_v());
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
		}
	}
	glEnd();
}
void Cube::drawRight(int blockId)
{
	const float v = 0.5f;
	const float x = v;
	const boost::array<glm::vec3,4> vertices = 
	{
		glm::vec3(x,v,v),
		glm::vec3(x,-v,v),
		glm::vec3(x,-v,-v),
		glm::vec3(x,v,-v),
	};

	DataBase::TextureData texture = DataBase::getFaceUV(blockId,DataBase::FACE_LEFT);

	glBegin(GL_QUADS);
	{
		glNormal3f(1.f,0,0);
		for(int i = 0 ; i < 4 ; ++i)
		{
			const DataBase::UV uv = texture.get_uv(i);
			glTexCoord2f(uv.get_u(),uv.get_v());
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
		}
	}
	glEnd();
}
void Cube::drawBack(int blockId)
{
	const float v = 0.5f;
	const float z = -v;
	const boost::array<glm::vec3,4> vertices = 
	{
		glm::vec3(v,v,z),
		glm::vec3(v,-v,z),
		glm::vec3(-v,-v,z),
		glm::vec3(-v,v,z),
	};

	DataBase::TextureData texture = DataBase::getFaceUV(blockId,DataBase::FACE_BACK);

	glBegin(GL_QUADS);
	{
		glNormal3f(0,0,-1.f);
		for(int i = 0 ; i < 4 ; ++i)
		{
			const DataBase::UV uv = texture.get_uv(i);
			glTexCoord2f(uv.get_u(),uv.get_v());
			glVertex3f(vertices[i].x,vertices[i].y,vertices[i].z);
		}
	}
	glEnd();
}
}//graphic
}//MinePlanner
