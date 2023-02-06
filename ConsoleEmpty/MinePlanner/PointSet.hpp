#ifndef MINEPLANNER_POINTSET_HPP
#define MINEPLANNER_POINTSET_HPP
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "MinePlanner/Point.hpp"
namespace MinePlanner{
class point_set_implementation;
/**
* 参照カウント式位置コレクション
*/
class PointSet
{
public:
	typedef boost::function<void(const Point& point)> Callback;
public:
	PointSet();
	static PointSet create();
	bool hasInstance()const;

	void add(const Point& point);
	void remove(const Point& point);
	void clear();
	int getNum()const;

	bool isContain(const Point& point)const;
	void for_each(Callback callback)const;

	PointSet clone()const;
private:
	boost::shared_ptr<point_set_implementation> m_impl;
};
}//MinePlanner
#endif
