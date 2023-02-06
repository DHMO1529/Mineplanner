#include "MinePlanner/DataBase/RawBlockTable.hpp"
#include <iostream>
#include <cassert>
#include <map>
#include <set>
#include <exception>
#include <boost/assign.hpp>
#include <boost/unordered_set.hpp>
//special blocks
const int RAWID_WOOD = 17;
const int RAWID_WOOL = 35;
/*Wooden CobbleStone Brick StoneBrick*/
const std::set<int> RAWID_STAIRS = boost::assign::list_of(53)(67)(108)(109);
/*Furnace Dispenser Chest*/
const std::set<int> RAWID_FURNACE_etc = boost::assign::list_of(61)(23)(54);
/*Pumpkin Jack-O-Lantern*/
const std::set<int> RAWID_PUMPKINS = boost::assign::list_of(86)(91);
const int RAWID_SLABS = 44;
const int RAWID_DOUBLESLABS = 43;//StoneDoubleSlabÇµÇ©Ç»Ç¢
const int RAWID_STONEBRICK = 98;

const boost::unordered_set<int> special_blocks_raw = boost::assign::list_of
	(17)(35)(53)(67)(108)(109)(61)(23)(54)(86)(91)(44)(43)(98);

const int PLANNER_EAST = 0;
const int PLANNER_WEST = 2;
const int PLANNER_SOUTH = 3;
const int PLANNER_NORTH = 1;

