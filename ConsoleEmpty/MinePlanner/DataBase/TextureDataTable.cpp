#include "MinePlanner/DataBase/TextureDataTable.hpp"
#include <iostream>
#include "MinePlanner/DataBase/FaceDef.hpp"
namespace MinePlanner{
namespace DataBase{
inline TextureData getTextureData(int textureIndex)
{
	//テクスチャ座標計算の定数
	static const float TEX_SIZE = 256.f;
	static const int BLOCKNUM_W = 16;

	static const float PIXEL_SIZE = 1.f / TEX_SIZE;
	static const float HALF_PIXEL_SIZE = PIXEL_SIZE / 2.f;
	static const float ONE_BLOCK_WIDTH = 1.f / BLOCKNUM_W;

	const int X = textureIndex % BLOCKNUM_W;
	const int Y = textureIndex / BLOCKNUM_W;

	//左下のuv
	const float U = HALF_PIXEL_SIZE + ONE_BLOCK_WIDTH * X;
	const float V = HALF_PIXEL_SIZE + ONE_BLOCK_WIDTH * Y;

	const float of = ONE_BLOCK_WIDTH - PIXEL_SIZE;//幅が3なら2→に動かせば右のテクスチャ座標になる
	const TextureData data = TextureData::make(
		UV::make(U,V+of),
		UV::make(U,V),
		UV::make(U+of,V),
		UV::make(U+of,V+of));
	return data;
}

TextureDataTable::TextureDataTable(sqlite3x::sqlite3_connection& connection)
{
	try{
		sqlite3x::sqlite3_command command(connection,L"SELECT * FROM 基本描画ブロックテクスチャ");
		sqlite3x::sqlite3_reader reader = command.executereader();
		while(reader.read())
		{
			BlockTextureData insert;
			insert[FACE_TOP] =    getTextureData( reader.getint(1) );
			insert[FACE_BUTTOM] = getTextureData( reader.getint(2) );
			insert[FACE_FRONT] =  getTextureData( reader.getint(3) );
			insert[FACE_LEFT] =   getTextureData( reader.getint(4) );
			insert[FACE_RIGHT] =  getTextureData( reader.getint(5) );
			insert[FACE_BACK] =   getTextureData( reader.getint(6) );
			const int blockId = reader.getint(0);
			m_texture_datas[ blockId ] = insert;
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
}
TextureData TextureDataTable::getFaceUV(BlockID blockId,int face)const
{
	boost::unordered_map<BlockID,BlockTextureData>::const_iterator it = m_texture_datas.find(blockId);
	if(it == m_texture_datas.end())
	{
		assert(0);
	}
	return it->second[face];
}
}//DataBase
}//MinePlanner