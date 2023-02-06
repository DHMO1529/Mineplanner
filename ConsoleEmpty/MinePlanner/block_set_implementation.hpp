#ifndef MINEPLANNER_BLOCKSETIMPLEMENTATION_HPP
#define MINEPLANNER_BLOCKSETIMPLEMENTATION_HPP
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include "MinePlanner/Point.hpp"
#include "MinePlanner/Pose.hpp"
namespace MinePlanner{
class block_set_implementation
{
public:
	typedef boost::function<void(const Point& point,int blockId,const Pose& pose)> Callback;
	struct Container
	{
		Pose pose;
		int blockId;
	};
public:

	block_set_implementation():
	 m_block_set()
	,m_isCalcedBlockInfo(false)
	,m_maxWidth(0)
	,m_origin()
	{
	}

	void add(const Point& point,int blockId,const Pose& pose)
	{
		if(m_block_set.find(point) == m_block_set.end())
		{
			Container container = {pose,blockId};
			m_block_set[ point ] = container;
		}
	}
	void remove(const Point& point)
	{
		m_block_set.erase(point);
	}
	void clear()
	{
		m_block_set.clear();
	}

	bool isExist(const Point& target)const
	{
		return m_block_set.find(target) != m_block_set.end();
	}
	void setPose(const Point& target,const Pose& pose)
	{
		m_block_set.find(target)->second.pose = pose;
	}
	void setBlockID(const Point& target,int blockid)
	{
		m_block_set.find(target)->second.blockId = blockid;
	}
	Pose getPose(const Point& target)const
	{
		return m_block_set.find(target)->second.pose;
	}
	int getBlockID(const Point& target)const
	{
		return m_block_set.find(target)->second.blockId;
	}
	int getBlockNum()const
	{
		return m_block_set.size();
	}
	//internal
	void calcBlockInfo()const
	{
		if(m_block_set.empty())
		{
			m_isCalcedBlockInfo = true;
			return;
		}
		int minx,miny,minz;
		int maxx,maxy,maxz;
		minx = miny = minz = std::numeric_limits<int>::max();
		maxx = maxy = maxz = std::numeric_limits<int>::min();

		typedef boost::unordered_map<Point,Container>::value_type type;
		BOOST_FOREACH(const type& val,m_block_set)
		{
			const Point& pos = val.first;
			minx = std::min(minx,pos.getX());
			miny = std::min(miny,pos.getY());
			minz = std::min(minz,pos.getZ());
			maxx = std::max(maxx,pos.getX());
			maxy = std::max(maxy,pos.getY());
			maxz = std::max(maxz,pos.getZ());
		}
		m_origin = Point((minx+maxx)/2, (miny+maxy)/2, (minz+maxz)/2);

		const int x_width = maxx - minx;
		const int y_width = maxy - miny;
		const int z_width = maxz - minz;
		m_maxWidth = std::max( std::max(x_width,y_width) , z_width);
		m_isCalcedBlockInfo = true;
	}
	Point getOrigin()const
	{
		if(m_isCalcedBlockInfo)
		{
			return m_origin;
		}
		calcBlockInfo();
		return m_origin;
	}
	int getMaxWidth()const
	{
		if(m_isCalcedBlockInfo)
		{
			return m_maxWidth;
		}
		calcBlockInfo();
		return m_maxWidth;
	}
	void move(int x,int y,int z)
	{
		boost::unordered_map<Point,Container> buffer;
		typedef boost::unordered_map<Point,Container>::value_type type;
		BOOST_FOREACH(const type& val,m_block_set)
		{
			const Point new_point = Point::move(val.first,x,y,z);
			buffer[ new_point ] = val.second;
		}
		std::swap(m_block_set,buffer);

		m_origin = Point::move(m_origin,x,y,z);
	}
	void rotate(int x,int y,int z)
	{
		const Point origin = getOrigin();
		if(z)
		{
			boost::unordered_map<Point,Container> buffer;
			typedef boost::unordered_map<Point,Container>::value_type type;
			BOOST_FOREACH(const type& val,m_block_set)
			{
				const Point new_point = Point::rotateZ(val.first,z,origin);
				buffer[ new_point ] = val.second;
			}
			std::swap(m_block_set,buffer);
		}
		if(x)
		{
			boost::unordered_map<Point,Container> buffer;
			typedef boost::unordered_map<Point,Container>::value_type type;
			BOOST_FOREACH(const type& val,m_block_set)
			{
				const Point new_point = Point::rotateX(val.first,x,origin);
				buffer[ new_point ] = val.second;
			}
			std::swap(m_block_set,buffer);
		}
		if(y)
		{
			boost::unordered_map<Point,Container> buffer;
			typedef boost::unordered_map<Point,Container>::value_type type;
			BOOST_FOREACH(const type& val,m_block_set)
			{
				const Point new_point = Point::rotateY(val.first,y,origin);
				buffer[ new_point ] = val.second;
			}
			std::swap(m_block_set,buffer);
		}
	}
	void reverse(bool x,bool y,bool z)
	{
		const Point origin = getOrigin();
		if(z)
		{
			boost::unordered_map<Point,Container> buffer;
			typedef boost::unordered_map<Point,Container>::value_type type;
			BOOST_FOREACH(const type& val,m_block_set)
			{
				const Point new_point = Point::reverseZ(val.first,origin);
				buffer[ new_point ] = val.second;
			}
			std::swap(m_block_set,buffer);
		}
		if(x)
		{
			boost::unordered_map<Point,Container> buffer;
			typedef boost::unordered_map<Point,Container>::value_type type;
			BOOST_FOREACH(const type& val,m_block_set)
			{
				const Point new_point = Point::reverseX(val.first,origin);
				buffer[ new_point ] = val.second;
			}
			std::swap(m_block_set,buffer);
		}
		if(y)
		{
			boost::unordered_map<Point,Container> buffer;
			typedef boost::unordered_map<Point,Container>::value_type type;
			BOOST_FOREACH(const type& val,m_block_set)
			{
				const Point new_point = Point::reverseY(val.first,origin);
				buffer[ new_point ] = val.second;
			}
			std::swap(m_block_set,buffer);
		}
	}
	void for_each(Callback callback)const
	{
		typedef boost::unordered_map<Point,Container>::value_type type;
		BOOST_FOREACH(const type& val,m_block_set)
		{
			callback(val.first,val.second.blockId,val.second.pose);
		}
	}
	boost::shared_ptr<block_set_implementation> clone()const
	{
		return boost::shared_ptr<block_set_implementation>( new block_set_implementation(*this) );
	}
private:
	boost::unordered_map<Point,Container> m_block_set;

	mutable bool m_isCalcedBlockInfo;
	mutable int m_maxWidth;
	mutable Point m_origin;
};
}//MinePlanner

#endif