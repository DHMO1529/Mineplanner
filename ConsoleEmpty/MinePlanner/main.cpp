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

	//アプリケーション初期化コード
	Util::setupLocale();

	PathSetup();

	Log::LogManager::Create();

	DataBase::Init();
		g_pLogManager()->post("データベースマネージャ初期化完了");
	Operation::Manager::Create();
}
void finalize()
{
	Operation::Manager::Destory();
	DataBase::Fin();
		g_pLogManager()->post("データベースマネージャ終了");

		g_pLogManager()->post("アプリケーション終了");
	Log::LogManager::Destory();
}
}//MinePlanner
