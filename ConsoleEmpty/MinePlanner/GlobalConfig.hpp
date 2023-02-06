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

	//�o�C���h�̂���
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

	//���[�h
	virtual int getMode()const = 0;
	//�X���C�X���[�h
	virtual bool getSliceModeEnable()const = 0;
	//�X���C�X�̍���
	virtual int getSliceHeight()const = 0;
	//�㉺�u���b�N��`�悷�邩
	virtual bool getUpBlockEnable()const = 0;
	virtual bool getDownBlockEnable()const = 0;
	//�u���b�N�̗֊s�̗L��
	virtual bool getBlockContourEnable()const = 0;
	//���C�g�̗L��
	virtual bool getLightEnable()const = 0;
	//�J�������[�h
	virtual int getCameraMode()const = 0;
	//�ҏW�^�C�v
	virtual int getEditType()const = 0;
	//�I���u���b�N
	virtual int getSelectBlock()const = 0;
	//�ҏW�O���b�h
	virtual bool getEditGridEnable()const = 0;
	//�ҏW�O���b�h�̍�����ݒ�
	virtual int getEditGridHeight()const = 0;
	//�I�����[�h��ݒ�
	virtual int getSubMode()const = 0;
};
GlobalConfig* getGlobalConfigInstance();
}//MinePlanner

#define g_config MinePlanner::getGlobalConfigInstance()

#endif