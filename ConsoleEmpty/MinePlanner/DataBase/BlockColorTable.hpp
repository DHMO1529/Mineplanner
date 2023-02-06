#ifndef MINEPLANNER_DATABASE_BLOCKCOLORTABLE_HPP
#define MINEPLANNER_DATABASE_BLOCKCOLORTABLE_HPP
#include <boost/unordered_map.hpp>
#include <sqlite3x.hpp>
#include "MinePlanner/Color.hpp"
namespace MinePlanner{
namespace DataBase{
typedef int BlockID;
class BlockColorTable
{
public:
	BlockColorTable(sqlite3x::sqlite3_connection& connection);

	int getNearColorBlockID(const Color& color)const;
private:
	boost::unordered_map<BlockID,Color> m_color_table;
};
}//DataBase
}//MinePlanner
#endif