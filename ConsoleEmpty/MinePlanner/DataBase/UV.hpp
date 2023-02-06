#ifndef MINEPLANNER_DATABASE_UV_HPP
#define MINEPLANNER_DATABASE_UV_HPP
namespace MinePlanner{
namespace DataBase{
class UV
{
public:
	UV():m_u(0),m_v(0){}

	float get_u()const {return m_u;}
	float get_v()const {return m_v;}

	static UV make(float u,float v)
	{
		UV uv;
		uv.m_u = u;
		uv.m_v = v;
		return uv;
	}
private:
	float m_u,m_v;
};
}//DataBase
}//MinePlanner
#endif