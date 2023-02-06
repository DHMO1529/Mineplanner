#ifndef MINEPLANNER_DATABASE_BLOCKMASTER_HPP
#define MINEPLANNER_DATABASE_BLOCKMASTER_HPP
#include <string>
#include <sqlite3x.hpp>
#include <boost/unordered_map.hpp>
namespace MinePlanner{
namespace DataBase{
class BlockMaster
{
public:
	BlockMaster(sqlite3x::sqlite3_connection& connection);

	bool isExistBlock(int blockId)const;
	std::string getName(int blockId)const;
	std::string getNameJp(int blockId)const;
private:
	struct names{
		std::string name;
		std::string namejp;
	};
	boost::unordered_map<int,names> m_datas;
};
}//DataBase
}//MinePlanner
#endif