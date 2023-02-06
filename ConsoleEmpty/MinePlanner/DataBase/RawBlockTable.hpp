#ifndef MINEPLANNER_DATABASE_RAWBLOCKTABLE_HPP
#define MINEPLANNER_DATABASE_RAWBLOCKTABLE_HPP
#include <utility>
#include <sqlite3x.hpp>
#include <boost/unordered_map.hpp>
#include "MinePlanner/DataBase/RawBlockData.hpp"
#include "MinePlanner/Pose.hpp"
namespace MinePlanner{
namespace DataBase{
typedef int RawID;
typedef int BlockID;
typedef std::pair<BlockID,Pose> BlockData;
class RawBlockTable
{
public:
	RawBlockTable(sqlite3x::sqlite3_connection& connection);

	RawBlockData convertToRawFromBlock(BlockID blockId,const Pose& pose)const;

	//コンバートに失敗すると、bad_castをスローします。
	BlockData convertToBlockFromRaw(const RawBlockData& raw_block_data)const;
private:
	boost::unordered_map<BlockID,RawID> m_block_to_raw;
	boost::unordered_map<RawID,BlockID> m_raw_to_block;
};
}//DataBase
}//MinePlanner
#endif