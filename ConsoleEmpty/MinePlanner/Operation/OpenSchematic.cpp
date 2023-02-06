#include "MinePlanner/Operation/OpenSchematic.hpp"

#include <boost/array.hpp>
#include <boost/tuple/tuple.hpp>
#include <juce.h>
#include "nbt/nbt.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"
#include "MinePlanner/World.hpp"
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace Operation{
void OpenSchematic(const std::string& filename)
{
	nbt::Tag::ptr root = nbt::read_nbt(filename.c_str());

	int HEIGHT;
	int WIDTH;
	int DEPTH;

	try{
		HEIGHT = root->getTagFromName("Height")->getShortPayload();
	}catch(std::bad_cast&){
		HEIGHT = root->getTagFromName("Height")->getIntPayload();
	}
	try{
		WIDTH = root->getTagFromName("Width")->getShortPayload();
	}catch(std::bad_cast&){
		WIDTH = root->getTagFromName("Width")->getIntPayload();
	}
	try{
		DEPTH = root->getTagFromName("Length")->getShortPayload();
	}catch(std::bad_cast&){
		DEPTH = root->getTagFromName("Length")->getIntPayload();
	}

	nbt::Tag::payloadType_byteArray blocks = root->getTagFromName("Blocks")->getByteArrayPayload();
	nbt::Tag::payloadType_byteArray data = root->getTagFromName("Data")->getByteArrayPayload();

	for(int h = 0 ; h < HEIGHT ; ++h)
	{
		for(int d = 0 ; d < DEPTH ; ++d)
		{
			for(int w = 0 ; w < WIDTH ; ++w)
			{
				const int WD = WIDTH * DEPTH;
				const int W = WIDTH;
				const int INDEX = WD * h + W * d + w;

				if(blocks[INDEX] == 0){ continue; }

				const DataBase::RawBlockData raw_data = DataBase::RawBlockData::make(blocks[INDEX],data[INDEX]);

				Point p(w,h,d);
				int blockId = 0;
				Pose pose;
				try{
					boost::tie(blockId,pose) = DataBase::convertToBlockFromRaw(raw_data);

					//¬Œ÷‚µ‚½‚ç’Ç‰Á
					World::instance().add(p,blockId,pose);
				}catch(std::bad_cast&){
					//ok
				}
			}
		}
	}
}
}//Operation
}//MinePlanner
