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

//���O
std::string getName(int blockId);
std::string getNameJp(int blockId);

/**
* �u���b�N�̎w���������擾����
* @param blockId �}�C���v�����i�[�Ǝ���`�h�c
* @return �w�����^�C�v
*/
int getOrientType(int blockId);

/**
* �u���b�N�̕`��^�C�v���擾����
* @param blockId �}�C���v�����i�[�Ǝ���`�h�c
* @return �u���b�N�̕`��^�C�v
*/
int getDrawType(int blockId);

/**
* �`�悷��ۂ̃e�N�X�`���t�u�����擾����
* @param blockId �}�C���v�����i�[�Ǝ���`�h�c
* @param face �ǂ̖ʂ��擾����̂�
* @return �ʂ̃e�N�X�`���t�u
*/
TextureData getFaceUV(int blockId,int face);

/**
* �F�ɋ߂��u���b�N�h�c���擾����
* @param color ���肷��F
* @return �F�ɋ߂��u���b�N�h�c
*/
int getNearColorBlockID(const Color& color);

/*���h�c�ƃv�����i�[�u���b�N��ϊ�*/
RawBlockData convertToRawFromBlock(int blockId,const Pose& pose);

typedef std::pair<int,Pose> BlockData;//id,pose
BlockData convertToBlockFromRaw(const RawBlockData& raw_block_data);

//�R���{�{�b�N�X�ɕ\�����鏇��
std::vector<int> getComboboxOrder();

//���f���ŕ`�悷����̂̃��X�g
std::vector<int> getModelDrawBlockList();

//�ʏ�`�悷����̂̃��X�g
std::vector<int> getNormalDrawBlockList();

//���u���b�N����V�u���b�N��
int convertBlockIdFromOldBlockName(const char* old_name);

//�~�j�摜xy���W
std::pair<int,int> getMiniPictureXY(int blockId);
}//DataBase
}//MinePlanner
#endif