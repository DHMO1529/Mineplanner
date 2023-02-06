#include "MinePlanner/getBlockPose.hpp"
#include "MinePlanner/graphic/Camera.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"
#include <glm/ext.hpp>
#include <limits>
namespace MinePlanner{
inline int get_y_rot()
{
	glm::vec3 dir = g_camera->getEye() - g_camera->getLookAt();

	dir.y = 0;
	dir = glm::normalize(dir);

	float x = dir.x;
	float y = dir.z;
	
	const float angle135 = glm::radians(135.f);
	const float angle45 = glm::radians(45.f);
	const float angle_45 = glm::radians(-45.f);
	const float angle_135 = glm::radians(-135.f);

	float radian = glm::atan(y,x);
	if(angle_135 < radian && radian < angle_45)
	{
		return 2;
	}
	else if(angle_45 <= radian && radian < angle45)
	{
		return 1;
	}
	else if(angle45 <= radian && radian < angle135)
	{
		return 0;
	}
	else
	{
		return 3;
	}
	assert(0);
	return std::numeric_limits<int>::min();
}
Pose getBlockPose(int blockId)
{
	const int orient_type = DataBase::getOrientType(blockId);
	if(orient_type == DataBase::ORIENT_TYPE_NONE)
	{
		return Pose();
	}
	else if(orient_type == DataBase::ORIENT_TYPE_YAXIS)
	{
		return Pose::make(0,get_y_rot());
	}
	//else
	//{
	//	glm::vec3 dir = g_camera->getEye() - g_camera->getLookAt();
	//	dir = glm::normalize(dir);

	//	float angle = glm::angle(dir,glm::vec3(0,1.f,0));
	//	const float threshold = 40.f;
	//	if(angle < threshold)
	//	{
	//		//ã
	//		return Pose::make(0,0);
	//	}
	//	else if((180.f - threshold) < angle)
	//	{
	//		//‰º
	//		return Pose::make(2,0);
	//	}
	//	else
	//	{
	//		return Pose::make(1,get_y_rot());
	//	}
	//}
	assert(0);
	return Pose();
}
}//MinePlanner