#ifndef MINEPLANNER_GRAPHIC_CUBE_HPP
#define MINEPLANNER_GRAPHIC_CUBE_HPP
#include <boost/noncopyable.hpp>
namespace MinePlanner{
namespace graphic{
/**
* ‘å‘½”‚ÌƒuƒƒbƒN‚ğ•`‰æ‚·‚éŠÖ”ŒS
* Œ´“_‚ÉŠg‘åAˆÚ“®‚È‚µA‘å‚«‚³‚P‚Å•`‰æ‚·‚é
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