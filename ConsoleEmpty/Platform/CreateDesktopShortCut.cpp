#include "Platform/CreateDesktopShortCut.hpp"

#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/ApplicationConstant.hpp"

#include <exception>
#include <stdexcept>
#include <string>
#include <boost/signals2.hpp>

#include <windows.h>
#include <shlobj.h>
#include <juce.h>
namespace Platform{
void CreateDesktopShortCut()
{
	if(FAILED(CoInitialize(NULL)))
	{
		throw std::runtime_error("CoInitialize()");
	}
	boost::signals2::signal<void(void)> release_signal;
	release_signal.connect( CoUninitialize ,boost::signals2::at_front);

	IShellLinkW* shell_link = nullptr;
	if(FAILED( CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,IID_IShellLinkW,(void **)&shell_link) ))
	{
		release_signal();
		throw std::runtime_error("CoCreateInstance()");
	}
	release_signal.connect([&shell_link](){shell_link->Release(); shell_link = nullptr;}, boost::signals2::at_front);

	IPersistFile* persist_file = nullptr;
	if(FAILED( shell_link->QueryInterface(IID_IPersistFile,(void **)&persist_file) ))
	{
		release_signal();
		throw std::runtime_error("IShellLinkW::QueryInterface()");
	}
	release_signal.connect([&persist_file](){persist_file->Release(); persist_file = nullptr;}, boost::signals2::at_front);

	auto desktop_path = std::wstring( 
		File::getSpecialLocation(File::userDesktopDirectory)
		 .getFullPathName()
		 .toUTF16());

	auto shortcut_name = MinePlanner::string_cast<std::wstring,std::string>(MinePlanner::ApplicationConstant::VERSION);
	shortcut_name = L"マインプランナーver" + shortcut_name + L"(ｼｮｰﾄｶｯﾄ).lnk";

	auto shortcut_path = 
		desktop_path + L"\\" + shortcut_name;

	auto app_full_name = std::wstring( 
		File::getSpecialLocation(File::currentApplicationFile)
		 .getFullPathName()
		 .toUTF16() );

	auto app_working_path = std::wstring(
		File::getSpecialLocation(File::currentApplicationFile)
		 .getParentDirectory()
		 .getFullPathName()
		 .toUTF16() );
	
	if(FAILED( shell_link->SetPath(app_full_name.c_str()) ))
	{
		release_signal();
		throw std::runtime_error("IShellLinkW::SetPath()");
	}
	if(FAILED( shell_link->SetWorkingDirectory(app_working_path.c_str()) ))
	{
		release_signal();
		throw std::runtime_error("IShellLinkW::SetWorkingDirectory()");
	}
	if(FAILED( persist_file->Save(shortcut_path.c_str(),FALSE) ))
	{
		release_signal();
		throw std::runtime_error("IPersistFile::Save()");
	}

	release_signal();
}
}//Platform
