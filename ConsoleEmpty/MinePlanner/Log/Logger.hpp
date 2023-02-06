#ifndef MINEPLANNER_LOG_LOGGER
#define MINEPLANNER_LOG_LOGGER
#include <string>
#include <boost/shared_ptr.hpp>
namespace MinePlanner{
namespace Log{
//ログを書き込みます
//ログファイル、デバッグ出力(デバッグ時のみ)を出力します
class Logger
{
public:
	virtual ~Logger(){}
public:
	/**
	* ログ出力します
	* @param line 内容 自動的に改行が付く 非同期に処理される
	*/
	virtual void post(const std::string& line) = 0;
public:
	typedef boost::shared_ptr<Logger> ptr;
	static ptr create();
};
}//Log
}//MinePlanner
#endif