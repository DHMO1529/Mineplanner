#ifndef MINEPLANNER_UI_WINDOW
#define MINEPLANNER_UI_WINDOW
#include <string>
#include <juce.h>
#include "MinePlanner/UI/MyMenuBar.hpp"
namespace MinePlanner{
namespace UI{
/**
* �E�B���h�E�̃^�C�g���o�[�̕������ݒ�
* @param title �^�C�g���o�[�̕�����
*/
void setWindowTitle(const std::string& title);
int getWindowX();
int getWindowY();
void updateMenuBar();
DocumentWindow* getMainWindow();

//main window class
class MainWindow 
	: public DocumentWindow,
		public KeyListener
{
public:
	MainWindow();
	~MainWindow();
	virtual void closeButtonPressed();
	virtual bool keyPressed(const juce::KeyPress& key,juce::Component*);
	void updateMenuBar();
private:
	MyMenuBar m_menu;
	TooltipWindow m_tooltipWindow;//for tooltip
};
}//UI
}//MinePlanner
#endif