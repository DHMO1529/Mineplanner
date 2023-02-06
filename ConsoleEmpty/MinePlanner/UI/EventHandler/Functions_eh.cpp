#include "MinePlanner/UI/EventHandler/Functions.hpp"

#include <sstream>
#include <exception>
#include <boost/filesystem.hpp>
#include <boost/unordered_set.hpp>
#include <boost/assign.hpp>
#include <boost/function.hpp>

#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/Net/UpdateCheck.hpp"
#include "MinePlanner/UI/NecessaryMaterialDialog.hpp"
#include "MinePlanner/UI/EventHandler/ImportModel.hpp"
#include "MinePlanner/UI/RepaintOpenGL.hpp"
#include "MinePlanner/graphic/graphic.hpp"
#include "Util/Lerp.hpp"

#include "MinePlanner/Operation/Manager.hpp"
#include "MinePlanner/Operation/EditManager.hpp"
#include "MinePlanner/Operation/ArrangementManager.hpp"
#include "MinePlanner/Operation/SelectionManager.hpp"
#include "MinePlanner/Log/LogManager.hpp"

#include "MinePlanner/Operation/OpenPlan.hpp"
#include "MinePlanner/Operation/OpenOldPlan.hpp"
#include "MinePlanner/Operation/SavePlan.hpp"
#include "MinePlanner/Operation/OpenPicture.hpp"
#include "MinePlanner/Operation/OpenCubeKingdom.hpp"
#include "MinePlanner/Operation/OpenSchematic.hpp"
#include "MinePlanner/Operation/SaveSchematic.hpp"

#include "MinePlanner/UI/Shape/BoxDesigner.hpp"
#include "MinePlanner/UI/Shape/SphereDesigner.hpp"
#include "MinePlanner/UI/Shape/CylinderDesigner.hpp"
#include "MinePlanner/UI/Shape/ConeDesigner.hpp"
#include "MinePlanner/Shape/CreateBox.hpp"
#include "MinePlanner/Shape/CreateSphere.hpp"
#include "MinePlanner/Shape/CreateCylinder.hpp"
#include "MinePlanner/Shape/CreateCone.hpp"

#include "MinePlanner/UI/MakeSnapShot.hpp"
#include "Platform/CreateDesktopShortCut.hpp"
#include "MinePlanner/ApplicationConstant.hpp"
#include "Platform/FileDialog.hpp"

