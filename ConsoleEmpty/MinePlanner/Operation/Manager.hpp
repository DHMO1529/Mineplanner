#ifndef MINEPLANNER_OPERATION_MANAGER
#define MINEPLANNER_OPERATION_MANAGER

#include <juce.h>
#include "Util/Singleton.hpp"
namespace MinePlanner{
namespace Operation{
class Manager : public Util::Singleton<Manager>
{
public:
	Manager();
	~Manager();

	void draw()const;

	void mouseMove(const MouseEvent& e);
	void mouseDown(const MouseEvent& e);
	void mouseDrag(const MouseEvent& e);
	void mouseUp(const MouseEvent& e);
};
}//Operation
}//MinePlanner

inline MinePlanner::Operation::Manager* g_pOperationManager()
{
	return MinePlanner::Operation::Manager::pInstance();
}
#endif