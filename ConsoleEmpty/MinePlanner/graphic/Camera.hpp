#ifndef MINEPLANNER_GRAPHIC_CAMERA
#define MINEPLANNER_GRAPHIC_CAMERA
#include <string>
#include <glm/glm.hpp>
namespace MinePlanner{
namespace graphic{
class Camera
{
public:
	virtual ~Camera(){}
public:
	//fovy以外をリセット
	virtual void reset() = 0;

	virtual void rotateX(float degree) = 0;
	virtual void rotateY(float degree) = 0;
	
	virtual void moveBack(float distance) = 0;
	virtual void moveRight(float distance) = 0;
	virtual void moveUp(float distance) = 0;

	virtual void approach(float distance) = 0;

	virtual void setDistance(float distance) = 0;
	virtual float getDistance()const = 0;

	void setXAxisView();
	void setYAxisView();
	void setZAxisView();

	//左下が0,0の座標系
	virtual void mouseMiddleButtonDrag(int dx,int dy) = 0;

	virtual glm::vec3 getLookAt()const = 0;
	virtual glm::vec3 getEye()const = 0;

		typedef std::pair<glm::vec3,glm::vec3> ray;//pos,dir
	
	//左下が0,0の座標系
	virtual ray getMouseRay(int mousex,int mousey)const = 0;
	
	virtual void updateInternalMatrix() = 0;
	virtual glm::mat4x4 getViewMatrix()const = 0;
	virtual glm::mat4x4 getProjMatrix()const = 0;

	virtual std::string toString()const = 0;
public:
	static Camera* getNowCamera();
};
}//graphic
}//MinePlanner

#define g_camera MinePlanner::graphic::Camera::getNowCamera()

#endif