namespace MinePlanner{
namespace DataBase{
RawBlockTable::RawBlockTable(sqlite3x::sqlite3_connection& connection)
{
	try{
		if(true){
			sqlite3x::sqlite3_command command(connection,L"SELECT * FROM ÉuÉçÉbÉNÇhÇcÇ©ÇÁê∂ÇhÇc");
			sqlite3x::sqlite3_reader reader = command.executereader();
			while(reader.read())
			{
				const int blockId = reader.getint(0);
				const int rawId = reader.getint(1);
				m_block_to_raw[ blockId ] = rawId;
			}
		}
		if(true){
			sqlite3x::sqlite3_command command(connection,L"SELECT * FROM ê∂ÇhÇcÇ©ÇÁÉuÉçÉbÉNÇhÇc");
			sqlite3x::sqlite3_reader reader = command.executereader();
			while(reader.read())
			{
				const int rawId = reader.getint(0);
				const int blockId = reader.getint(1);
				m_raw_to_block[ rawId ] = blockId;
			}
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
}
//ÉuÉçÉbÉNÅ®ê∂
RawBlockData RawBlockTable::convertToRawFromBlock(BlockID blockId,const Pose& pose)const
{
	auto it = m_block_to_raw.find(blockId);
	if(it == m_block_to_raw.end())
	{
		//ãÛÉuÉçÉbÉN
		return RawBlockData::make(0,0);
	}

	const unsigned char raw_id = static_cast<unsigned char>(it->second);
	if(special_blocks_raw.find(raw_id) == special_blocks_raw.end())
	{
		//ÇªÇÃÇ‹Ç‹ïœä∑Ç≈Ç´ÇÈÉuÉçÉbÉN
		return RawBlockData::make(raw_id,0);
	}

	//ì¡éÍÉuÉçÉbÉN
	if(raw_id == RAWID_WOOD)
	{
		switch(blockId)
		{
		case 10:/*Wood*/
			return RawBlockData::make(raw_id,0);
		case 11:/*Wood(Black)*/
			return RawBlockData::make(raw_id,1);
		case 12:/*Wood(White)*/
			return RawBlockData::make(raw_id,2);
		}
	}
	else if(raw_id == RAWID_WOOL)
	{
		/*ÉvÉâÉìÉiÅ[ID - extention*/
		static const std::map<int,unsigned char> table = boost::assign::map_list_of
			(24,0)
			(25,1)
			(26,2)
			(27,3)
			(28,4)
			(29,5)
			(30,6)
			(31,7)
			(32,8)
			(33,9)
			(34,10)
			(35,11)
			(36,12)
			(37,13)
			(38,14)
			(39,15);
		return RawBlockData::make(raw_id,table.find(blockId)->second);
	}
	else if(RAWID_STAIRS.find(raw_id) != RAWID_STAIRS.end())
	{
		switch(pose.get_rotatey())
		{
		case PLANNER_SOUTH:/*ìÏ*/
			return RawBlockData::make(raw_id,0);
		case PLANNER_EAST:/*ìå*/
			return RawBlockData::make(raw_id,3);
		case PLANNER_NORTH:/*ñk*/
			return RawBlockData::make(raw_id,1);
		case PLANNER_WEST:/*êº*/
			return RawBlockData::make(raw_id,2);
		}
	}
	else if(RAWID_FURNACE_etc.find(raw_id) != RAWID_FURNACE_etc.end())
	{
		//Ç«Ç§Ç‚ÇÁÇ±Ç±ÇæÇØå¸Ç´Ç™ãtÇÁÇµÇ¢
		switch(pose.get_rotatey())
		{
		case PLANNER_SOUTH:/*ìÏ*/
			return RawBlockData::make(raw_id,4);
		case PLANNER_EAST:/*ìå*/
			return RawBlockData::make(raw_id,3);
		case PLANNER_NORTH:/*ñk*/
			return RawBlockData::make(raw_id,5);
		case PLANNER_WEST:/*êº*/
			return RawBlockData::make(raw_id,2);
		}
	}
	else if(RAWID_PUMPKINS.find(raw_id) != RAWID_PUMPKINS.end())
	{
		switch(pose.get_rotatey())
		{
		case PLANNER_SOUTH:/*ìÏ*/
			return RawBlockData::make(raw_id,1);
		case PLANNER_EAST:/*ìå*/
			return RawBlockData::make(raw_id,0);
		case PLANNER_NORTH:/*ñk*/
			return RawBlockData::make(raw_id,3);
		case PLANNER_WEST:/*êº*/
			return RawBlockData::make(raw_id,2);
		}
	}
	else if(raw_id == RAWID_SLABS)
	{
		switch(blockId)
		{
		case 43:/*StoneSlab*/
			return RawBlockData::make(raw_id,0);
		case 44:/*SandStoneSlab*/
			return RawBlockData::make(raw_id,1);
		case 45:/*WoodenPlankSlab*/
			return RawBlockData::make(raw_id,2);
		case 46:/*CobbleStoneSlab*/
			return RawBlockData::make(raw_id,3);
		case 47:/*BrickSlab*/
			return RawBlockData::make(raw_id,4);
		case 48:/*StoneBrickSlab*/
			return RawBlockData::make(raw_id,5);
		}
	}
	else if(blockId == RAWID_DOUBLESLABS)
	{
		return RawBlockData::make(raw_id,0);
	}
	else if(raw_id == RAWID_STONEBRICK)
	{
		switch(blockId)
		{
		case 70:/*StoneBrick*/
			return RawBlockData::make(raw_id,0);
		case 76:/*CrackedStoneBrick*/
			return RawBlockData::make(raw_id,2);
		case 77:/*MossyStoneBrick*/
			return RawBlockData::make(raw_id,1);
		}
	}

	assert(0);
	return RawBlockData::make(raw_id,0);
}
BlockData RawBlockTable::convertToBlockFromRaw(const RawBlockData& raw_block_data)const
{
	const int raw_id = raw_block_data.getId();
	if(special_blocks_raw.find(raw_id) == special_blocks_raw.end())
	{
		auto it = m_raw_to_block.find(raw_id);
		if(it == m_raw_to_block.end())
		{
			throw std::bad_cast();
		}
		//í èÌÉuÉçÉbÉNÅ@âÒì]Ç‡ÇµÇ»Ç¢
		const int blockId = it->second;
		return BlockData(blockId,Pose());
	}

	int id = -1;
	Pose pose;

	const int ext = raw_block_data.getExtention();
	if(raw_id == RAWID_WOOD)
	{
		switch(ext)
		{
		case 0:
			id = 10;
			break;
		case 1:
			id = 11;
			break;
		case 2:
			id = 12;
			break;
		}
	}
	else if(raw_id == RAWID_WOOL)
	{
		static const std::vector<int> table = boost::assign::list_of
			(24)(25)(26)(27)(28)(29)(30)(31)(32)(33)(34)(35)(36)(37)(38)(39);
		id = table[ext];
	}
	else if(RAWID_STAIRS.find(raw_id) != RAWID_STAIRS.end())
	{
		static const std::map<int,int> table = boost::assign::map_list_of
			(53,53)/*ñÿäKíi*/
			(67,58)/*ä€êŒäKíi*/
			(108,74)/*ó˘ä¢äKíi*/
			(109,75)/*êŒó˘ä¢äKíi*/;
		id = table.find(raw_id)->second;
		switch(ext)
		{
		case 0:/*ìÏ*/
			pose = Pose::make(0,PLANNER_SOUTH);
			break;
		case 1:/*ñk*/
			pose = Pose::make(0,PLANNER_NORTH);
			break;
		case 2:/*êº*/
			pose = Pose::make(0,PLANNER_WEST);
			break;
		case 3:/*ìå*/
			pose = Pose::make(0,PLANNER_EAST);
			break;
		}
	}
	else if(RAWID_FURNACE_etc.find(raw_id) != RAWID_FURNACE_etc.end())
	{
		//Ç«Ç§Ç‚ÇÁÇ±Ç±ÇæÇØå¸Ç´Ç™ãtÇÁÇµÇ¢
		id = m_raw_to_block.find(raw_id)->second;
		switch(ext)
		{
		case 2:/*ìå*/
			pose = Pose::make(0,PLANNER_WEST);
			break;
		case 3:/*êº*/
			pose = Pose::make(0,PLANNER_EAST);
			break;
		case 4:/*ñk*/
			pose = Pose::make(0,PLANNER_SOUTH);
			break;
		case 5:/*ìÏ*/
			pose = Pose::make(0,PLANNER_NORTH);
			break;
		}
	}
	else if(RAWID_PUMPKINS.find(raw_id) != RAWID_PUMPKINS.end())
	{
		id = m_raw_to_block.find(raw_id)->second;
		switch(ext)
		{
		case 0:/*ìå*/
			pose = Pose::make(0,PLANNER_EAST);
			break;
		case 1:/*ìÏ*/
			pose = Pose::make(0,PLANNER_SOUTH);
			break;
		case 2:/*êº*/
			pose = Pose::make(0,PLANNER_WEST);
			break;
		case 3:/*ñk*/
			pose = Pose::make(0,PLANNER_NORTH);
			break;
		}
	}
	else if(raw_id == RAWID_SLABS)
	{
		static const std::vector<int> table = boost::assign::list_of
			(43)(44)(45)(46)(47)(48)(43);
		id = table[ext];
	}
	else if(raw_id == RAWID_DOUBLESLABS)
	{
		static const std::vector<int> table = boost::assign::list_of
			(42)(18)(3)(2)(49)(70)(42);
		id = table[ext];
	}
	else if(raw_id == RAWID_STONEBRICK)
	{
		static const std::vector<int> table = boost::assign::list_of
			(70)(76)(77);
		id = table[ext];
	}

	if(id == -1){
		assert(0);
		throw std::bad_cast();
	}
	return BlockData(id,pose);
}
}//DataBase
}//MinePlanner

//ÉsÉXÉgÉìÅ@ï€óØ
	//else if(blockId == RAWID_PISTON)
	//{
	//	if(pose.get_rotatex() == 0)
	//	{
	//		//è„
	//		return RawBlockData::make(raw_id,1);
	//	}
	//	else if(pose.get_rotatex() == 1)
	//	{
	//		switch(pose.get_rotatey())
	//		{
	//		case 0:/*ìÏ*/
	//			return RawBlockData::make(raw_id,5);
	//		case 1:/*ìå*/
	//			return RawBlockData::make(raw_id,2);
	//		case 2:/*ñk*/
	//			return RawBlockData::make(raw_id,4);
	//		case 3:/*êº*/
	//			return RawBlockData::make(raw_id,3);
	//		}
	//	}
	//	else if(pose.get_rotatex() == 2)
	//	{
	//		//â∫
	//		return RawBlockData::make(raw_id,0);
	//	}
	//	assert(0);
	//}