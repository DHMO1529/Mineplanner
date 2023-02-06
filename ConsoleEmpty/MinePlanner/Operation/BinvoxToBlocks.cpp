#include "MinePlanner/Operation\BinvoxToBlocks.hpp"

#include <vector>
#include <fstream>
#include <string>
#include "MinePlanner/DataBase/DataBase.hpp"
namespace MinePlanner{
namespace Operation{
namespace{
//íÜêgÇ™ãlÇ‹ÇËÇ∑Ç¨Ç»ÇÃÇ≈Ç©ÇÁÇ¡Ç€Ç…Ç∑ÇÈ
inline bool IsExist(const std::vector<char>& data,int Size,int x,int y,int z)
{
	if(x < 0 || Size <= x)
	{
		return false;
	}
	if(y < 0 || Size <= y)
	{
		return false;
	}
	if(z < 0 || Size <= z)
	{
		return false;
	}

	const int HD = Size * Size;
	const int H = Size;
	const int Index = x * HD + z * H + y;

	return data[Index] != 0;
}
inline bool IsMustDraw(const std::vector<char>& Data,int Size,int x,int y,int z)
{
	if(x <= 0)
	{
		return true;
	}
	if(y <= 0)
	{
		return true;
	}
	if(z <= 0)
	{
		return true;
	}
	if(Size <= x+1)
	{
		return true;
	}
	if(Size <= y+1)
	{
		return true;
	}
	if(Size <= z+1)
	{
		return true;
	}

	if(!IsExist(Data,Size,x+1,y,z))
	{
		return true;
	}
	if(!IsExist(Data,Size,x-1,y,z))
	{
		return true;
	}
	if(!IsExist(Data,Size,x,y+1,z))
	{
		return true;
	}
	if(!IsExist(Data,Size,x,y-1,z))
	{
		return true;
	}
	if(!IsExist(Data,Size,x,y,z+1))
	{
		return true;
	}
	if(!IsExist(Data,Size,x,y,z-1))
	{
		return true;
	}
	return false;
}
}
BlockSet BinvoxToBlocks(const std::string filename)
{
	std::ifstream ifs(filename,std::ios::binary | std::ios::in);
	
	int width,height,depth;
	
	std::string buffer;
	std::getline(ifs,buffer);
	if(buffer != "#binvox 1")
	{
		return BlockSet::create();
	}

	std::getline(ifs,buffer);
	sscanf(buffer.c_str(),"dim %d %d %d",&depth,&width,&height);

	for(int i = 0 ; i < 3 ; ++i)
		std::getline(ifs,buffer);

	const int SIZE = width;

	std::vector<char> boxelData(width * height * depth);

	int index = 0;
	while( true )
	{
		unsigned char buf[2] = "";
		ifs.read(reinterpret_cast<char*>(buf),2);

		if(ifs.eof())
			break;

		const bool val = (buf[0] == 1);
		const int num = static_cast<int>(buf[1]);

		for(int i = 0 ; i < num ; ++i)
		{
			boxelData[index++] = val? 1 : 0;
		}
	}
	const int blockId = 24;
	BlockSet blockSet =  BlockSet::create();
	for (int x = 0; x < SIZE; ++x)
	{
		for (int z = 0; z < SIZE; ++z)
		{
			for (int y = 0; y < SIZE; ++y)
			{
				if(IsExist(boxelData,SIZE,x,y,z))
				{
					if(IsMustDraw(boxelData,SIZE,x,y,z))
					{
						blockSet.add(Point(x,y,z),blockId,Pose());
					}
				}
			}
		}
	}

	return blockSet;
}
}//Operation
}//MinePlanner