#ifndef MINEPLANNER_GRAPHIC_MODEL
#define MINEPLANNER_GRAPHIC_MODEL
#include <boost/shared_ptr.hpp>
#include <glm/glm.hpp>
namespace MinePlanner{
namespace graphic{
class Model
{
public:
	virtual ~Model(){}
public:
	virtual int numVertex()const = 0;
	virtual int numTriangle()const = 0;

	virtual glm::vec3 getNormal(int index)const = 0;
	virtual glm::vec2 getTextureCoord(int index)const = 0;
	virtual glm::vec3 getVertex(int index)const = 0;
public:
	typedef boost::shared_ptr<const Model> ptr;
	static ptr createFromArchiveWaveFront(const char* filename);
};
}//graphic
}//MinePlanner
#endif