namespace MinePlanner{
namespace UI{
namespace EventHandler{
void OnSelectedNew()
{
	if(World::instance().getBlockNum() > 0)
	{
		bool result = NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,L"����",L"�S���u���b�N���������Ă���낵���ł����H");
		if(result)
		{
			g_pEditManager()->allClear();
			g_pEditManager()->setFilename("");
			g_pEditManager()->edited();
		}
	}
}
void OnSelectedOpenPlan()
{
	Platform::FileDialog::Filters filters;
	filters.add("*.plan","�݌v�t�@�C��(*.plan)");
	Platform::FileDialog fd("�݌v�t�@�C�����J��","",filters);

	if(fd.show_open())
	{
		auto filename = fd.get_filename();
		boost::function<void(std::string)> open_func;
		if(Operation::isEnablePlanFile(filename))
		{
			open_func = Operation::OpenPlan;
		}
		else if(Operation::isEnableOldPlanFile(filename))
		{
			open_func = Operation::OpenOldPlan;
		}
		else
		{
			NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"�G���[",L"�t�@�C���`�����s���ł��B");
			return;
		}

		g_pEditManager()->allClear();

		open_func( filename );

		g_pEditManager()->setFilename( filename );
		g_pEditManager()->saved();
	}
}
void OnSelectedSavePlan()
{
	std::string filename = g_pEditManager()->getFilename();
	if(filename.empty())
	{
		Platform::FileDialog::Filters filters;
		filters.add("*.plan","�݌v�t�@�C��(*.plan)");
		Platform::FileDialog fd("�݌v�t�@�C���̕ۑ�","����1",filters);
		if(fd.show_save())
		{
			filename = fd.get_filename();
		}
		else
		{
			//�L�����Z��
			return;
		}
	}

	Operation::SavePlan( filename );
	g_pEditManager()->setFilename( filename );
	g_pEditManager()->saved();
}
void OnSelectedSaveAsPlan()
{
	Platform::FileDialog::Filters filters;
	filters.add("*.plan","�݌v�t�@�C��(*.plan)");
	Platform::FileDialog fd("�݌v�t�@�C���̕ۑ�","����1",filters);
	if(fd.show_save())
	{
		auto filename = fd.get_filename();
		Operation::SavePlan( filename );
		g_pEditManager()->setFilename( filename );
		g_pEditManager()->saved();
	}
}
void OnSelectedClear()
{
	if(World::instance().getBlockNum() > 0)
	{
		bool result = NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,L"����",L"�S���u���b�N���������Ă���낵���ł����H");
		if(result)
		{
			g_pEditManager()->allClear();
			g_pEditManager()->edited();
		}
	}
}
void OnSelectedNecessaryMaterial()
{
	NecessaryMaterialDialog nmd;
	nmd.show();
}
void OnSelectedOpenPicture()
{
	Platform::FileDialog::Filters filters;
	filters.add("*.png","�摜�t�@�C��-����(*.png)");
	filters.add("*.gif;*.jpg;*jpeg;*.jpe;*.jfif","�摜�t�@�C��-�񐄏�(*.gif;*.jpg;*jpeg;*.jpe;*.jfif)");
	Platform::FileDialog fd("�摜�t�@�C���̓ǂݍ���","",filters);
	if(fd.show_open())
	{
		g_pEditManager()->allClear();
			Operation::OpenPicture( fd.get_filename() );
		g_pEditManager()->setFilename("");
		g_pEditManager()->saved();
	}
}
void OnSelectedOpenCubeKingdom()
{
	Platform::FileDialog::Filters filters;
	filters.add("*.cko","�L���[�u�L���O�_���t�@�C��(*.cko)");
	Platform::FileDialog fd("�L���[�u�L���O�_���t�@�C�����J��","",filters);
	if(fd.show_open())
	{
		g_pEditManager()->allClear();
			Operation::OpenCubeKingdom( fd.get_filename() );
		g_pEditManager()->setFilename("");
		g_pEditManager()->saved();
	}
}
void OnSelectedOpenSchematic()
{
	Platform::FileDialog::Filters filters;
	filters.add("*.schematic","Schematic�t�@�C��(*.schematic)");
	Platform::FileDialog fd("Schematic�t�@�C�����J��","",filters);
	if(fd.show_open())
	{
		g_pEditManager()->allClear();
			Operation::OpenSchematic( fd.get_filename() );
		g_pEditManager()->setFilename("");
		g_pEditManager()->saved();
	}
}
void OnSelectedSaveSchematic()
{
	Platform::FileDialog::Filters filters;
	filters.add("*.schematic","Schematic�t�@�C��(*.schematic)");
	Platform::FileDialog fd("Schematic�t�@�C���Ƃ��ĕۑ�","����1",filters);
	if(fd.show_save())
	{
		Operation::SaveSchematic(fd.get_filename());
	}
}
void OnSelectedOpenSample(const std::string& filename)
{
	g_pEditManager()->allClear();
		Operation::OpenPlanFromArchive(filename);
	g_pEditManager()->setFilename("");
	g_pEditManager()->saved();
}
void OnSelectedModelImport()
{
	std::string name = Operation::getImportModelName();
	if(!name.empty())
	{
		Operation::ImportModel( name );
	}
}
void OnSelectedScreenShot()
{
	Platform::FileDialog::Filters filters;
	filters.add("*.png","PNG(*.png)");
	filters.add("*.jpg","JPEG(*.jpg)");
	Platform::FileDialog fd("�X�N���[���V���b�g�̕ۑ�","����1",filters);

	if(fd.show_save())
	{
		String filename = string_cast<String,std::string>( fd.get_filename() );
		auto extention = fd.get_extention();

		//select file format
		boost::scoped_ptr<ImageFileFormat> image_format;
		if(extention == ".png")
		{
			image_format.reset(new PNGImageFormat());
		}
		else if(extention == ".jpg")
		{
			image_format.reset(new JPEGImageFormat());
		}
		else
		{
			assert(0);
			return;
		}
		try{
			auto image = MakeSnapShot();
			File file(filename);
			if(file.exists())
			{
				file.deleteFile();
			}
			boost::scoped_ptr<FileOutputStream> stream( file.createOutputStream() );
			if(!stream)
			{
				throw std::exception();
			}
			if( !image_format->writeImageToStream(image,*stream) )
			{
				throw std::exception();
			}
		}catch(std::exception&){
			NativeMessageBox::showMessageBox(AlertWindow::WarningIcon,L"���s",L"�t�@�C���̏����o���Ɏ��s���܂����B");
		}
	}
}
void OnSelectedCreateShortCut()
{
	try{
		Platform::CreateDesktopShortCut();
	}catch(std::exception& e){
		std::stringstream ss;
		ss << "�V���[�g�J�b�g�̍쐬�Ɏ��s���܂���" << std::endl;
		ss << "�ڍ�:" << e.what();
		NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"���s",string_cast<String,std::string>(ss.str()));
		g_pLogManager()->post(e.what());
	}
}
void OnSelectedUpdateCheck()
{
	Net::UpdateCheck();
}
void OnSelectedCreateBox()
{
	Shape::BoxDesigner bd;
	if(bd.show())
	{
		g_pArrangementManager()->arrange(MinePlanner::Shape::CreateBox(bd.getxsize(),bd.getysize(),bd.getzsize(),bd.getBlockID()));
	}
}
void OnSelectedCreateSphere()
{
	UI::Shape::SphereDesigner sd;
	if(sd.show())
	{
		g_pArrangementManager()->arrange(MinePlanner::Shape::CreateSphere(sd.getDiameter(),sd.getBlockID()));
	}
}
void OnSelectedCreateCylinder()
{
	UI::Shape::CylinderDesigner cd;
	if(cd.show())
	{
		g_pArrangementManager()->arrange(MinePlanner::Shape::CreateSylinder(cd.getDiameter(),cd.getHeight(),cd.getBlockID()));
	}
}
void OnSelectedCreateCone()
{
	UI::Shape::ConeDesigner cd;
	if(cd.show())
	{
		g_pArrangementManager()->arrange(MinePlanner::Shape::CreateCone(cd.getDiameter(),cd.getHeight(),cd.getBlockID()));
	}
}

