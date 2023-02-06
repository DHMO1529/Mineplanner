#ifndef MINEPLANNER__FUNCTIONS
#define MINEPLANNER_GRAPHIC_FUNCTIONS
#include <string>
#include <juce.h>
namespace MinePlanner{
namespace UI{
namespace EventHandler{

void OnSelectedNew();
void OnSelectedOpenPlan();
void OnSelectedSavePlan();
void OnSelectedSaveAsPlan();
void OnSelectedClear();
void OnSelectedNecessaryMaterial();
void OnSelectedOpenPicture();
void OnSelectedOpenCubeKingdom();
void OnSelectedOpenSchematic();
void OnSelectedSaveSchematic();
void OnSelectedOpenSample(const std::string& filename);
void OnSelectedModelImport();
void OnSelectedScreenShot();
void OnSelectedCreateShortCut();
void OnSelectedUpdateCheck();
void OnSelectedCreateBox();
void OnSelectedCreateSphere();
void OnSelectedCreateCylinder();
void OnSelectedCreateCone();

void OnSelectedVersionInfo();

//���C���E�B���h�E
bool keyPressed(const juce::KeyPress& key);

//OpenGL�X�N���[��
void mouseMove(const MouseEvent& e);
void mouseDown(const MouseEvent& e);
void mouseUp(const MouseEvent &e);
void mouseDrag(const MouseEvent& e);
void mouseWheelMove(const MouseEvent &e, float wheelIncrementX, float wheelIncrementY);

//�t�@�C���h���b�v
void filesDropped(const StringArray &files, int x, int y);
bool isInterestedInFileDrag(const StringArray &files);

//false �Ȃ�L�����Z�� true�Ȃ�I��
bool OnApplicationExit();
}//EventHandler
}//UI
}//MinePlanner
#endif