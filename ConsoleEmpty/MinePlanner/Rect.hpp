#ifndef MINEPLANNER_RECT
#define MINEPLANNER_RECT
#include <string>
namespace MinePlanner{
//���l�I�ɏ������Ƃ��낪x,y�ƂȂ�
class Rect
{
public:
	Rect();
	Rect(int width,int height);
	Rect(int x,int y,int width,int height);

	bool empty()const;//���ƍ�����0�Ȃ�true

	int getX()const;
	int getY()const;
	int getWidth()const;
	int getHeight()const;

	std::string toString()const;

	static Rect resize(const Rect& rect,int width,int height);
	static Rect replace(const Rect& rect,int x,int y);
	static Rect fromPoints(int x1,int y1,int x2,int y2);
private:
	int m_x,m_y;
	int m_width,m_height;
};
}//MinePlanner
#endif