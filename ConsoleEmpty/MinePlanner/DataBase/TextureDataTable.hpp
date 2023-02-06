#ifndef MINEPLANNER_DATABASE_TEXTUREDATATABLE_HPP
#define MINEPLANNER_DATABASE_TEXTUREDATATABLE_HPP
#include <boost/unordered_map.hpp>
#include <sqlite3x.hpp>
#include "MinePlanner/DataBase/TextureData.hpp"
namespace MinePlanner{
namespace DataBase{
typedef int BlockID;
class TextureDataTable
{
public:
	TextureDataTable(sqlite3x::sqlite3_connection& connection);
	TextureData getFaceUV(BlockID blockId,int face)const;
private:
	typedef boost::array<TextureData,6> BlockTextureData;
	boost::unordered_map<BlockID,BlockTextureData> m_texture_datas;
};
}//DataBase
}//MinePlanner
#endif