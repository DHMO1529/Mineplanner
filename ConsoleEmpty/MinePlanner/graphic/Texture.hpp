#ifndef MINEPLANNER_GRAPHIC_TEXTURE
#define MINEPLANNER_GRAPHIC_TEXTURE
#include <boost/shared_ptr.hpp>
namespace MinePlanner{
namespace graphic{
class Texture
{
public:
	typedef boost::shared_ptr<Texture> ptr;
	static ptr createFromArchive(const char* filename);
public:
	virtual ~Texture(){}
public:
	virtual void bind()const = 0;
	virtual void unbind()const = 0;
};
}//graphic
}//MinePlanner
#endif