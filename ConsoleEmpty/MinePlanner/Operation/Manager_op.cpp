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
		g_pLogManager()->post("��{�ҏW�V�X�e������������");
	ArrangementManager::Create();
		g_pLogManager()->post("�z�u�}�l�[�W������������");
	EditManager::Create();
		g_pLogManager()->post("�ҏW�}�l�[�W������������");
	ClipBoard::Create();
		g_pLogManager()->post("�N���b�v�{�[�h�V�X�e������������");
	SelectionManager::Create();
		g_pLogManager()->post("�I���}�l�[�W������������");
	HideBuffer::Create();
		g_pLogManager()->post("�u���b�N�B���V�X�e������������");
}
Manager::~Manager()
{
	HideBuffer::Destory();
		g_pLogManager()->post("�u���b�N�B���V�X�e���I��");
	SelectionManager::Destory();
		g_pLogManager()->post("�I���}�l�[�W���I��");
	ClipBoard::Destory();
		g_pLogManager()->post("�N���b�v�{�[�h�V�X�e���I��");
	EditManager::Destory();
		g_pLogManager()->post("�z�u�}�l�[�W���I��");
	ArrangementManager::Destory();
		g_pLogManager()->post("�z�u�}�l�[�W���I��");
	BasicEditor::Destory();
		g_pLogManager()->post("��{�ҏW�V�X�e���I��");
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