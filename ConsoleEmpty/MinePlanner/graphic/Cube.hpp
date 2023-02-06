#ifndef MINEPLANNER_GRAPHIC_CUBE_HPP
#define MINEPLANNER_GRAPHIC_CUBE_HPP
#include <boost/noncopyable.hpp>
namespace MinePlanner{
namespace graphic{
/**
* �命���̃u���b�N��`�悷��֐��S
* ���_�Ɋg��A�ړ��Ȃ��A�傫���P�ŕ`�悷��
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