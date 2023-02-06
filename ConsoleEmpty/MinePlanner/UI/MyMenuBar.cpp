#include "MinePlanner/UI/MyMenuBar.hpp"

#include <cassert>

#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"

#include "MinePlanner/UI/RepaintOpenGL.hpp"
#include "MinePlanner/UI/EventHandler/Functions.hpp"
#include "MinePlanner/SampleFileDef.hpp"
#include "MinePlanner/UI/isLockSaveSchematic.hpp"

namespace MinePlanner{
namespace UI{
enum Menu{
	MENU_NEW = 1,
	MENU_OPEN_PLAN,
	MENU_SAVE_PLAN,
	MENU_SAVEAS_PLAN,
	MENU_CLEAR,

	MENU_NECESSARY_MATERIAL,

	MENU_OPEN_PICTURE,

	MENU_OPEN_CUBEKINGDOM,

	MENU_OPEN_SCHEMATIC,
	MENU_SAVE_SCHEMATIC,

	MENU_MODEL_IMPORT,
	MENU_SCREENSHOT,
	MENU_CREATESHORTCUT,
	MENU_UPDATE_CHECK,
	
	MENU_OPEN_SAMPLE_QB,
	MENU_OPEN_SAMPLE_NICONICOTV,
	MENU_OPEN_SAMPLE_METALGEARREX,
	MENU_OPEN_SAMPLE_DRAGONKING,
	MENU_OPEN_SAMPLE_RAPUTA,

	MENU_CREATE_BOX,
	MENU_CREATE_SPHERE,
	MENU_CREATE_CYLINDER,
	MENU_CREATE_CONE,

