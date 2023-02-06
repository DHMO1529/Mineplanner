#ifndef MINEPLANNER_GRAPHIC_RESOLUTION
#define MINEPLANNER_GRAPHIC_RESOLUTION
#include <string>
namespace MinePlanner{
namespace graphic{
class Resolution
{
public:
	Resolution();
	Resolution(int witdh,int height);

	int getWidth()const;
	int getHeight()const;
	float getAspect()const;

	std::string toString()const;
private:
	int m_width,m_height;
};
}//graphic
}//MinePlanner
#endif