#include "MinePlanner/UI/EventHandler/ImportModel.hpp"

#include <stdlib.h>
#include <sstream>
#include <juce.h>
#include <boost/filesystem.hpp>
#include <boost/scope_exit.hpp>
#include <boost/foreach.hpp>

#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/Log/LogManager.hpp"

#include "MinePlanner/Operation/EditManager.hpp"
#include "MinePlanner/Operation/BinvoxToBlocks.hpp"
#include "MinePlanner/Operation/BatchWork.hpp"
#include "MinePlanner/UI/ModelImportDialog.hpp"
namespace MinePlanner{
namespace Operation{
std::string getImportModelName()
{
	FileChooser chooser(L"�R�c���f���t�@�C�����J��",File::nonexistent,"*.dxf;*.obj;*.off;*.wrl;*.ply;*.stl");

	if(!chooser.browseForFileToOpen())
	{
		return "";
	}
	File choosedFile = chooser.getResult();
	std::string filename = string_cast<std::string,String>(choosedFile.getFullPathName());
	return filename;
}
void ImportModel(const std::string& filename)
{
	if(filename.empty())
	{
		return;
	}
	UI::ModelImportDialog mid(filename);
	mid.show();
	if(!mid.isDecided())
	{
		return;
	}
	int size = mid.getSize();

	try{
		std::vector<std::string> temporaryFiles;
		BOOST_SCOPE_EXIT( (&temporaryFiles) )
		{
			BOOST_FOREACH(const std::string& file,temporaryFiles)
			{
				if(boost::filesystem::exists(file))
				{
					boost::filesystem::remove(file);
				}
			}
		}
		BOOST_SCOPE_EXIT_END

		boost::filesystem::path src(filename);
		std::string temporary = std::string("tool\\temporary") + src.extension().string();
		boost::filesystem::path dst(temporary);

		//���炩���ߑ|��
		if(boost::filesystem::exists(dst))
		{
			boost::filesystem::remove(dst);
		}

		//��ƃR�s�[
		boost::filesystem::copy_file(src,dst);
		temporaryFiles.push_back(temporary);
		
		//���炩���ߑ|��
		if(boost::filesystem::exists("tool\\temporary.binvox"))
		{
			boost::filesystem::remove("tool\\temporary.binvox");
		}

		std::stringstream arg;
		arg << "tool\\binvox.exe ";
		arg << temporary;
		arg << " -d " << size;
		std::system(arg.str().c_str()); // ���s

		//���ʂ��`�F�b�N
		if(boost::filesystem::exists("tool\\temporary.binvox"))
		{
			temporaryFiles.push_back("tool\\temporary.binvox");
		}
		else
		{
			NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"���s",
				L"�ǂݍ��݂Ɏ��s���܂����B\n�R�c���f���t�@�C�����s���ł��邩�A�o�O�̉\��������܂��B");
			throw std::exception("�ϊ��Ɏ��s");
		}

		BlockSet blockSet = BinvoxToBlocks("tool\\temporary.binvox");

		g_pEditManager()->allClear();
		Work::ptr work = BatchWork::createBatchAdd(blockSet);
		work->exe();

		g_pEditManager()->setFilename("");
		g_pEditManager()->edited();
	}catch(std::exception& e){
		g_pLogManager()->post(e.what());
		return;
	}
}
}//Operation
}//MinePlanner
