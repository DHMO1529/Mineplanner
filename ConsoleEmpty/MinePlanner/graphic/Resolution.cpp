#include "MinePlanner/graphic/Resolution.hpp"

#include <sstream>
#include <cassert>
namespace MinePlanner{
namespace graphic{
Resolution::Resolution():
 m_width(100),m_height(100)
{
}
Resolution::Resolution(int witdh,int height):
 m_width(witdh),m_height(height)
{
}
int Resolution::getWidth()const
{
	return m_width;
}
int Resolution::getHeight()const
{
	return m_height;
}
float Resolution::getAspect()const
{
	assert(m_height);
	return static_cast<float>(m_width) / static_cast<float>(m_height);
}
std::string Resolution::toString()const
{
	std::stringstream ss;
	ss << "Resolution(w=" << m_width << ",h=" << m_height << ",Aspect=" << getAspect() << ")";
	return ss.str();
}
}//graphic
}//MinePlanner