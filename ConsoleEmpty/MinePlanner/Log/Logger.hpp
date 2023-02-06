#ifndef MINEPLANNER_LOG_LOGGER
#define MINEPLANNER_LOG_LOGGER
#include <string>
#include <boost/shared_ptr.hpp>
namespace MinePlanner{
namespace Log{
//���O���������݂܂�
//���O�t�@�C���A�f�o�b�O�o��(�f�o�b�O���̂�)���o�͂��܂�
class Logger
{
public:
	virtual ~Logger(){}
public:
	/**
	* ���O�o�͂��܂�
	* @param line ���e �����I�ɉ��s���t�� �񓯊��ɏ��������
	*/
	virtual void post(const std::string& line) = 0;
public:
	typedef boost::shared_ptr<Logger> ptr;
	static ptr create();
};
}//Log
}//MinePlanner
#endif