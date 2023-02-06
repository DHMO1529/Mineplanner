#include "MinePlanner/Net/UpdateCheck.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <clx/http.h>
#include <clx/uri.h>

#include <juce.h>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace Net{
inline std::string ExtractLastestVersion(const std::string& body)
{
	boost::regex regex("LastestVersion=\"([0-9.]*)\"");
	boost::smatch result;

	if(boost::regex_search(body,result,regex))
	{
		return result[1];
	}
	throw std::exception("�o�[�W�����̒��o�Ɏ��s");
	return std::string();
}
inline std::string ExtractUrl(const std::string& body)
{
	boost::regex regex("DownloadURL=\"([^\n]*)\"");
	boost::smatch result;

	if(boost::regex_search(body,result,regex))
	{
		return result[1];
	}

	throw std::exception("�_�E�����[�hURL�̒��o�Ɏ��s");
	return std::string();
}
void UpdateCheck()
{
	try{
		clx::http session(clx::uri::encode("minedesign3d.miraiserver.com"),80);
		session.get("/MinePlanner.html");
	
		const std::string body = session.body();

		const std::string lastestVersion = ExtractLastestVersion(body);
		const std::string url = ExtractUrl(body);

		const float lastestVersionValue = boost::lexical_cast<float,std::string>(lastestVersion);
		const float thisVersionValue = boost::lexical_cast<float,std::string>(ApplicationConstant::VERSION);

		if(lastestVersionValue > thisVersionValue)
		{
			bool result = NativeMessageBox::showOkCancelBox(AlertWindow::InfoIcon,L"",
				L"�V�o�[�W������������܂����B\n�_�E�����[�h�ɂ����܂����H");
			if(result)
			{
				URL urlopen(string_cast<String,std::string>(url));
				urlopen.launchInDefaultBrowser();
			}
		}
		else
		{
			NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon,L"",L"���݂̃o�[�W�������ŐV�ł��B");
		}
	}
	catch(std::exception& e)
	{
		std::stringstream ss;
		ss << "�A�b�v�f�[�g�`�F�b�N�Ɏ��s���܂����B" << std::endl;
		ss << "�G���[���e:" << e.what();
		String message = string_cast<String,std::string>(ss.str());
		NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"�G���[",message);
	}
}
}//Net
}//MinePlanner
