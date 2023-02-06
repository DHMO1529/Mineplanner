#include "MinePlanner/PathSetup.hpp"
#include <juce.h>
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
void PathSetup()
{
	File executablefile = File::getSpecialLocation(File::currentExecutableFile);
	executablefile.getParentDirectory().setAsCurrentWorkingDirectory();
}
}//MinePlanner