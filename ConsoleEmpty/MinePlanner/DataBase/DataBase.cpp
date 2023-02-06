#include "MinePlanner/DataBase/DataBase.hpp"
#include <iostream>
#include <sstream>
#include <sqlite3x.hpp>
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/DataBase/TextureDataTable.hpp"
#include "MinePlanner/DataBase/BlockAttributeTable.hpp"
#include "MinePlanner/DataBase/BlockColorTable.hpp"
#include "MinePlanner/DataBase/RawBlockTable.hpp"
#include "MinePlanner/DataBase/BlockMaster.hpp"
#include "MinePlanner/DataBase/ComboBoxTable.hpp"
#include "MinePlanner/DataBase/OldBlockNameTable.hpp"
namespace MinePlanner{
namespace DataBase{
const wchar_t* DATABASE_NAME = L"db.sqlite3";

//global variables
static sqlite3x::sqlite3_connection g_connection;
static TextureDataTable* g_pTextureDataTable = 0;
static BlockAttributeTable* g_pBlockAttributeTable = 0;
static BlockColorTable* g_pBlockColorTable = 0;
static RawBlockTable* g_pRawBlockTable = 0;
static BlockMaster* g_pBlockMaster = 0;
static ComboBoxTable* g_pComboBoxTable = 0;
static OldBlockNameTable* g_pOldBlockNameTable = 0;

void Init()
{
	g_connection.open(DATABASE_NAME);

	g_pTextureDataTable = new TextureDataTable(g_connection);
	g_pBlockAttributeTable = new BlockAttributeTable(g_connection);
	g_pBlockColorTable = new BlockColorTable(g_connection);
	g_pRawBlockTable = new RawBlockTable(g_connection);
	g_pBlockMaster = new BlockMaster(g_connection);
	g_pComboBoxTable = new ComboBoxTable(g_connection);
	g_pOldBlockNameTable = new OldBlockNameTable(g_connection);
}
void Fin()
{
	delete g_pOldBlockNameTable; g_pOldBlockNameTable = 0;
	delete g_pComboBoxTable; g_pComboBoxTable = 0;
	delete g_pBlockMaster; g_pBlockMaster = 0;
	delete g_pRawBlockTable; g_pRawBlockTable = 0;
	delete g_pBlockColorTable; g_pBlockColorTable = 0;
	delete g_pBlockAttributeTable; g_pBlockAttributeTable = 0;
	delete g_pTextureDataTable; g_pTextureDataTable = 0;

	g_connection.close();
}
bool isExistBlock(int blockId)
{
	return g_pBlockMaster->isExistBlock(blockId);
}
std::string getName(int blockId)
{
	return g_pBlockMaster->getName(blockId);
}
std::string getNameJp(int blockId)
{
	return g_pBlockMaster->getNameJp(blockId);
}
int getOrientType(int blockId)
{
	return g_pBlockAttributeTable->getOrientType(blockId);
}
int getDrawType(int blockId)
{
	return g_pBlockAttributeTable->getDrawType(blockId);
}
TextureData getFaceUV(int blockId,int face)
{
	return g_pTextureDataTable->getFaceUV(blockId,face);
}
int getNearColorBlockID(const Color& color)
{
	return g_pBlockColorTable->getNearColorBlockID(color);
}
RawBlockData convertToRawFromBlock(int blockId,const Pose& pose)
{
	return g_pRawBlockTable->convertToRawFromBlock(blockId,pose);
}
BlockData convertToBlockFromRaw(const RawBlockData& raw_block_data)
{
	return g_pRawBlockTable->convertToBlockFromRaw(raw_block_data);
}
std::vector<int> getComboboxOrder()
{
	return g_pComboBoxTable->getComboboxOrder();
}
std::vector<int> getModelDrawBlockList()
{
	std::vector<int> list;
	try{
		sqlite3x::sqlite3_command command(g_connection,L"SELECT マインプランナーＩＤ FROM ブロック属性 WHERE 描画タイプ = 1");
		sqlite3x::sqlite3_reader reader = command.executereader();
		while(reader.read())
		{
			list.push_back( reader.getint(0) );
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
	return list;
}
std::vector<int> getNormalDrawBlockList()
{
	std::vector<int> list;
	try{
		sqlite3x::sqlite3_command command(g_connection,L"SELECT マインプランナーＩＤ FROM ブロック属性 WHERE 描画タイプ = 0");
		sqlite3x::sqlite3_reader reader = command.executereader();
		while(reader.read())
		{
			list.push_back( reader.getint(0) );
		}
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}
	return list;
}
int convertBlockIdFromOldBlockName(const char* old_name)
{
	return g_pOldBlockNameTable->convertBlockIdFromOldBlockName(old_name);
}
std::pair<int,int> getMiniPictureXY(int blockId)
{
	try{
		std::stringstream ss;
		ss << "SELECT 画像Ｘ,画像Ｙ FROM ブロックミニ画像 WHERE マインプランナーＩＤ = " << blockId;
		std::wstring query = string_cast<std::wstring,std::string>( ss.str() );
		sqlite3x::sqlite3_command command(g_connection,query);
		sqlite3x::sqlite3_reader reader = command.executereader();
		reader.read();
		const int x = reader.getint(0);
		const int y = reader.getint(1);
		return std::make_pair(x,y);
	}catch(sqlite3x::database_error& e){
		std::cout << e.what() << std::endl;
		assert(0);
	}

	return std::make_pair(0,0);
}
}//DataBase
}//MinePlanner