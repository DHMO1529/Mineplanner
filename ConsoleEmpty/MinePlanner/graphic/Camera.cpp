#include "MinePlanner/graphic/Camera.hpp"

//#include "MinePlanner/graphic/CameraNormal.hpp"
//#include "MinePlanner/graphic/CameraOrtho.hpp"
#include <sstream>
#include <glm/ext.hpp>
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"
#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/Resolution.hpp"
namespace MinePlanner{
namespace graphic{
namespace{
const float FOVY = 45.f;
class CameraImpl : public Camera
{
public:
	CameraImpl()
	{
		this->reset();
	}
	virtual void reset()
	{
		m_lookAt = glm::vec3(0,0,0);
		m_distance = 100;
		m_rotatex = 0;
		m_rotatey = 0;
		m_view = glm::mat4x4();
		m_proj = glm::mat4x4();
	}
	virtual void rotateX(float degree)
	{
		m_rotatex += degree;
		m_rotatex = glm::clamp(m_rotatex,-89.5f,89.5f);
	}
	virtual void rotateY(float degree)
	{
		m_rotatey += degree;
	}

	virtual void moveBack(float distance)
	{
		if(g_config->getCameraMode() == CAMERA_MODE_NORMAL)
		{
			m_lookAt += ( - getFrontAxis()) * distance;
		}
		else
		{
			//NOP
		}
	}
	virtual void moveRight(float distance)
	{
		m_lookAt += getRightAxis() * distance;
	}
	virtual void moveUp(float distance)
	{
		m_lookAt += getUpAxis() * distance;
	}
	virtual void approach(float distance)
	{
		m_distance -= distance;
		m_distance = glm::clamp(m_distance,5.f,500.f);
	}

	virtual void setDistance(float distance)
	{
		m_distance = distance;
	}
	virtual float getDistance()const
	{
		return m_distance;
	}

	virtual void mouseMiddleButtonDrag(int dx,int dy)
	{
		int vpbuf[4] = {0};
		glGetIntegerv(GL_VIEWPORT, vpbuf);

		glm::vec4 viewport(0,0,
			static_cast<float>(vpbuf[2]),
			static_cast<float>(vpbuf[3]));
		glm::vec3 win = glm::project<float>(m_lookAt,m_view,m_proj,viewport);
		
		win.x -= static_cast<float>(dx);
		win.y += static_cast<float>(dy);

		m_lookAt = glm::unProject(win,m_view,m_proj,viewport);
	}

	virtual glm::vec3 getLookAt()const
	{
		return m_lookAt;
	}
	virtual glm::vec3 getEye()const
	{
		glm::vec3 dir(0,0,m_distance);
		dir = glm::rotateX<float>(dir,m_rotatex);
		dir = glm::rotateY<float>(dir,m_rotatey);
		return m_lookAt + dir;
	}
	virtual ray getMouseRay(int mousex,int mousey)const
	{
		int vpbuf[4] = {0};
		glGetIntegerv(GL_VIEWPORT,vpbuf);

		glm::vec4 viewport(0,0,
			static_cast<float>(vpbuf[2]),
			static_cast<float>(vpbuf[3]));

		glm::vec3 beg(static_cast<float>(mousex),static_cast<float>(mousey),-1.f);
		glm::vec3 end(static_cast<float>(mousex),static_cast<float>(mousey),1.f);

		beg = glm::unProject(beg,m_view,m_proj,viewport);
		end = glm::unProject(end,m_view,m_proj,viewport);
		return ray(beg,end - beg);
	}

	//s—ñ¶¬
	virtual void updateInternalMatrix()
	{
		int viewport[4] = {0};
		glGetIntegerv(GL_VIEWPORT, viewport);
		Resolution resolution(viewport[2],viewport[3]);

		if(g_config->getCameraMode() == CAMERA_MODE_NORMAL)
		{
			m_proj = glm::perspective(FOVY,resolution.getAspect(),5.f,500.f);
		}
		else
		{
			const float w = m_distance * 0.5f * resolution.getAspect();
			const float h = m_distance * 0.5f; 
			m_proj = glm::ortho(-w,w,-h,h,-100.f,300.f);
		}
		glm::vec3 eye = this->getEye();
		m_view = glm::lookAt<float>(eye,m_lookAt,glm::vec3(0,1.f,0));
	}
	virtual glm::mat4x4 getViewMatrix()const
	{
		return m_view;
	}
	virtual glm::mat4x4 getProjMatrix()const
	{
		return m_proj;
	}

	virtual std::string toString()const
	{
		std::stringstream ss;
		const glm::vec3 eye = this->getEye();
		const glm::vec3& lookat = m_lookAt;

		struct{
			int operator()(float f)
			{
				return static_cast<int>(f);
			}
		}c;
		ss << "Camera(lookat=" << c(lookat.x) << "," << c(lookat.y) << "," << c(lookat.z);
		ss << " eye=" << c(eye.x) << "," << c(eye.y) << "," << c(eye.z) << ")";
		return ss.str();
	}
private:
	glm::vec3 getFrontAxis()
	{
		return glm::normalize( m_lookAt - this->getEye() );
	}
	glm::vec3 getRightAxis()
	{
		return glm::normalize( glm::cross(this->getFrontAxis(),glm::vec3(0,1.f,0)) );
	}
	glm::vec3 getUpAxis()
	{
		return glm::normalize( glm::cross(this->getRightAxis(),this->getFrontAxis()) );
	}
private:
	glm::vec3 m_lookAt;
	float m_distance;
	float m_rotatex,m_rotatey;//degree

	glm::mat4x4 m_view;
	glm::mat4x4 m_proj;
};
}
void Camera::setXAxisView()
{
	const float dis = this->getDistance();
	this->reset();
	this->rotateY(90.f);
	this->setDistance(dis);
}
void Camera::setYAxisView()
{
	const float dis = this->getDistance();
	this->reset();
	this->rotateX(-90.f);
	this->setDistance(dis);
}
void Camera::setZAxisView()
{
	const float dis = this->getDistance();
	this->reset();
	this->setDistance(dis);
}
Camera* Camera::getNowCamera()
{
	//static CameraNormal normal;
	//static CameraOrtho ortho;

	//if(g_config->getCameraMode() == CAMERA_MODE_NORMAL)
	//{
	//	return &normal;
	//}
	//else
	//{
	//	return &ortho;
	//}
	static CameraImpl camera;
	return &camera;
}
}//graphic
}//MinePlanner