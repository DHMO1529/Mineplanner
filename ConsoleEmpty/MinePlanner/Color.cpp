#include "MinePlanner/Color.hpp"
#include <algorithm>
#include <new>
#include <sstream>
#include <cmath>
#include <glm/glm.hpp>
#include <boost/math/special_functions.hpp>
namespace MinePlanner{
/**
* 0`1‚Ìfloat‚ğ0`255‚Ìuint8Œ^‚É•ÏŠ·
* @param f 0`1‚Ìfloat’l@‚»‚êˆÈŠO‚ğ“ü‚ê‚é‚ÆŠÛ‚ß‚ç‚ê‚é
* @return •ÏŠ·Œã 0`255‚Ìuint8
*/
inline Color::uint8 convi(float f)
{
	const float arg = glm::clamp(f,0.f,1.f);
	const float val = 255.f * arg;
	return static_cast<Color::uint8>( boost::math::round(val) );
}

/**
* 0`255‚Ìuint8Œ^‚ğ0`1‚Ìfloat‚É•ÏŠ·
* @param f 0`255‚Ìuint8Œ^
* @return 0`1‚Ìfloat
*/
inline float convf(Color::uint8 i)
{
	const float arg = static_cast<float>(i);
	const float val = arg / 255.f;
	return glm::clamp(val,0.f,1.f);
}
Color::Color()
{
	std::fill(m_value.begin(),m_value.end(),0);
}
Color::Color(uint8 r,uint8 g,uint8 b,uint8 a)
{
	m_value[0] = r;
	m_value[1] = g;
	m_value[2] = b;
	m_value[3] = a;
}
Color::Color(uint8 r,uint8 g,uint8 b)
{
	new(this)Color(r,g,b,255);
}
bool Color::operator==(const Color& rhs)const
{
	return this->m_value == rhs.m_value;
}
Color::uint8 Color::getRed()const
{
	return m_value[0];
}
Color::uint8 Color::getGreen()const
{
	return m_value[1];
}
Color::uint8 Color::getBlue()const
{
	return m_value[2];
}
Color::uint8 Color::getAlpha()const
{
	return m_value[3];
}

float Color::getRedf()const
{
	return convf( this->getRed() );
}
float Color::getGreenf()const
{
	return convf( this->getGreen() );
}
float Color::getBluef()const
{
	return convf( this->getBlue() );
}
float Color::getAlphaf()const
{
	return convf( this->getAlpha() );
}
bool Color::isOpaque()const
{
	return this->getAlpha() == 255;
}
bool Color::isInvisible()const
{
	return this->getAlpha() == 0;
}

Color Color::withAlpha(uint8 alpha)const
{
	return Color(this->getRed(),this->getGreen(),this->getBlue(),alpha);
}
Color Color::withAlpha(float alpha)const
{
	return Color(this->getRed(),this->getGreen(),this->getBlue(),convi(alpha));
}

std::string Color::toString()const
{
	struct{
		int operator()(unsigned char c)
		{
			return static_cast<int>(c);
		}
	}cast;
	std::stringstream ss;
	ss << "Color[rgba](";
	ss << cast(this->getRed()) << ",";
	ss << cast(this->getGreen()) << ",";
	ss << cast(this->getBlue()) << ",";
	ss << cast(this->getAlpha()) << ")";
	return ss.str();
}
Color Color::make_color(uint8 r,uint8 g,uint8 b,uint8 a)
{
	return Color(r,g,b,a);
}
Color Color::make_color(uint8 r,uint8 g,uint8 b)
{
	return Color(r,g,b);
}
Color Color::make_colorf(float r,float g,float b,float a)
{
	return Color(convi(r), convi(g), convi(b), convi(a));
}
Color Color::make_colorf(float r,float g,float b)
{
	return Color(convi(r), convi(g), convi(b));
}
float Color::diff(const Color& lhs,const Color& rhs)
{
	glm::vec3 a(lhs.getRedf(),lhs.getGreenf(),lhs.getBluef());
	glm::vec3 b(rhs.getRedf(),rhs.getGreenf(),rhs.getBluef());
	return glm::distance(a,b);
}
}//MinePlanner

