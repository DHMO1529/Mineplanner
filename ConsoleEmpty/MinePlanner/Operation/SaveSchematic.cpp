#include "MinePlanner/Operation/SaveSchematic.hpp"

#include <limits>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <juce.h>

#include "nbt/nbt.hpp"
#include "MinePlanner/World.hpp"
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"

namespace MinePlanner{
namespace Operation{
struct calc_size_struct{
	calc_size_struct(){
		minx = miny = minz = std::numeric_limits<int>::max();
		maxx = maxy = maxz = std::numeric_limits<int>::min();
		offsetx = offsety = offsetz = 0;
	}
	int getWidth()const
	{
		return maxx + offsetx + 1;
	}
	int getHeight()const
	{
		return maxy + offsety + 1;
	}
	int getDepth()const
	{
		return maxz + offsetz + 1;
	}

	int getOffsetX()const
	{
		return offsetx;
	}
	int getOffsetY()const
	{
		return offsety;
	}
	int getOffsetZ()const
	{
		return offsetz;
	}
	void each(const Point& point,int blockId,const Pose& pose){
		minx = std::min(minx,point.getX());
		miny = std::min(miny,point.getY());
		minz = std::min(minz,point.getZ());

		maxx = std::max(maxx,point.getX());
		maxy = std::max(maxy,point.getY());
		maxz = std::max(maxz,point.getZ());
	}
	void calc_offset(){
		if(minx < 0)
		{
			offsetx = -minx;
		}
		if(miny < 0)
		{
			offsety = -miny;
		}
		if(minz < 0)
		{
			offsetz = -minz;
		}
	}
private:
	int minx,miny,minz;
	int maxx,maxy,maxz;
	int offsetx,offsety,offsetz;
};
void SaveSchematic(const std::string& filename)
{
	nbt::Tag::ptr root = nbt::Tag::makeCompoundTag("Schematic");

	calc_size_struct calc_size;

	World::instance().for_each(boost::bind(&calc_size_struct::each,&calc_size,_1,_2,_3));
	calc_size.calc_offset();

	const int WIDTH = calc_size.getWidth();
	const int HEIGHT = calc_size.getHeight();
	const int DEPTH = calc_size.getDepth();
	nbt::Tag::ptr widthTag = nbt::Tag::makeTag("Width",nbt::TAG_Short,static_cast<short int>(WIDTH));
	nbt::Tag::ptr lengthTag = nbt::Tag::makeTag("Length",nbt::TAG_Short,static_cast<short int>(DEPTH));
	nbt::Tag::ptr heightTag = nbt::Tag::makeTag("Height",nbt::TAG_Short,static_cast<short int>(HEIGHT));
	root->addCompoundChild(widthTag);
	root->addCompoundChild(lengthTag);
	root->addCompoundChild(heightTag);

	root->addCompoundChild( nbt::Tag::makeTag("Materials",nbt::TAG_String,nbt::Tag::payloadType_string("Alpha")) );
	root->addCompoundChild( nbt::Tag::makeListTag("Entities") );
	root->addCompoundChild( nbt::Tag::makeListTag("TileEntities") );

	nbt::Tag::payloadType_byteArray blocks(WIDTH * HEIGHT * DEPTH);
	nbt::Tag::payloadType_byteArray data(WIDTH * HEIGHT * DEPTH);

	for(int h = 0 ; h < HEIGHT ; ++h)
	{
		for(int d = 0 ; d < DEPTH ; ++d)
		{
			for(int w = 0 ; w < WIDTH ; ++w)
			{
				Point p(w - calc_size.getOffsetX(),h - calc_size.getOffsetY(),d - calc_size.getOffsetZ());

				if(World::instance().isExist(p))
				{
					const int blockId = World::instance().getBlockID(p);
					const Pose pose = World::instance().getPose(p);

					DataBase::RawBlockData raw_data = DataBase::convertToRawFromBlock(blockId,pose);

					const int WD = WIDTH * DEPTH;
					const int W = WIDTH;
					const int INDEX = WD * h + W * d + w;
					blocks[INDEX] = raw_data.getId();
					data[INDEX] = raw_data.getExtention();
				}
			}
		}
	}

	root->addCompoundChild( nbt::Tag::makeTag("Blocks",nbt::TAG_Byte_Array,blocks) );
	root->addCompoundChild( nbt::Tag::makeTag("Data",nbt::TAG_Byte_Array,data) );

	nbt::write_nbt(root,filename.c_str());
}
}//Operation
}//MinePlanner
