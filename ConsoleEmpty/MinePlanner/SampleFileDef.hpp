#ifndef MINEPLANNER_SAMPLEFILEDEF
#define MINEPLANNER_SAMPLEFILEDEF
#include <string>
#include <boost/noncopyable.hpp>
namespace MinePlanner{
/**
* サンプルのファイル名を定義
*/
class SampleFilename : public boost::noncopyable
{
private:
	SampleFilename();
public:
	static const std::string QB;
	static const std::string NICONICOTV;
	static const std::string METALGEARREX;
	static const std::string DRAGONKING;
	static const std::string RAPUTA;
};
}//MinePlanner
#endif