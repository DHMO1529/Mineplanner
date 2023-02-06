#ifndef MINEPLANNER_DATABASE_DATABASE_HPP
#define MINEPLANNER_DATABASE_DATABASE_HPP

#include <utility>
#include <vector>
#include <boost/optional.hpp>
#include "MinePlanner/Pose.hpp"
#include "MinePlanner/Color.hpp"
#include "MinePlanner/DataBase/RawBlockData.hpp"
#include "MinePlanner/DataBase/FaceDef.hpp"
#include "MinePlanner/DataBase/BlockAttributeDef.hpp"
#include "MinePlanner/DataBase/TextureData.hpp"
namespace MinePlanner{
namespace DataBase{
void Init();
void Fin();

bool isExistBlock(int blockId);

//名前
std::string getName(int blockId);
std::string getNameJp(int blockId);

/**
* ブロックの指向性情報を取得する
* @param blockId マインプランナー独自定義ＩＤ
* @return 指向性タイプ
*/
int getOrientType(int blockId);

/**
* ブロックの描画タイプを取得する
* @param blockId マインプランナー独自定義ＩＤ
* @return ブロックの描画タイプ
*/
int getDrawType(int blockId);

/**
* 描画する際のテクスチャＵＶ情報を取得する
* @param blockId マインプランナー独自定義ＩＤ
* @param face どの面を取得するのか
* @return 面のテクスチャＵＶ
*/
TextureData getFaceUV(int blockId,int face);

/**
* 色に近いブロックＩＤを取得する
* @param color 判定する色
* @return 色に近いブロックＩＤ
*/
int getNearColorBlockID(const Color& color);

/*生ＩＤとプランナーブロックを変換*/
RawBlockData convertToRawFromBlock(int blockId,const Pose& pose);

typedef std::pair<int,Pose> BlockData;//id,pose
BlockData convertToBlockFromRaw(const RawBlockData& raw_block_data);

//コンボボックスに表示する順序
std::vector<int> getComboboxOrder();

//モデルで描画するもののリスト
std::vector<int> getModelDrawBlockList();

//通常描画するもののリスト
std::vector<int> getNormalDrawBlockList();

//旧ブロックから新ブロックへ
int convertBlockIdFromOldBlockName(const char* old_name);

//ミニ画像xy座標
std::pair<int,int> getMiniPictureXY(int blockId);
}//DataBase
}//MinePlanner
#endif