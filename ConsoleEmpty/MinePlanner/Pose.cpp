#include "MinePlanner/Pose.hpp"
#include <sstream>
namespace MinePlanner{
Pose::Pose():
 m_rotatex(0)
,m_rotatey(0)
,m_rotatez(0){}
bool Pose::operator==(const Pose& rhs)const
{
	if(m_rotatex != rhs.m_rotatex)
		return false;
	
	if(m_rotatey != rhs.m_rotatey)
		return false;

	if(m_rotatez != rhs.m_rotatez)
		return false;

	return true;
}
int Pose::get_rotatex()const
{
	return m_rotatex;
}
int Pose::get_rotatey()const
{
	return m_rotatey;
}
int Pose::get_rotatez()const
{
	return m_rotatez;
}
std::string Pose::toString()const
{
	std::stringstream ss;
	ss << "Pose(" << m_rotatex << "," << m_rotatey << "," << m_rotatez << ")";
	return ss.str();
}
Pose Pose::make(int rotatex,int rotatey,int rotatez)
{
	Pose p;
	p.m_rotatex = rotatex;
	p.m_rotatey = rotatey;
	p.m_rotatez = rotatez;
	return p;
}
}//MinePlanner