#ifndef MINEPLANNER_POSE_HPP
#define MINEPLANNER_POSE_HPP
#include <string>
#include <boost/operators.hpp>
namespace MinePlanner{
/**
* 姿勢を保持するクラス
* ｚを正面と考える
* 回転はz→x→y 
* ただzを回転させることはまずないだろうが、
* ３次元なので、一応用意しておく
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