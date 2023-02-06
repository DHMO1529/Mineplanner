#ifndef MINEPLANNER_GRAPHIC_DISPLAYLIST
#define MINEPLANNER_GRAPHIC_DISPLAYLIST
/**
* �f�B�X�v���C���X�g�@�R�s�[�\�ł���B�R�s�[����ƃ��t�@�����X�J�E���g������
*/
#include <boost/shared_ptr.hpp>
namespace MinePlanner{
namespace graphic{
class DisplayListImpl;
class DisplayList
{
public:
	DisplayList();
	~DisplayList();
	static DisplayList create();

	bool hasInstance()const;
	void newList();
	void endList();
	bool empty()const;
	void clear();
	void call()const;
private:
	boost::shared_ptr<DisplayListImpl> m_pimpl;
};
}//graphic
}//MinePlanner
#endif