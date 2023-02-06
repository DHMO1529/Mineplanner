#ifndef MINEPLANNER_POSE_HPP
#define MINEPLANNER_POSE_HPP
#include <string>
#include <boost/operators.hpp>
namespace MinePlanner{
/**
* �p����ێ�����N���X
* ���𐳖ʂƍl����
* ��]��z��x��y 
* ����z����]�����邱�Ƃ͂܂��Ȃ����낤���A
* �R�����Ȃ̂ŁA�ꉞ�p�ӂ��Ă���
*/
class Pose : private boost::equality_comparable<Pose>
{
public:
	Pose();
	bool operator==(const Pose& rhs)const;
	int get_rotatex()const;
	int get_rotatey()const;
	int get_rotatez()const;
	std::string toString()const;
	static Pose make(int rotatex,int rotatey,int rotatez = 0);
private:
	int m_rotatex;
	int m_rotatey;
	int m_rotatez;
};
}//MinePlanner
#endif