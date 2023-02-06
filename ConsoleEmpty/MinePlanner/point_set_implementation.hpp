#ifndef MINEPLANNER_POINTSETIMLEMENTATION_HPP
#define MINEPLANNER_POINTSETIMLEMENTATION_HPP
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/unordered_set.hpp>
#include <boost/foreach.hpp>
namespace MinePlanner{
class point_set_implementation
{
public:
	typedef boost::function<void(const Point& point)> Callback;
public:
	point_set_implementation():m_points(){}

	void add(const Point& point)
	{
		m_points.insert(point);
	}
	void remove(const Point& point)
	{
		m_points.erase(point);
	}
	void clear()
	{
		m_points.clear();
	}
	int getNum()const
	{
		return m_points.size();
	}

	bool isContain(const Point& point)const
	{
		return m_points.find(point) != m_points.end();
	}
	void for_each(Callback callback)const
	{
		BOOST_FOREACH(const Point& point,m_points)
		{
			callback(point);
		}
	}

	boost::shared_ptr<point_set_implementation> clone()const
	{
		return boost::shared_ptr<point_set_implementation>(new point_set_implementation(*this));
	}
private:
	boost::unordered_set<Point> m_points;
};
}//MinePlanner
#endif