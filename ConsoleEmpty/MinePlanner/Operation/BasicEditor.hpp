#ifndef MINEPLANNER_OPERATION_BASICEDITOR
#define MINEPLANNER_OPERATION_BASICEDITOR

/**
* マウスでの基本編集機能を提供する
*/
#include <juce.h>
#include "Util/Singleton.hpp"
#include "MinePlanner/Collision/RayCastResult.hpp"
namespace MinePlanner{
namespace Operation{
class BasicEditor : public Util::Singleton<BasicEditor>
{
public:
	BasicEditor();
	~BasicEditor();

	void draw()const;

	void mouseMove(const MouseEvent& e);
	void mouseDown(const MouseEvent& e);
	void mouseDrag(const MouseEvent& e);
private:
	Collision::RayCastResult m_rayCastResult;
};
}//Operation
}//MinePlanner
inline MinePlanner::Operation::BasicEditor* g_pBasicEditor()
{
	return MinePlanner::Operation::BasicEditor::pInstance();
}
#endif