#include "MinePlanner/Operation/Manager.hpp"

#include "MinePlanner/Log/LogManager.hpp"

#include "MinePlanner/Operation/ArrangementManager.hpp"
#include "MinePlanner/Operation/EditManager.hpp"
#include "MinePlanner/Operation/ClipBoard.hpp"
#include "MinePlanner/Operation/BasicEditor.hpp"
#include "MinePlanner/Operation/SelectionManager.hpp"
#include "MinePlanner/Operation/HideBuffer.hpp"

#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"
namespace MinePlanner{
namespace Operation{
Manager::Manager()
{
	BasicEditor::Create(); 
		g_pLogManager()->post("基本編集システム初期化完了");
	ArrangementManager::Create();
		g_pLogManager()->post("配置マネージャ初期化完了");
	EditManager::Create();
		g_pLogManager()->post("編集マネージャ初期化完了");
	ClipBoard::Create();
		g_pLogManager()->post("クリップボードシステム初期化完了");
	SelectionManager::Create();
		g_pLogManager()->post("選択マネージャ初期化完了");
	HideBuffer::Create();
		g_pLogManager()->post("ブロック隠蔽システム初期化完了");
}
Manager::~Manager()
{
	HideBuffer::Destory();
		g_pLogManager()->post("ブロック隠蔽システム終了");
	SelectionManager::Destory();
		g_pLogManager()->post("選択マネージャ終了");
	ClipBoard::Destory();
		g_pLogManager()->post("クリップボードシステム終了");
	EditManager::Destory();
		g_pLogManager()->post("配置マネージャ終了");
	ArrangementManager::Destory();
		g_pLogManager()->post("配置マネージャ終了");
	BasicEditor::Destory();
		g_pLogManager()->post("基本編集システム終了");
}
void Manager::draw()const
{
	if(g_config->getMode() == MODE_EDIT)
	{
		g_pArrangementManager()->draw();

		if(g_config->getSubMode() == SUBMODE_SELECT)
		{
			g_pSelectionManager()->draw();
		}
		else
		{
			g_pBasicEditor()->draw();
		}
	}
}
void Manager::mouseMove(const MouseEvent& e)
{
	if(g_config->getMode() == MODE_EDIT)
	{
		if(g_config->getSubMode() == SUBMODE_SELECT)
		{

		}
		else
		{
			g_pBasicEditor()->mouseMove(e);
		}
	}
}
void Manager::mouseDown(const MouseEvent& e)
{
	if(g_config->getMode() == MODE_EDIT)
	{
		if(g_config->getSubMode() == SUBMODE_SELECT)
		{
			g_pSelectionManager()->mouseDown(e);
		}
		else
		{
			g_pBasicEditor()->mouseDown(e);
		}
	}
}
void Manager::mouseDrag(const MouseEvent& e)
{
	if(g_config->getMode() == MODE_EDIT)
	{
		if(g_config->getSubMode() == SUBMODE_SELECT)
		{
			g_pSelectionManager()->mouseDrag(e);
		}
		else
		{
			g_pBasicEditor()->mouseDrag(e);
		}
	}
}
void Manager::mouseUp(const MouseEvent& e)
{
	if(g_config->getMode() == MODE_EDIT)
	{
		if(g_config->getSubMode() == SUBMODE_SELECT)
		{
			g_pSelectionManager()->mouseUp(e);
		}
		else
		{
		}
	}
}
}//Operation
}//MinePlanner