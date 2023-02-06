#ifndef MINEPLANNER_OPERATION_IMPORTMODEL
#define MINEPLANNER_OPERATION_IMPORTMODEL
#include <string>
namespace MinePlanner{
namespace Operation{
std::string getImportModelName();
void ImportModel(const std::string& filename);
}//Operation
}//MinePlanner
#endif