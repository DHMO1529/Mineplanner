#ifndef MINEPLANNER_GLOBALCONFIGENUMDEF_HPP
#define MINEPLANNER_GLOBALCONFIGENUMDEF_HPP
namespace MinePlanner{
//���[�h
enum Mode{
	MODE_VIEW = 0,
	MODE_EDIT,
};
//�J�������[�h
enum CameraMode{
	CAMERA_MODE_NORMAL = 0,
	CAMERA_MODE_ORTHO,
};
//�T�u���[�h
enum SubMode{
	SUBMODE_BASIC,
	SUBMODE_SELECT,
};
/**
* �ҏW�^�C�v�̒�`
*/
enum EditType{
	EDITTYPE_ADD = 0,
	EDITTYPE_SWAP,
	EDITTYPE_DELETE,
};
}//MinePlanner
#endif