#ifndef MINEDEPLANNER_APPLICATIONCONSTANT
#define MINEDEPLANNER_APPLICATIONCONSTANT
#include <string>
#include <boost/noncopyable.hpp>
/**
* アプリケーションの定数定義
*/
namespace MinePlanner{
class ApplicationConstant : private boost::noncopyable
{
private:
	ApplicationConstant();
public:
	static const std::string NAME;
	static const std::string VERSION;
	static const int WINDOW_WIDTH;
	static const int WINDOW_HEIGHT;
	static const std::string ZIP_ARCHIVE;
	static const std::string ZIP_PASSWORD;
};
}//MinePlanner
#endif