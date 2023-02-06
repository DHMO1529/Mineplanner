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
	throw std::exception("バージョンの抽出に失敗");
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

	throw std::exception("ダウンロードURLの抽出に失敗");
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
				L"新バージョンが見つかりました。\nダウンロードにいきますか？");
			if(result)
			{
				URL urlopen(string_cast<String,std::string>(url));
				urlopen.launchInDefaultBrowser();
			}
		}
		else
		{
			NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon,L"",L"現在のバージョンが最新です。");
		}
	}
	catch(std::exception& e)
	{
		std::stringstream ss;
		ss << "アップデートチェックに失敗しました。" << std::endl;
		ss << "エラー内容:" << e.what();
		String message = string_cast<String,std::string>(ss.str());
		NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"エラー",message);
	}
}
}//Net
}//MinePlanner
