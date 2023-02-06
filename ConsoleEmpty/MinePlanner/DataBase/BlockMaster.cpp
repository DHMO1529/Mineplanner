#include "MinePlanner/DataBase/BlockMaster.hpp"
#include <iostream>
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace DataBase{
BlockMaster::BlockMaster(sqlite3x::sqlite3_connection& connection):m_datas()
{
	try{
		sqlite3x::sqlite3_command command(connection,L"SELECT * FROM ブロックマスター");
		sqlite3x::sqlite3_reader reader = command.executereader();
		while(reader.read())
		{
			const int blockId = reader.getint(0);
			std::wstring name = reader.getstring16(1);
			std::wstring namejp = reader.getstring16(2);

			names add = {
				string_cast<std::string,std::wstring>(name) ,
				string_cast<std::string,std::wstring>(namejp)
			};
			m_datas[ blockId ] = add;
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
}
bool BlockMaster::isExistBlock(int blockId)const
{
	auto it = m_datas.find(blockId);
	return it != m_datas.end();
}
std::string BlockMaster::getName(int blockId)const
{
	return m_datas.find(blockId)->second.name;
}
std::string BlockMaster::getNameJp(int blockId)const
{
	return m_datas.find(blockId)->second.namejp;
}
}//DataBase
}//MinePlanner