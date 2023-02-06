#include "MinePlanner/Operation/OpenOldPlan.hpp"

#include <fstream>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <juce.h>
#include "MinePlanner/World.hpp"
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"
namespace MinePlanner{
namespace Operation{
std::string GetOpenOldPlanFilename()
{
	FileChooser chooser(L"旧Planファイルを開く",File::nonexistent,"*.plan");
	if(chooser.browseForFileToOpen())
	{
		File choosedFile = chooser.getResult();
		return string_cast<std::string,String>(choosedFile.getFullPathName());
	}
	return "";
}
bool isEnableOldPlanFile(const std::string& filename)
{
	std::ifstream ifs(filename);
	std::string line_buffer;
	std::getline(ifs,line_buffer);
	
	boost::regex regex("#boxel");
	if(boost::regex_search(line_buffer,regex))
	{
		return true;
	}
	return false;
}
void OpenOldPlan(const std::string& filename)
{
	std::ifstream ifs(filename);
	std::string line_buffer;
	std::getline(ifs,line_buffer);
	while(true)
	{
		std::getline(ifs,line_buffer);
		if(ifs.fail())
		{
			break;
		}
		if(line_buffer.empty())
		{
			continue;
		}
		int x,y,z;
		char block_name[32] = "";
		char extention[32] = "";
		sscanf(line_buffer.c_str(),"%d,%d,%d,%[^,],%[^,]",&x,&y,&z,block_name,extention);

		if(std::string(block_name).empty())
		{
			continue;
		}
		const Point point = Point(x,y,z);
		const int blockId = DataBase::convertBlockIdFromOldBlockName(block_name);
		Pose pose;
		if(DataBase::getOrientType(blockId) == DataBase::ORIENT_TYPE_YAXIS)
		{
			std::string ext(block_name);
			if(ext == "North")
			{
				pose = Pose::make(0,2);
			}
			else if(ext == "South")
			{
				pose = Pose::make(0,0);
			}
			else if(ext == "West")
			{
				pose = Pose::make(0,3);
			}
			else if(ext == "East")
			{
				pose = Pose::make(0,1);
			}
		}
		World::instance().add(point,blockId,pose);
	}
}
}//Operation
}//MinePlanner