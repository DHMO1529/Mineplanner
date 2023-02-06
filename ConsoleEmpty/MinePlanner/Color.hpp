#ifndef MINEPLANNER_COLOR
#define MINEPLANNER_COLOR
#include <boost/operators.hpp>
#include <boost/array.hpp>
namespace MinePlanner{
/**
* 色を定義するクラス
* <値>
* uint8 なら0～255
* float なら0.f～1.f
*/
class Color : private boost::equality_comparable<Color>
{
public:
	typedef unsigned char uint8;
	Color();
	Color(uint8 r,uint8 g,uint8 b,uint8 a);
	Color(uint8 r,uint8 g,uint8 b);

	bool operator==(const Color& rhs)const;

	uint8 getRed()const;
	uint8 getGreen()const;
	uint8 getBlue()const;
	uint8 getAlpha()const;

	float getRedf()const;
	float getGreenf()const;
	float getBluef()const;
	float getAlphaf()const;

	/**
	* @return 完全不透明なら(alpha=255) true
	*/
	bool isOpaque()const;

	/**
	* @return 完全透明なら(alpha=0) true
	*/
	bool isInvisible()const;

	/**
	* 現在持っているrgb色+指定したアルファ色を持つColorを生成 現在のアルファ色は無視
	* @param alpha 指定するアルファ値
	* @return 色
	*/
	Color withAlpha(uint8 alpha)const;
	Color withAlpha(float alpha)const;

	std::string toString()const;
	
	static Color make_color(uint8 r,uint8 g,uint8 b,uint8 a);
	static Color make_color(uint8 r,uint8 g,uint8 b);
	static Color make_colorf(float r,float g,float b,float a);
	static Color make_colorf(float r,float g,float b);

	/**
	* 色の差を計算 rgbのみ
	* どのくらい色が近い(遠い)のか？
	* @param lhs,rhs 比較する色
	* @return 差
	*/
	static float diff(const Color& lhs,const Color& rhs);
private:
	boost::array<uint8,4> m_value;//rgba
};
}//MinePlanner
#endif