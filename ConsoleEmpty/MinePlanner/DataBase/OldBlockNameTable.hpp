#ifndef MINEPLANNER_DATABASE_OLDBLOCKNAMETABLE_HPP
#define MINEPLANNER_DATABASE_OLDBLOCKNAMETABLE_HPP
#include <string>
#include <boost/unordered_map.hpp>
#include <sqlite3x.hpp>
namespace MinePlanner{
namespace DataBase{
class OldBlockNameTable
{
public:
	OldBlockNameTable(sqlite3x::sqlite3_connection& connection);

	int convertBlockIdFromOldBlockName(const char* old_name)const;
private:
	boost::unordered_map<std::string,int> m_table;
};
}//DataBase
}//MinePlanner
#endif