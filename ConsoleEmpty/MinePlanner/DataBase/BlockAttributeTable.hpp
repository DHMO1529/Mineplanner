#ifndef MINEPLANNER_DATABASE_BLOCKATTRIBUTETABLE_HPP
#define MINEPLANNER_DATABASE_BLOCKATTRIBUTETABLE_HPP
#include <sqlite3x.hpp>
#include <boost/unordered_map.hpp>
namespace MinePlanner{
namespace DataBase{
typedef int BlockID;
class BlockAttributeTable
{
public:
	BlockAttributeTable(sqlite3x::sqlite3_connection& connection);

	int getOrientType(BlockID blockId)const;
	int getDrawType(BlockID blockId)const;
private:
	struct Attribute{
		int orient_type;
		int draw_type;
	};
	boost::unordered_map<BlockID,Attribute> m_attributes;
};
}//DataBase
}//MinePlanner
#endif