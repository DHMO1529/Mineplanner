#include "MinePlanner/Operation/OpenPlan.hpp"

#include <clx/unzip.h>
#include <fstream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <juce.h>

#include "MinePlanner/World.hpp"
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"
#include "MinePlanner/Log/LogManager.hpp"
namespace MinePlanner{
namespace Operation{
bool isEnablePlanFile(const std::string& filename)
{
	std::ifstream ifs(filename);
	std::string line_buffer;
	std::getline(ifs,line_buffer);

	boost::regex regex("< *file *format *= *\"(.*)\" *>");
	boost::smatch result;
	if(boost::regex_search(line_buffer,result,regex))
	{
		if(result[1] == "plan2")
		{
			return true;
		}
	}
	return false;
}
template <class T>
inline void open(T& stream)
{
	std::string line_buffer;
	std::getline(stream,line_buffer);

	boost::regex regex("< *id *= *\"(.*)\" *pos *= *\"(.*),(.*),(.*)\" *rot *= *\"(.*),(.*),(.*)\" *>");
	while(true)
	{
		std::getline(stream,line_buffer);
		if(stream.fail())
		{
			break;
		}
		if(line_buffer.empty())
		{
			continue;
		}
		if(line_buffer[0] == '#')
		{
			continue;
		}

		boost::smatch result;
		if(boost::regex_search(line_buffer,result,regex))
		{
			const int id = boost::lexical_cast<int,std::string>(result[1]);
			if(DataBase::isExistBlock(id))
			{
				const int x = boost::lexical_cast<int,std::string>(result[2]);
				const int y = boost::lexical_cast<int,std::string>(result[3]);
				const int z = boost::lexical_cast<int,std::string>(result[4]);

				const int rx = boost::lexical_cast<int,std::string>(result[5]);
				const int ry = boost::lexical_cast<int,std::string>(result[6]);
				const int rz = boost::lexical_cast<int,std::string>(result[7]);

				World::instance().add(Point(x,y,z),id,Pose::make(rx,ry,rz));
			}
			else
			{
				std::stringstream ss;
				ss << "OpenPlan 識別できないブロックをスキップ : " << id;
				g_pLogManager()->post(ss.str());
			}
		}
	}
}

void OpenPlan(const std::string& filename)
{
	std::ifstream ifs(filename);
	open(ifs);
}
void OpenPlanFromArchive(const std::string& filename)
{
	clx::unzip unzip(ApplicationConstant::ZIP_ARCHIVE,ApplicationConstant::ZIP_PASSWORD);
	clx::unzip::iterator it = unzip.find(filename);
	if(it == unzip.end())
	{
		assert(0);
	}
	else
	{
		open(*it);
	}
}
}//Operation
}//MinePlanner