#ifndef MINEPLANNER_POINT
#define MINEPLANNER_POINT
/*
ブロックの座標を定義するクラス
*/
#include <string>
#include <boost/operators.hpp>
namespace MinePlanner{
class Point : private boost::equality_comparable<Point>
{
public:
	Point();
	Point(int X,int Y,int Z);

	bool operator==(const Point& rhs)const;

	int getX()const;
	int getY()const;
	int getZ()const;

	std::string toString()const;
	size_t hash_value()const;

	static Point move(const Point& point,int x,int y,int z);
	static Point rotateX(const Point& point,int n,const Point& origin);
	static Point rotateY(const Point& point,int n,const Point& origin);
	static Point rotateZ(const Point& point,int n,const Point& origin);
	static Point reverseX(const Point& point,const Point& origin);
	static Point reverseY(const Point& point,const Point& origin);
	static Point reverseZ(const Point& point,const Point& origin);
private:
	int x,y,z;
};
size_t hash_value(const Point& point);
}//MinePlanner
#endif