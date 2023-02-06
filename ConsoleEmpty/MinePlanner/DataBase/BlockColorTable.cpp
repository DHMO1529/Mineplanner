#include "MinePlanner/DataBase/BlockColorTable.hpp"
#include <iostream>
#include <boost/foreach.hpp>
namespace MinePlanner{
namespace DataBase{
BlockColorTable::BlockColorTable(sqlite3x::sqlite3_connection& connection)
{
	try{
		sqlite3x::sqlite3_command command(connection,L"SELECT * FROM ブロックカラー");
		sqlite3x::sqlite3_reader reader = command.executereader();
		while(reader.read())
		{
			const int blockId = reader.getint(0);
			const Color::uint8 r = static_cast<Color::uint8>( reader.getint(1) );
			const Color::uint8 g = static_cast<Color::uint8>( reader.getint(2) );
			const Color::uint8 b = static_cast<Color::uint8>( reader.getint(3) );
			m_color_table[ blockId ] = Color::make_color(r,g,b);
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
}
int BlockColorTable::getNearColorBlockID(const Color& color)const
{
	int result_blockId = -1;
	float diff = std::numeric_limits<float>::max();
	typedef boost::unordered_map<BlockID,Color>::value_type value_type;
	BOOST_FOREACH(const value_type& val,m_color_table)
	{
		const int blockId = val.first;
		const Color& color_data = val.second;

		const float this_diff = Color::diff(color,color_data);
		if(this_diff < diff)
		{
			result_blockId = blockId;
			diff = this_diff;
		}
	}
	return result_blockId;
}
}//DataBase
}//MinePlanner