#ifndef MINEPLANNER_GRAPHIC_DISPLAYLIST
#define MINEPLANNER_GRAPHIC_DISPLAYLIST
/**
* ディスプレイリスト　コピー可能である。コピーするとリファレンスカウントが増加
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