	MENU_VERSION_INFO,
};
const StringArray MyMenuBar::getMenuBarNames()
{
	const wchar_t* const viewModeNames[] = {L"ファイル",L"サンプル",L"ツール",L"ヘルプ",0};
	const wchar_t* const editModeNames[] = {L"ファイル",L"サンプル",L"ツール",L"図形",L"ヘルプ",0};

	if(g_config->getMode() == MODE_VIEW)
	{
		return StringArray( viewModeNames );
	}
	return StringArray( editModeNames );
}
const PopupMenu MyMenuBar::getMenuForIndex(int topLevelMenuIndex,const String& menuName)
{
	PopupMenu menu;
	if(menuName == L"ファイル")
	{
		menu.addItem(MENU_NEW,L"新規作成");
		menu.addItem(MENU_OPEN_PLAN,L"開く");
		menu.addItem(MENU_SAVE_PLAN,L"保存 (ctrl + s)");
		menu.addItem(MENU_SAVEAS_PLAN,L"名前をつけて保存");
		menu.addItem(MENU_CLEAR,L"全消去");

		menu.addSeparator();

		menu.addItem(MENU_NECESSARY_MATERIAL,L"必要素材");

		menu.addSeparator();

		menu.addItem(MENU_OPEN_PICTURE,L"画像ファイル読み込み");

		menu.addSeparator();

		menu.addItem(MENU_OPEN_CUBEKINGDOM,L"キューブキングダムファイルを開く");

		menu.addSeparator();

		menu.addItem(MENU_OPEN_SCHEMATIC,L"Schematicファイルを開く");
		menu.addItem(MENU_SAVE_SCHEMATIC,L"Schematicファイルとして保存",!isLockSaveSchematic());
	}
	else if(menuName == L"サンプル")
	{
		menu.addItem(MENU_OPEN_SAMPLE_QB, L"キュゥべえ");
		menu.addItem(MENU_OPEN_SAMPLE_NICONICOTV, L"ニコニコテレビちゃん");
		menu.addItem(MENU_OPEN_SAMPLE_METALGEARREX, L"メタルギアRex");
		menu.addItem(MENU_OPEN_SAMPLE_DRAGONKING, L"りゅうおう");
		menu.addItem(MENU_OPEN_SAMPLE_RAPUTA, L"ラピュタ");
	}
	else if(menuName == L"ツール")
	{
		menu.addItem(MENU_MODEL_IMPORT,L"3Dモデルをインポート");
		menu.addItem(MENU_SCREENSHOT,L"スクリーンショット");
		menu.addItem(MENU_CREATESHORTCUT,L"デスクトップにショートカットを作成");
		menu.addItem(MENU_UPDATE_CHECK,L"最新版の有無をチェック");
	}
	else if(menuName == L"図形")
	{
		menu.addItem(MENU_CREATE_BOX,L"箱");
		menu.addItem(MENU_CREATE_SPHERE,L"球");
		menu.addItem(MENU_CREATE_CYLINDER,L"円柱");
		menu.addItem(MENU_CREATE_CONE,L"円錐");
	}
	else if(menuName == L"ヘルプ")
	{
		menu.addItem(MENU_VERSION_INFO,L"バージョン情報");
	}
	return menu;
}

void MyMenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	switch(menuItemID)
	{
	//ファイル
	case MENU_NEW:
		EventHandler::OnSelectedNew();
		break;
	case MENU_OPEN_PLAN:
		EventHandler::OnSelectedOpenPlan();
		break;
	case MENU_SAVE_PLAN:
		EventHandler::OnSelectedSavePlan();
		break;
	case MENU_SAVEAS_PLAN:
		EventHandler::OnSelectedSaveAsPlan();
		break;
	case MENU_CLEAR:
		EventHandler::OnSelectedClear();
		break;
	case MENU_NECESSARY_MATERIAL:
		EventHandler::OnSelectedNecessaryMaterial();
		break;

	case MENU_OPEN_PICTURE:
		EventHandler::OnSelectedOpenPicture();
		break;

	case MENU_OPEN_CUBEKINGDOM:
		EventHandler::OnSelectedOpenCubeKingdom();
		break;

	case MENU_OPEN_SCHEMATIC:
		EventHandler::OnSelectedOpenSchematic();
		break;
	case MENU_SAVE_SCHEMATIC:
		EventHandler::OnSelectedSaveSchematic();
		break;

		//サンプル
	case MENU_OPEN_SAMPLE_QB:
		EventHandler::OnSelectedOpenSample(SampleFilename::QB);
		break;
	case MENU_OPEN_SAMPLE_NICONICOTV:
		EventHandler::OnSelectedOpenSample(SampleFilename::NICONICOTV);
		break;
	case MENU_OPEN_SAMPLE_METALGEARREX:
		EventHandler::OnSelectedOpenSample(SampleFilename::METALGEARREX);
		break;
	case MENU_OPEN_SAMPLE_DRAGONKING:
		EventHandler::OnSelectedOpenSample(SampleFilename::DRAGONKING);
		break;
	case MENU_OPEN_SAMPLE_RAPUTA:
		EventHandler::OnSelectedOpenSample(SampleFilename::RAPUTA);
		break;

	//ツール
	case MENU_MODEL_IMPORT:
		EventHandler::OnSelectedModelImport();
		break;
	case MENU_SCREENSHOT:
		EventHandler::OnSelectedScreenShot();
		break;
	case MENU_CREATESHORTCUT:
		EventHandler::OnSelectedCreateShortCut();
		break;
	case MENU_UPDATE_CHECK:
		EventHandler::OnSelectedUpdateCheck();
		break;

	//図形
	case MENU_CREATE_BOX:
		EventHandler::OnSelectedCreateBox();
		break;
	case MENU_CREATE_SPHERE:
		EventHandler::OnSelectedCreateSphere();
		break;
	case MENU_CREATE_CYLINDER:
		EventHandler::OnSelectedCreateCylinder();
		break;
	case MENU_CREATE_CONE:
		EventHandler::OnSelectedCreateCone();
		break;

	case MENU_VERSION_INFO:
		EventHandler::OnSelectedVersionInfo();
		break;
	default:
		assert(0);
	}
	RepaintOpenGL();
}
}//UI
}//MinePlanner