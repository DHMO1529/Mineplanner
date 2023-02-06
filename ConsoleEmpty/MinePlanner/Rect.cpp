#include "MinePlanner/Rect.hpp"

#include <cmath>
#include <sstream>
namespace MinePlanner{
Rect::Rect():
 m_x(0)
,m_y(0)
,m_width(0)
,m_height(0)
{
}
Rect::Rect(int width,int height):
 m_x(0)
,m_y(0)
,m_width(width)
,m_height(height)
{
}
Rect::Rect(int x,int y,int width,int height):
 m_x(x)
,m_y(y)
,m_width(width)
,m_height(height)
{
}
bool Rect::empty()const
{
	return (m_width == 0) && (m_height == 0);
}
int Rect::getX()const
{
	return m_x;
}
int Rect::getY()const
{
	return m_y;
}
int Rect::getWidth()const
{
	return m_width;
}
int Rect::getHeight()const
{
	return m_height;
}
std::string Rect::toString()const
{
	std::stringstream ss;
	ss << "Rect(x=" << m_x << ",";
	ss << "y=" << m_y << ",";
	ss << "width=" << m_width << ",";
	ss << "height=" << m_height;
	ss << ")";
	return ss.str();
}
Rect Rect::resize(const Rect& rect,int width,int height)
{
	return Rect(rect.getX(),rect.getY(),width,height);
}
Rect Rect::replace(const Rect& rect,int x,int y)
{
	return Rect(x,y,rect.getWidth(),rect.getHeight());
}
Rect Rect::fromPoints(int x1,int y1,int x2,int y2)
{
	const int w = std::abs(x1 - x2);
	const int h = std::abs(y1 - y2);

	const int x = std::min(x1,x2);
	const int y = std::min(y1,y2);
	return Rect(x,y,w,h);
}
}//MinePlanner