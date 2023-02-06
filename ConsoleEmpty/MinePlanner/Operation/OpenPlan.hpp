#ifndef MINEPLANNER_OPERATION_OPENPLAN
#define MINEPLANNER_OPERATION_OPENPLAN
#include <string>

namespace MinePlanner{
namespace Operation{
//���[���h�̓N���A���Ȃ�
//���炩���߃N���A���Ă�������
bool isEnablePlanFile(const std::string& filename);
void OpenPlan(const std::string& filename);
void OpenPlanFromArchive(const std::string& filename);
}//Operation
}//MinePlanner
#endif