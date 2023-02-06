#include "MinePlanner/UI/isLockSaveSchematic.hpp"

#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <clx/unzip.h>

#include "MinePlanner/ApplicationConstant.hpp"
namespace MinePlanner{
namespace UI{
bool isLockSaveSchematic()
{
	static bool isLock = true;
	if(!isLock)
	{
		//もうロック解除されてた
		return false;
	}

	//解除ファイル
	std::ifstream ifs("unlock_saveschematic",std::ios::binary);
	if(!ifs)
	{
		//ファイルがない
		return true;
	}
	ifs.seekg(0,std::ios::end);
	std::vector<char> unlockdata( static_cast<int>(ifs.tellg()) );
	ifs.seekg(0,std::ios::beg);
	ifs.read(&unlockdata[0],unlockdata.size());

	//正答
	clx::unzip unzip(ApplicationConstant::ZIP_ARCHIVE,ApplicationConstant::ZIP_PASSWORD);
	clx::unzip::iterator it = unzip.find("unlock_saveschematic");
	if(it == unzip.end())
	{
		assert(0);
	}
	clx::unzip::stream_type& stream = *it;

	std::vector<char> bin_buffer;
	while(true)
	{
		char d = stream.get();
		if(stream.eof())
		{
			break;
		}
		bin_buffer.push_back(d);
	}

	if(unlockdata == bin_buffer)
	{
		isLock = false;
		return false;
	}
	return true;
}
}//UI
}//MinePlanner