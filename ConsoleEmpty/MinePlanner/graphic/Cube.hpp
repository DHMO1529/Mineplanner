#ifndef MINEPLANNER_GRAPHIC_CUBE_HPP
#define MINEPLANNER_GRAPHIC_CUBE_HPP
#include <boost/noncopyable.hpp>
namespace MinePlanner{
namespace graphic{
/**
* 大多数のブロックを描画する関数郡
* 原点に拡大、移動なし、大きさ１で描画する
*/
class Cube : private boost::noncopyable
{
private:
	Cube();
public:
	static void drawTop(int blockId);
	static void drawBottom(int blockId);
	static void drawFront(int blockId);
	static void drawLeft(int blockId);
	static void drawRight(int blockId);
	static void drawBack(int blockId);
};
}//graphic
}//MinePlanner

#endif