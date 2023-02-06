#ifndef MINEPLANNER_GLOBALCONFIGENUMDEF_HPP
#define MINEPLANNER_GLOBALCONFIGENUMDEF_HPP
namespace MinePlanner{
//モード
enum Mode{
	MODE_VIEW = 0,
	MODE_EDIT,
};
//カメラモード
enum CameraMode{
	CAMERA_MODE_NORMAL = 0,
	CAMERA_MODE_ORTHO,
};
//サブモード
enum SubMode{
	SUBMODE_BASIC,
	SUBMODE_SELECT,
};
/**
* 編集タイプの定義
*/
enum EditType{
	EDITTYPE_ADD = 0,
	EDITTYPE_SWAP,
	EDITTYPE_DELETE,
};
}//MinePlanner
#endif