void OnSelectedVersionInfo()
{
	std::stringstream ss;
	ss << ApplicationConstant::NAME << " ver" << ApplicationConstant::VERSION << std::endl;
	ss << "Copyright(C)�@2011 ������. All rights reserved.";
	NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon,L"�o�[�W�������",string_cast<String,std::string>(ss.str()));
}

bool keyPressed(const juce::KeyPress& key)
{
	if(key.getKeyCode() == 'S')
	{
		if(key.getModifiers() == ModifierKeys::ctrlModifier)
		{
			OnSelectedSavePlan();
			return true;
		}
	}
	if(key.getKeyCode() == 'A')
	{
		if(key.getModifiers() == ModifierKeys::ctrlModifier)
		{
			g_pSelectionManager()->selectAll();
			return true;
		}
	}
	if(key.getKeyCode() == 'D')
	{
		if(key.getModifiers() == ModifierKeys::ctrlModifier)
		{
			g_pSelectionManager()->clearSelect();
			return true;
		}
	}

	const float MOV = 2.f;
	switch(key.getKeyCode())
	{
	case 'W':
		g_camera->moveBack(-MOV);
		break;
	case 'A':
		g_camera->moveRight(-MOV);
		break;
	case 'S':
		g_camera->moveBack(MOV);
		break;
	case 'D':
		g_camera->moveRight(MOV);
		break;
	}

	if(key.getKeyCode() == KeyPress::F1Key)
	{
		g_camera->setZAxisView();
	}
	else if(key.getKeyCode() == KeyPress::F2Key)
	{
		g_camera->setXAxisView();
	}
	else if(key.getKeyCode() == KeyPress::F3Key)
	{
		g_camera->setYAxisView();
	}

	RepaintOpenGL();
	return false;
}

