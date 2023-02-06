#ifndef MINEPLANNER_OPERATION_WORK
#define MINEPLANNER_OPERATION_WORK
#include <boost/shared_ptr.hpp>
/**
* ���[���h�ɑ΂��鑀����`����
* ����͕K�����ɖ߂���
* ������瑦exe����A����Ă��烏�[���h�͕ҏW����Ȃ����̂Ƃ���
*/
namespace MinePlanner{
namespace Operation{
class Work
{
public:
	virtual ~Work(){}
public:
	/**
	* ��������s����
	* @return ���������Ȃ�true ����ȊO��false
	*/
	virtual bool exe() = 0;

	//���ɖ߂�
	virtual void undo() = 0;

	//��蒼�� ��xexe�Ő������Ă���̂Ő�ΐ�������ׂ���
	virtual void redo() = 0;
public:
	typedef boost::shared_ptr<Work> ptr;
};
}//Operation
}//MinePlanner
#endif