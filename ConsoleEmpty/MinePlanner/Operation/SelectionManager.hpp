#ifndef MINEPLANNER_OPERATION_SELECTIONMANAGER
#define MINEPLANNER_OPERATION_SELECTIONMANAGER
#include <juce.h>
#include "Util/Singleton.hpp"
#include "MinePlanner/Rect.hpp"

#include "MinePlanner/PointSet.hpp"
namespace MinePlanner{
namespace Operation{
class SelectionManager : public Util::Singleton<SelectionManager>
{
public:
	SelectionManager();
	~SelectionManager();

	void draw()const;

	void mouseDown(const MouseEvent& e);
	void mouseDrag(const MouseEvent& e);
	void mouseUp(const MouseEvent& e);

	//外部公開
	bool isSelecting()const;
	PointSet getSelectedPoints();//防御的コピーします
	void clearSelect();
	void selectAll();
private:
	Rect m_selectingRect;
	PointSet m_selectedPoints;
};
}//Operation
}//MinePlanner

inline MinePlanner::Operation::SelectionManager* g_pSelectionManager()
{
	return MinePlanner::Operation::SelectionManager::pInstance();
}
#endif