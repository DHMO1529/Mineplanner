#ifndef MINEPLANNER_GRAPHIC_BRENDMODE
#define MINEPLANNER_GRAPHIC_BRENDMODE
/**
* �u�����f�B���O���[�h��ݒ�
*/
#include <boost/noncopyable.hpp>
namespace MinePlanner{
namespace graphic{
enum BrendMode{
	BLEND_OPAQUE = 0,/*�����Ȃ�*/
	BLEND_LINEAR,/*���`����*/
	BLEND_ADDITIVE,/*���Z����*/
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