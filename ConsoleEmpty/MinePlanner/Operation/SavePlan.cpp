#include "MinePlanner/Operation/SavePlan.hpp"
#include <fstream>
#include <juce.h>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

#include "MinePlanner/World.hpp"
#include "MinePlanner/string_cast.hpp"

namespace MinePlanner{
namespace Operation{
void SavePlan(const std::string& filename)
{
	std::ofstream ofs(filename);
	const std::string header("<file format = \"plan2\">");
	ofs << header << std::endl;

	auto each = [&ofs](const Point& point,int blockId,const Pose& pose)
	{
		ofs << boost::format("<id=\"%1%\" pos=\"%2%,%3%,%4%\" rot=\"%5%,%6%,%7%\">\n")
			% blockId
			% point.getX() % point.getY() % point.getZ()
			% pose.get_rotatex() % pose.get_rotatey() % pose.get_rotatez();
	};
	World::instance().for_each(each);
}
}//Operation
}//MinePlanner