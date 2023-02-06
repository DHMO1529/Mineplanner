#ifndef MINEPLANNER_OPERATION_CLIPBOARD
#define MINEPLANNER_OPERATION_CLIPBOARD
#include "Util/Singleton.hpp"
#include "MinePlanner/BlockSet.hpp"
namespace MinePlanner{
namespace Operation{
class ClipBoard : public Util::Singleton<ClipBoard>
{
public:
	ClipBoard();
	~ClipBoard();

	void copy();
	void cut();
	void paste();

	bool hasData()const;
private:
	BlockSet m_clipBuffer;
};
}//Operation
}//MinePlanner

inline MinePlanner::Operation::ClipBoard* g_pClipBoard()
{
	return MinePlanner::Operation::ClipBoard::pInstance();
}
#endif