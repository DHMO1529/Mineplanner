#ifndef MINEPLANNER_LOG_DEBUGPRINT
#define MINEPLANNER_LOG_DEBUGPRINT
#include <string>
namespace MinePlanner{
namespace Log{
/**
* IDEデバッグ出力
* 一行分出力します。自動で改行が入ります。
* この関数はスレッドセーフです。
* リリースモードでは何もしません
*/
void DebugPrint(const std::string& line);
}//Log
}//MinePlanner
#endif