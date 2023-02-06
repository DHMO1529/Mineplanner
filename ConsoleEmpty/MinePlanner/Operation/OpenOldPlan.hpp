#ifndef MINEPLANNER_OPERATION_OPENOLDPLAN_HPP
#define MINEPLANNER_OPERATION_OPENOLDPLAN_HPP
#include <string>

namespace MinePlanner{
namespace Operation{
//ワールドはクリアしない
//あらかじめクリアしておくこと
std::string GetOpenOldPlanFilename();
bool isEnableOldPlanFile(const std::string& filename);
void OpenOldPlan(const std::string& filename);
}//Operation
}//MinePlanner
#endif