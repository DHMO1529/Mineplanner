#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GlU32.Lib")

#include "MinePlanner/main.hpp"

#include "Util/setupLocale.hpp"

#include "MinePlanner/Log/LogManager.hpp"

#include "MinePlanner/DataBase/DataBase.hpp"
#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/Operation/Manager.hpp"
#include "MinePlanner/PathSetup.hpp"
namespace MinePlanner{
void initialize()
{
	//_CrtSetBreakAlloc(70611);

	//�A�v���P�[�V�����������R�[�h
	Util::setupLocale();

	PathSetup();

	Log::LogManager::Create();

	DataBase::Init();
		g_pLogManager()->post("�f�[�^�x�[�X�}�l�[�W������������");
	Operation::Manager::Create();
}
void finalize()
{
	Operation::Manager::Destory();
	DataBase::Fin();
		g_pLogManager()->post("�f�[�^�x�[�X�}�l�[�W���I��");

		g_pLogManager()->post("�A�v���P�[�V�����I��");
	Log::LogManager::Destory();
}
}//MinePlanner
