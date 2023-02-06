#ifndef MINEPLANNER_GLOBALCONFIG
#define MINEPLANNER_GLOBALCONFIG
#include <string>
#include <juce.h>
namespace MinePlanner{
class GlobalConfig
{
public:
	virtual void clear() = 0;
	virtual std::string toString()const = 0;

	//バインドのため
	virtual Value& getSliceModeEnableValueObject() = 0;//bool
	virtual Value& getModeValueObject() = 0;//int
	virtual Value& getSliceHeightValueObject() = 0;//double
	virtual Value& getUpBlockEnableValueObject() = 0;//bool
	virtual Value& getDownBlockEnableValueObject() = 0;//bool
	virtual Value& getBlockContourEnableValueObject() = 0;//bool
	virtual Value& getLightEnableValueObject() = 0;//bool
	virtual Value& getCameraModeValueObject() = 0;//int
	virtual Value& getEditTypeValueObject() = 0;//int
	virtual Value& getSelectBlockValueObject() = 0;//int
	virtual Value& getEditGridEnableValueObject() = 0;//int
	virtual Value& getEditGridHeightValueObject() = 0;//double
	virtual Value& getSubModeValueObject() = 0;//int

	//モード
	virtual int getMode()const = 0;
	//スライスモード
	virtual bool getSliceModeEnable()const = 0;
	//スライスの高さ
	virtual int getSliceHeight()const = 0;
	//上下ブロックを描画するか
	virtual bool getUpBlockEnable()const = 0;
	virtual bool getDownBlockEnable()const = 0;
	//ブロックの輪郭の有無
	virtual bool getBlockContourEnable()const = 0;
	//ライトの有無
	virtual bool getLightEnable()const = 0;
	//カメラモード
	virtual int getCameraMode()const = 0;
	//編集タイプ
	virtual int getEditType()const = 0;
	//選択ブロック
	virtual int getSelectBlock()const = 0;
	//編集グリッド
	virtual bool getEditGridEnable()const = 0;
	//編集グリッドの高さを設定
	virtual int getEditGridHeight()const = 0;
	//選択モードを設定
	virtual int getSubMode()const = 0;
};
GlobalConfig* getGlobalConfigInstance();
}//MinePlanner

#define g_config MinePlanner::getGlobalConfigInstance()

#endif