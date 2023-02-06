#include "MinePlanner/graphic/Rendering.hpp"

#include "MinePlanner/graphic/gl.hpp"
#include "MinePlanner/graphic/FpsCount.hpp"

#include "MinePlanner/graphic/Camera.hpp"
#include "MinePlanner/graphic/DrawXYZAxis.hpp"
#include "MinePlanner/graphic/DrawLookAt.hpp"
#include "MinePlanner/graphic/DrawGrid.hpp"
#include "MinePlanner/graphic/DrawFullBlocks.hpp"
#include "MinePlanner/graphic/DrawSliceBlocks.hpp"
#include "MinePlanner/graphic/DrawBlocksInEdit.hpp"
#include "MinePlanner/graphic/DrawXYZIcon.hpp"

#include "MinePlanner/GlobalConfig.hpp"
#include "MinePlanner/GlobalConfigEnumDef.hpp"

#include "MinePlanner/Operation/Manager.hpp"
#include "MinePlanner/Operation/SelectionManager.hpp"

#include "MinePlanner/graphic/DrawBlock.hpp"
namespace MinePlanner{
namespace graphic{
void Rendering()
{
	FpsCount();

	//�s��̐ݒ�
	g_camera->updateInternalMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glm::mat4x4 proj = g_camera->getProjMatrix();
	glLoadMatrixf(&proj[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glm::mat4x4 view = g_camera->getViewMatrix();
	glLoadMatrixf(&view[0][0]);

	glClearColor(0.15f,0.15f,0.15f,1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.f,1.f,1.f);

	//�R��
	DrawXYZAxis();

	//���C���`��
	if(g_config->getMode() == MODE_EDIT)
	{
		DrawBlocksInEdit();
	}
	else
	{
		if(g_config->getSliceModeEnable())
		{
			DrawSliceBlocks();
		}
		else
		{
			DrawFullBlocks();
		}
	}

	//�O���b�h
	int h = 0;
	if(g_config->getMode() == MODE_VIEW)
	{
		h = g_config->getSliceHeight();
	}
	else
	{
		h = g_config->getEditGridHeight();
	}
	DrawGrid(100,h);

	g_pOperationManager()->draw();

	DrawLookAt();

	DrawXYZIcon();
}
}//graphic
}//MinePlanner
