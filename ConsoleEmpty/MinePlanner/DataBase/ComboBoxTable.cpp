#include "MinePlanner/DataBase/ComboBoxTable.hpp"
#include <cassert>
#include <iostream>
namespace MinePlanner{
namespace DataBase{
ComboBoxTable::ComboBoxTable(sqlite3x::sqlite3_connection& connection):m_combobox_order()
{
	try{
		sqlite3x::sqlite3_command command(connection,L"SELECT マインプランナーＩＤ FROM コンボボックス表示順 ORDER BY 順序 ASC");
		sqlite3x::sqlite3_reader reader = command.executereader();

		while(reader.read())
		{
			m_combobox_order.push_back( reader.getint(0) );
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
}
}//DataBase
}//MinePlanner