#ifndef MINEPLANNER_OPERATION_ARRANGEMENTMANAGER
#define MINEPLANNER_OPERATION_ARRANGEMENTMANAGER
#include <boost/scoped_ptr.hpp>
#include "Util/Singleton.hpp"
#include "MinePlanner/BlockSet.hpp"
#include "MinePlanner/UI/ArrangeUI.hpp"
namespace MinePlanner{
namespace Operation{
class ArrangementManager : public Util::Singleton<ArrangementManager>
{
public:
	ArrangementManager();
	~ArrangementManager();

	bool isArranging()const;
	void arrange(BlockSet arrangeTarget);
	void arrangeFinish();

	void draw()const;

	void onModeChanged();
private:
	BlockSet m_arrangeTarget;
	boost::scoped_ptr<UI::ArrangeUI> m_arrangeUI;
};
}//Operation
}//MinePlanner

inline MinePlanner::Operation::ArrangementManager* g_pArrangementManager()
{
	return MinePlanner::Operation::ArrangementManager::pInstance();
}
#endif
