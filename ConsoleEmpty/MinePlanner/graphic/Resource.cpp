#include "MinePlanner/graphic/Resource.hpp"

#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <MinePlanner/graphic/gl.hpp>
#include "MinePlanner/DataBase/DataBase.hpp"
#include "MinePlanner/graphic/Model.hpp"
#include "MinePlanner/graphic/Cube.hpp"
namespace MinePlanner{
namespace graphic{
//global varialble
static Texture::ptr g_texture;
static DisplayList g_arrowDisplayList;
static boost::unordered_map<int,DisplayList> g_models;
static DisplayList g_contourDisplayList;

void InitResource()
{
	//ÉeÉNÉXÉ`ÉÉ
	g_texture = Texture::createFromArchive("BlockTexture.png");

	//ñÓàÛ
	g_arrowDisplayList = DisplayList::create();
	{
		Model::ptr model = Model::createFromArchiveWaveFront("Arrow.obj");
		g_arrowDisplayList.newList();
			glBegin(GL_TRIANGLES);
			const int numVertex = model->numVertex();
			for(int i = 0 ; i < numVertex ; ++i)
			{		
				glm::vec3 vertex = model->getVertex(i);
				glVertex3f(vertex.x,vertex.y,vertex.z);
			}
			glEnd();
		g_arrowDisplayList.endList();
	}

	//ÉÇÉfÉã
	{
		std::vector<int> model_draw_id_list = DataBase::getModelDrawBlockList();
		BOOST_FOREACH(int id,model_draw_id_list)
		{
			std::string name = DataBase::getName(id);
			std::string filename = name + std::string(".obj");
			Model::ptr model = Model::createFromArchiveWaveFront(filename.c_str());
			DisplayList disp = DisplayList::create();
			disp.newList();
			{
				glBegin(GL_TRIANGLES);
				const int numVertex = model->numVertex();
				for(int i = 0 ; i < numVertex ; ++i)
				{		
					glm::vec3 normal = model->getNormal(i);
					glm::vec2 textureCoord = model->getTextureCoord(i);
					glm::vec3 vertex = model->getVertex(i);

					glNormal3f(normal.x,normal.y,normal.z);
					glTexCoord2f(textureCoord.x,textureCoord.y);
					glVertex3f(vertex.x,vertex.y,vertex.z);
				}
				glEnd();
			}
			disp.endList();
			g_models[ id ] = disp;
		}
	}
	//í èÌï`âÊ
	{
		std::vector<int> nomal_draw_id_list = DataBase::getNormalDrawBlockList();
		BOOST_FOREACH(int id,nomal_draw_id_list)
		{
			DisplayList disp = DisplayList::create();
			disp.newList();
			Cube::drawTop(id);
			Cube::drawBottom(id);
			Cube::drawFront(id);
			Cube::drawBack(id);
			Cube::drawLeft(id);
			Cube::drawRight(id);
			disp.endList();
			g_models[ id ] = disp;
		}
	}

	//ó÷äs
	{
		g_contourDisplayList = DisplayList::create();
		g_contourDisplayList.newList();
		glBegin(GL_LINES);
		{
			const float v = 0.5f;
			//è„
			{
				const float h = v;
				glVertex3f(-v,h,v); glVertex3f(v,h,v);
				glVertex3f(v,h,v); glVertex3f(v,h,-v);
				glVertex3f(v,h,-v); glVertex3f(-v,h,-v);
				glVertex3f(-v,h,-v); glVertex3f(-v,h,v);
			}

			//â∫
			{
				const float h = -v;
				glVertex3f(-v,h,v); glVertex3f(v,h,v);
				glVertex3f(v,h,v); glVertex3f(v,h,-v);
				glVertex3f(v,h,-v); glVertex3f(-v,h,-v);
				glVertex3f(-v,h,-v); glVertex3f(-v,h,v);
			}

			//èc
			{
				const float h = v;
				const float l = -v;
				glVertex3f(-v,h,v); glVertex3f(-v,l,v);
				glVertex3f(v,h,v); glVertex3f(v,l,v);
				glVertex3f(v,h,-v); glVertex3f(v,l,-v);
				glVertex3f(-v,h,-v); glVertex3f(-v,l,-v);
			}
		}
		glEnd();
		g_contourDisplayList.endList();
	}
}
void FinResource()
{
	g_texture = Texture::ptr();
	g_arrowDisplayList = DisplayList();
	g_models.clear();
}
Texture::ptr getTexture()
{
	return g_texture;
}
DisplayList getArrowDisplayList()
{
	return g_arrowDisplayList;
}
DisplayList getBlockDisplayList(int blockId)
{
	return g_models.find(blockId)->second;
}
DisplayList getContourDisplayList()
{
	return g_contourDisplayList;
}
}//graphic
}//MinePlanner