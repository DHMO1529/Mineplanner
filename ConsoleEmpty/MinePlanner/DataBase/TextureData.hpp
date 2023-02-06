#ifndef MINEPLANNER_DATABASE_TEXTUREDATA_HPP
#define MINEPLANNER_DATABASE_TEXTUREDATA_HPP
#include <boost/array.hpp>
#include "MinePlanner/DataBase/UV.hpp"
namespace MinePlanner{
namespace DataBase{
class TextureData
{
public:
	TextureData():m_UVs(){}
	UV get_uv(int index)const
	{
		return m_UVs[index];
	}

	/**
	*  a d
	*  b c
	*/
	static TextureData make(const UV& a,const UV& b,const UV& c,const UV& d)
	{
		TextureData td;
		td.m_UVs[UVPOS_LEFT_TOP] = a;
		td.m_UVs[UVPOS_LEFT_BOTTOM] = b;
		td.m_UVs[UVPOS_RIGHT_BOTTON] = c;
		td.m_UVs[UVPOS_RIGHT_TOP] = d;
		return td;
	}
	enum uv_pos{
		UVPOS_LEFT_TOP = 0,
		UVPOS_LEFT_BOTTOM,
		UVPOS_RIGHT_BOTTON,
		UVPOS_RIGHT_TOP,
	};
private:
	boost::array<UV,4> m_UVs;
};
}//DataBase
}//MinePlanner
#endif