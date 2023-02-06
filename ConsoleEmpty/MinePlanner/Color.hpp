#ifndef MINEPLANNER_COLOR
#define MINEPLANNER_COLOR
#include <boost/operators.hpp>
#include <boost/array.hpp>
namespace MinePlanner{
/**
* �F���`����N���X
* <�l>
* uint8 �Ȃ�0�`255
* float �Ȃ�0.f�`1.f
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
	* @return ���S�s�����Ȃ�(alpha=255) true
	*/
	bool isOpaque()const;

	/**
	* @return ���S�����Ȃ�(alpha=0) true
	*/
	bool isInvisible()const;

	/**
	* ���ݎ����Ă���rgb�F+�w�肵���A���t�@�F������Color�𐶐� ���݂̃A���t�@�F�͖���
	* @param alpha �w�肷��A���t�@�l
	* @return �F
	*/
	Color withAlpha(uint8 alpha)const;
	Color withAlpha(float alpha)const;

	std::string toString()const;
	
	static Color make_color(uint8 r,uint8 g,uint8 b,uint8 a);
	static Color make_color(uint8 r,uint8 g,uint8 b);
	static Color make_colorf(float r,float g,float b,float a);
	static Color make_colorf(float r,float g,float b);

	/**
	* �F�̍����v�Z rgb�̂�
	* �ǂ̂��炢�F���߂�(����)�̂��H
	* @param lhs,rhs ��r����F
	* @return ��
	*/
	static float diff(const Color& lhs,const Color& rhs);
private:
	boost::array<uint8,4> m_value;//rgba
};
}//MinePlanner
#endif