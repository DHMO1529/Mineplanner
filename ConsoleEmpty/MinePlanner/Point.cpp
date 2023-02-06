#include "MinePlanner/Point.hpp"

#include <cmath>
#include <sstream>
#include <boost/unordered_set.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions.hpp>

namespace MinePlanner{
/**
*intŒ^‚Ìsin,cos
* @param x Šp“x 1‚ª90“x ƒÎ/2
* @return sin,cos
*/
namespace{
inline int sini(int x)
{
	const float xf = boost::math::constants::pi<float>() * 0.5f * x;
	const float val = std::sinf(xf);
	return static_cast<int>( boost::math::round(val) );
}
inline int cosi(int x)
{
	const float xf = boost::math::constants::pi<float>() * 0.5f * x;
	const float val = std::cosf(xf);
	return static_cast<int>( boost::math::round(val) );
}
inline Point rotate_x(const Point& point,int n)
{
	const int SIN = sini(n);
	const int COS = cosi(n);
	const int newx = point.getX();
	const int newy = COS * point.getY() - SIN * point.getZ();
	const int newz = SIN * point.getY() + COS * point.getZ();
	return Point(newx,newy,newz);
}
inline Point rotate_y(const Point& point,int n)
{
	const int SIN = sini(n);
	const int COS = cosi(n);
	const int newx = COS * point.getX() + SIN * point.getZ();
	const int newy = point.getY();
	const int newz = -SIN * point.getX() + COS * point.getZ();
	return Point(newx,newy,newz);
}
inline Point rotate_z(const Point& point,int n)
{
	const int SIN = sini(n);
	const int COS = cosi(n);
	const int newx = COS * point.getX() - SIN * point.getY();
	const int newy = SIN * point.getX() + COS * point.getY();
	const int newz = point.getZ();
	return Point(newx,newy,newz);
}
}
Point::Point():
 x(0),y(0),z(0)
{
}
Point::Point(int X,int Y,int Z):
 x(X),y(Y),z(Z)
{
}
bool Point::operator==(const Point& rhs)const
{
	if(this->x != rhs.x)
	{
		return false;
	}
	if(this->y != rhs.y)
	{
		return false;
	}
	if(this->z != rhs.z)
	{
		return false;
	}
	return true;
}
int Point::getX()const
{
	return this->x;
}
int Point::getY()const
{
	return this->y;
}
int Point::getZ()const
{
	return this->z;
}
std::string Point::toString()const
{
	std::stringstream ss;
	ss << "Point(" << this->x << "," << this->y << "," << this->z << ")";
	return ss.str();
}
size_t Point::hash_value()const
{
	size_t h = 0;
	boost::hash_combine(h, this->x);
	boost::hash_combine(h, this->y);
	boost::hash_combine(h, this->z);
	return h;
}
Point Point::move(const Point& point,int x,int y,int z)
{
	return Point(point.getX() + x, point.getY() + y, point.getZ() + z);
}
Point Point::rotateX(const Point& point,int n,const Point& origin)
{
	Point p = Point::move(point,-origin.getX(),-origin.getY(),-origin.getZ());
	p = rotate_x(p,n);
	return Point::move(p,origin.getX(),origin.getY(),origin.getZ());
}
Point Point::rotateY(const Point& point,int n,const Point& origin)
{
	Point p = Point::move(point,-origin.getX(),-origin.getY(),-origin.getZ());
	p = rotate_y(p,n);
	return Point::move(p,origin.getX(),origin.getY(),origin.getZ());
}
Point Point::rotateZ(const Point& point,int n,const Point& origin)
{
	Point p = Point::move(point,-origin.getX(),-origin.getY(),-origin.getZ());
	p = rotate_z(p,n);
	return Point::move(p,origin.getX(),origin.getY(),origin.getZ());
}
Point Point::reverseX(const Point& point,const Point& origin)
{
	int x = point.getX() - origin.getX();
	x = -x;
	x += origin.getX();
	return Point(x,point.getY(),point.getZ());
}
Point Point::reverseY(const Point& point,const Point& origin)
{
	int y = point.getY() - origin.getY();
	y = -y;
	y += origin.getY();
	return Point(point.getX(),y,point.getZ());
}
Point Point::reverseZ(const Point& point,const Point& origin)
{
	int z = point.getZ() - origin.getZ();
	z = -z;
	z += origin.getZ();
	return Point(point.getX(),point.getY(),z);
}
size_t hash_value(const Point& point)
{
	return point.hash_value();
}
}//MinePlanner