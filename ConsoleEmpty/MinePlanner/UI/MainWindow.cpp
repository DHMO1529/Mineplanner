#include "MinePlanner/UI/MainWindow.hpp"

#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/UI/MainComponent.hpp"
#include "MinePlanner/UI/EventHandler/Functions.hpp"
#include "MinePlanner/string_cast.hpp"

namespace MinePlanner{
namespace UI{
static MainWindow* global_instance = 0;

void setWindowTitle(const std::string& title)
{
	if(global_instance)
	{
		global_instance->setName(string_cast<String,std::string>(title));
	}
}
int getWindowX()
{
	if(global_instance)
	{
		return global_instance->getX();
	}
	return 0;
}
int getWindowY()
{
	if(global_instance)
	{
		return global_instance->getY();
	}
	return 0;
}
void updateMenuBar()
{
	if(global_instance)
	{
		global_instance->updateMenuBar();
	}
}
DocumentWindow* getMainWindow()
{
	return global_instance;
}

//main window class
MainWindow::MainWindow():
 DocumentWindow(string_cast<String,std::string>(ApplicationConstant::NAME),Colours::lightgrey,DocumentWindow::allButtons)
{
  this->setResizable(true,false); // resizability is a property of ResizableWindow
  this->setResizeLimits(400,300,8192,8192);
	this->setMenuBar(&m_menu);
	this->setVisible(true);
	this->addKeyListener(this);

	global_instance = this;
	this->setContentOwned(new MainComponent(),true);
	this->centreWithSize(getWidth(),getHeight());
}
MainWindow::~MainWindow()
{
	this->setMenuBar(0);

	global_instance = 0;
}
void MainWindow::closeButtonPressed()
{
	if(EventHandler::OnApplicationExit())
	{
		JUCEApplication::quit();
	}
}
bool MainWindow::keyPressed(const juce::KeyPress& key,juce::Component*)
{
	return EventHandler::keyPressed(key);
}
void MainWindow::updateMenuBar()
{
	m_menu.menuItemsChanged();
}
}//UI
}//MinePlanner
