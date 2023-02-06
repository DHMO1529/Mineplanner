#ifndef MINEPLANNER_HIDEBUFFER_HPP
#define MINEPLANNER_HIDEBUFFER_HPP
#include "Util/Singleton.hpp"
#include "MinePlanner/PointSet.hpp"
namespace MinePlanner{
namespace Operation{
class HideBuffer : public Util::Singleton<HideBuffer>
{
public:
	HideBuffer();
	~HideBuffer();

	void hide();
	void show();

	PointSet getHideBuffer()const;

	bool isHide()const;
private:
	PointSet m_hideBuffer;
};
}//Operation
}//MinePlanner

inline MinePlanner::Operation::HideBuffer* g_pHideBuffer()
{
	return MinePlanner::Operation::HideBuffer::pInstance();
}
#endif