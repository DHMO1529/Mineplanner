#include "MinePlanner/DataBase/OldBlockNameTable.hpp"
#include <iostream>
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace DataBase{
OldBlockNameTable::OldBlockNameTable(sqlite3x::sqlite3_connection& connection)
{
	try{
		sqlite3x::sqlite3_command command(connection,L"SELECT * FROM ‹ŒƒuƒƒbƒN–¼");
		sqlite3x::sqlite3_reader reader = command.executereader();
		while(reader.read())
		{
			const std::string old_name = string_cast<std::string,std::wstring>( reader.getstring16(0) );
			m_table[ old_name ] = reader.getint(1);
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
}
int OldBlockNameTable::convertBlockIdFromOldBlockName(const char* old_name)const
{
	boost::unordered_map<std::string,int>::const_iterator it = m_table.find(old_name);
	if(it == m_table.end())
	{
		return 24;//white wool
	}
	return it->second;
}
}//DataBase
}//MinePlanner