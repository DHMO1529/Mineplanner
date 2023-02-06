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
	const wchar_t* const viewModeNames[] = {L"�t�@�C��",L"�T���v��",L"�c�[��",L"�w���v",0};
	const wchar_t* const editModeNames[] = {L"�t�@�C��",L"�T���v��",L"�c�[��",L"�}�`",L"�w���v",0};

	if(g_config->getMode() == MODE_VIEW)
	{
		return StringArray( viewModeNames );
	}
	return StringArray( editModeNames );
}
const PopupMenu MyMenuBar::getMenuForIndex(int topLevelMenuIndex,const String& menuName)
{
	PopupMenu menu;
	if(menuName == L"�t�@�C��")
	{
		menu.addItem(MENU_NEW,L"�V�K�쐬");
		menu.addItem(MENU_OPEN_PLAN,L"�J��");
		menu.addItem(MENU_SAVE_PLAN,L"�ۑ� (ctrl + s)");
		menu.addItem(MENU_SAVEAS_PLAN,L"���O�����ĕۑ�");
		menu.addItem(MENU_CLEAR,L"�S����");

		menu.addSeparator();

		menu.addItem(MENU_NECESSARY_MATERIAL,L"�K�v�f��");

		menu.addSeparator();

		menu.addItem(MENU_OPEN_PICTURE,L"�摜�t�@�C���ǂݍ���");

		menu.addSeparator();

		menu.addItem(MENU_OPEN_CUBEKINGDOM,L"�L���[�u�L���O�_���t�@�C�����J��");

		menu.addSeparator();

		menu.addItem(MENU_OPEN_SCHEMATIC,L"Schematic�t�@�C�����J��");
		menu.addItem(MENU_SAVE_SCHEMATIC,L"Schematic�t�@�C���Ƃ��ĕۑ�",!isLockSaveSchematic());
	}
	else if(menuName == L"�T���v��")
	{
		menu.addItem(MENU_OPEN_SAMPLE_QB, L"�L���D�ׂ�");
		menu.addItem(MENU_OPEN_SAMPLE_NICONICOTV, L"�j�R�j�R�e���r�����");
		menu.addItem(MENU_OPEN_SAMPLE_METALGEARREX, L"���^���M�ARex");
		menu.addItem(MENU_OPEN_SAMPLE_DRAGONKING, L"��イ����");
		menu.addItem(MENU_OPEN_SAMPLE_RAPUTA, L"���s���^");
	}
	else if(menuName == L"�c�[��")
	{
		menu.addItem(MENU_MODEL_IMPORT,L"3D���f�����C���|�[�g");
		menu.addItem(MENU_SCREENSHOT,L"�X�N���[���V���b�g");
		menu.addItem(MENU_CREATESHORTCUT,L"�f�X�N�g�b�v�ɃV���[�g�J�b�g���쐬");
		menu.addItem(MENU_UPDATE_CHECK,L"�ŐV�ł̗L�����`�F�b�N");
	}
	else if(menuName == L"�}�`")
	{
		menu.addItem(MENU_CREATE_BOX,L"��");
		menu.addItem(MENU_CREATE_SPHERE,L"��");
		menu.addItem(MENU_CREATE_CYLINDER,L"�~��");
		menu.addItem(MENU_CREATE_CONE,L"�~��");
	}
	else if(menuName == L"�w���v")
	{
		menu.addItem(MENU_VERSION_INFO,L"�o�[�W�������");
	}
	return menu;
}

void MyMenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	switch(menuItemID)
	{
	//�t�@�C��
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

		//�T���v��
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

	//�c�[��
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

	//�}�`
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