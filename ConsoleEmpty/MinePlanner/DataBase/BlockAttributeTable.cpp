#include "MinePlanner/DataBase/BlockAttributeTable.hpp"
#include <iostream>
namespace MinePlanner{
namespace DataBase{
BlockAttributeTable::BlockAttributeTable(sqlite3x::sqlite3_connection& connection)
{
	try{
		sqlite3x::sqlite3_command command(connection,L"SELECT * FROM ƒuƒƒbƒN‘®«");
		sqlite3x::sqlite3_reader reader = command.executereader();
		while(reader.read())
		{
			const int blockId = reader.getint(0);
			Attribute attribute = { reader.getint(1) , reader.getint(2) };
			m_attributes[ blockId ] = attribute; 
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
}
int BlockAttributeTable::getOrientType(BlockID blockId)const
{
	boost::unordered_map<BlockID,Attribute>::const_iterator it = m_attributes.find(blockId);
	if(it == m_attributes.end())
	{
		assert(0);
	}
	return it->second.orient_type;
}
int BlockAttributeTable::getDrawType(BlockID blockId)const
{
	boost::unordered_map<BlockID,Attribute>::const_iterator it = m_attributes.find(blockId);
	if(it == m_attributes.end())
	{
		assert(0);
	}
	return it->second.draw_type;
}
}//DataBase
}//MinePlanner