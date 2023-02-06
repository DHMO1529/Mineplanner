#ifndef MINEPLANNER_GRAPHIC_BRENDMODE
#define MINEPLANNER_GRAPHIC_BRENDMODE
/**
* ブレンディングモードを設定
*/
#include <boost/noncopyable.hpp>
namespace MinePlanner{
namespace graphic{
enum BrendMode{
	BLEND_OPAQUE = 0,/*合成なし*/
	BLEND_LINEAR,/*線形合成*/
	BLEND_ADDITIVE,/*加算合成*/
};
void SetBrendMode(BrendMode brendMode);

class ScopedBrendMode : private boost::noncopyable
{
public:
	ScopedBrendMode(BrendMode brendMode);
	~ScopedBrendMode();
};
}//graphic
}//MinePlanner
#endif