namespace{
//�h���b�O�̂���
int mousePrevX = 0;
int mousePrevY = 0;
}
void mouseMove(const MouseEvent& e)
{
	mousePrevX = e.x;
	mousePrevY = e.y;
	g_pOperationManager()->mouseMove(e);
}
void mouseDown(const MouseEvent& e)
{
	g_pOperationManager()->mouseDown(e);
}
void mouseUp(const MouseEvent& e)
{
	g_pOperationManager()->mouseUp(e);
}
void mouseDrag(const MouseEvent& e)
{
	//�J��������
	const int dx = e.x - mousePrevX;
	const int dy = e.y - mousePrevY;

	if(e.mods.isMiddleButtonDown())
	{
		g_camera->mouseMiddleButtonDrag(dx,dy);
	}
	if(e.mods.isRightButtonDown())
	{
		g_camera->rotateX(-0.5f * dy);
		g_camera->rotateY(-0.5f * dx);
	}
	mousePrevX = e.x;
	mousePrevY = e.y;

	g_pOperationManager()->mouseDrag(e);
}
void mouseWheelMove(const MouseEvent &e, float wheelIncrementX, float wheelIncrementY)
{
	Util::Lerpf lerp(1.f,0.1f,500.f,100.f);

	float dis = g_camera->getDistance();
	g_camera->approach(wheelIncrementY * lerp(dis));
}
//�h���b�O���h���b�v�\�t�@�C�����X�g
static const boost::unordered_set<std::string> dropAbleExtentions = boost::assign::list_of<std::string>
	(".plan")
	(".boxel")
	(".png")
	(".gif")(".jpg")(".jpeg")(".jpe")(".jfif")
	(".cko")
	(".schematic")
	(".dxf")
	(".obj")
	(".off")
	(".wrl")
	(".ply")
	(".stl");
static const boost::unordered_set<std::string> pictureExtentions = boost::assign::list_of<std::string>
	(".png")
	(".gif")(".jpg")(".jpeg")(".jpe")(".jfif");

bool isInterestedInFileDrag(const StringArray &files)
{
	if(files.size() != 1)
	{
		return false;
	}

	std::string filename = string_cast<std::string,String>(files[0]);
	boost::filesystem::path file(filename);
	std::string extention = file.extension().string();
	if(dropAbleExtentions.find(extention) != dropAbleExtentions.end())
	{
		return true;
	}
	return false;
}

void filesDropped(const StringArray &files, int x, int y)
{
	std::string filename = string_cast<std::string,String>(files[0]);
	boost::filesystem::path file(filename);
	std::string extention = file.extension().string();

	if(extention == ".plan")
	{
		boost::function<void(std::string)> open_func;
		if(Operation::isEnablePlanFile(filename))
		{
			open_func = Operation::OpenPlan;
		}
		else if(Operation::isEnableOldPlanFile(filename))
		{
			open_func = Operation::OpenOldPlan;
		}
		else
		{
			NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"�G���[",L"�t�@�C���`�����s���ł��B");
			return;
		}

		g_pEditManager()->allClear();

		open_func( filename );

		g_pEditManager()->setFilename( filename );
		g_pEditManager()->saved();
	}
	else if(pictureExtentions.find(extention) != pictureExtentions.end())
	{
		g_pEditManager()->allClear();
			Operation::OpenPicture( filename );
		g_pEditManager()->setFilename("");
		g_pEditManager()->saved();
	}
	else if(extention == ".cko")
	{
		g_pEditManager()->allClear();
			Operation::OpenCubeKingdom( filename );
		g_pEditManager()->setFilename("");
		g_pEditManager()->saved();
	}
	else if(extention == ".schematic")
	{
		g_pEditManager()->allClear();
			Operation::OpenSchematic( filename );
		g_pEditManager()->setFilename("");
		g_pEditManager()->saved();
	}
	else
	{
		Operation::ImportModel( filename );
	}

	RepaintOpenGL();
}

//false �Ȃ�L�����Z�� true�Ȃ�I��
bool OnApplicationExit()
{
	if(!g_pEditManager()->isSaved())
	{
		//�ۑ�����Ă��Ȃ�
		int result = NativeMessageBox::showYesNoCancelBox(AlertWindow ::WarningIcon,L"����",
			L"�ҏW���̃t�@�C���͕ۑ�����Ă��܂���B\n�ۑ����ďI�����܂����H");

		if(result == 0)
		{
			//�L�����Z��
			return false;
		}
		else if(result == 1)
		{
			//�͂�
			OnSelectedSavePlan();
		}
		else
		{
			//������
		}
	}
	else
	{
		//�ۑ�����Ă�
	}

	g_pArrangementManager()->arrangeFinish();
	return true;
}
}//EventHandler
}//UI
}//MinePlanner