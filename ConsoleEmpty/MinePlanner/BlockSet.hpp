#ifndef MINEPLANNER_BLOCKSET_HPP
#define MINEPLANNER_BLOCKSET_HPP
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include "MinePlanner/Point.hpp"
#include "MinePlanner/Pose.hpp"
namespace MinePlanner{
//参照カウント式ブロックコレクション
class block_set_implementation;
class BlockSet
{
public:
	typedef boost::function<void(const Point& point,int blockId,const Pose& pose)> Callback;
public:
	BlockSet();
	static BlockSet create();
	bool hasInstance()const;

	void add(const Point& point,int blockId,const Pose& pose);
	void remove(const Point& point);
	void clear();

	bool isExist(const Point& target)const;

	void setPose(const Point& target,const Pose& pose);
	void setBlockID(const Point& target,int blockid);
	Pose getPose(const Point& target)const;
	int getBlockID(const Point& target)const;

	int getBlockNum()const;

	//移動,回転,反転関連
	Point getOrigin()const;
	int getMaxWidth()const;
	void move(int x,int y,int z);
	void rotate(int x,int y,int z);
	void reverse(bool x,bool y,bool z);

	void for_each(Callback callback)const;

	BlockSet clone()const;
private:
	boost::shared_ptr<block_set_implementation> m_impl;
};
}//MinePlanner
#endif