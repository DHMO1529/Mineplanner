#include <juce.h>
#include <boost/scoped_ptr.hpp>

#include "MinePlanner/UI/MainWindow.hpp"
#include "MinePlanner/main.hpp"
#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/UI/MyLookAndFeel.hpp"
#include "MinePlanner/string_cast.hpp"

class Application : public JUCEApplication
{
public:
	Application():
	 m_mainWindow()
	,m_myLookAndFeel()
	{
	}
	~Application()
	{
	}
	virtual void initialise(const String& commandLineParameters)
	{
		LookAndFeel::setDefaultLookAndFeel(&m_myLookAndFeel);
		MinePlanner::initialize();
		m_mainWindow.reset(new MinePlanner::UI::MainWindow());
	}
	virtual void shutdown()
	{
		MinePlanner::finalize();
	}
	virtual const String getApplicationName()
	{
		return MinePlanner::string_cast<String,std::string>(MinePlanner::ApplicationConstant::NAME + " ver" + MinePlanner::ApplicationConstant::VERSION);
	}
  virtual const String getApplicationVersion()
  {
    return MinePlanner::ApplicationConstant::VERSION.c_str();
	}
  virtual bool moreThanOneInstanceAllowed()
  {
    return true;//多重起動可能
  }
  virtual void anotherInstanceStarted(const String& commandLine)
	{
		//ユーザーが他のプログラムを起動しようとしたときに呼ばれる
  }
private:
	boost::scoped_ptr<MinePlanner::UI::MainWindow> m_mainWindow;
	MinePlanner::UI::MyLookAndFeel m_myLookAndFeel;
};

START_JUCE_APPLICATION(Application)
