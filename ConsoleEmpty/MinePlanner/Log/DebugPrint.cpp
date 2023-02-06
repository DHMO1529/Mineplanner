#include "MinePlanner/Log/DebugPrint.hpp"

#include <juce.h>
#include "MinePlanner/string_cast.hpp"

namespace MinePlanner{
namespace Log{
CriticalSection g_CriticalSection;
void DebugPrint(const std::string& line)
{
#ifndef NDEBUG
		GenericScopedLock<CriticalSection> lock(g_CriticalSection);

		String putLine = string_cast<String,std::string>(line);
		DBG(putLine);
#endif
}
}//Log
}//MinePlanner
