#include "Platform/FileDialog.hpp"
#include <Windows.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
namespace Platform{
//�t�B���^�[
FileDialog::Filter::Filter(const char* ext,const char* disc)
	:extention(ext),discliption(disc){}
std::string FileDialog::Filter::getExtention()const
{
	return extention;
}
std::string FileDialog::Filter::getDiscliption()const
{
	return discliption;
}

//�t�B���^�['s
FileDialog::Filters::Filters():m_filters(){}
void FileDialog::Filters::add(const char* ext,const char* disc)
{
	m_filters.push_back(FileDialog::Filter(ext,disc));
}
std::vector<char> FileDialog::Filters::getFilter()const
{
	using namespace boost::assign;

	std::vector<char> filter_data;
	BOOST_FOREACH(const Filter& filter,m_filters)
	{
		auto dics = filter.getDiscliption();
		auto ext = filter.getExtention();

		/* �t�@�C������\0*�g���q */
		BOOST_FOREACH(char c,dics)
		{
			filter_data.push_back(c);
		}
		filter_data += '\0';
		BOOST_FOREACH(char c,ext)
		{
			filter_data.push_back(c);
		}
		filter_data += '\0';
	}
	filter_data += '\0','\0';
	return filter_data;
}
int FileDialog::Filters::count()const
{
	return m_filters.size();
}
std::string FileDialog::Filters::getExtention(int n)const
{
	return m_filters[n].getExtention();
}

//�_�C�A���O
FileDialog::FileDialog(const char* title,const char* default_name,const Filters& filters)
	:m_title(title? title : "")
	,m_default_name(default_name? default_name : "")
	,m_filters(filters)
	,m_result()
{
}
bool FileDialog::show_open()
{
	bool is_selected_ok = false;
	{
		char filename_full[256] = "";
		strcpy(filename_full,m_default_name.c_str());
		auto filter = m_filters.getFilter();
		
		OPENFILENAMEA ofn = {0};
		ofn.lStructSize = sizeof(OPENFILENAMEA);//�\���̃T�C�Y
		ofn.hwndOwner = GetActiveWindow();//�E�B���h�E�n���h��
		ofn.lpstrFilter = &filter[0];//�t�B���^
		ofn.lpstrFile = filename_full;//�t�@�C�����t��
		ofn.nMaxFile = sizeof(filename_full);//�t�@�C�����t�� �T�C�Y
		ofn.lpstrFileTitle = nullptr;//�t�@�C����
		ofn.nMaxFileTitle = 0;//�t�@�C�����̃T�C�Y
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		ofn.lpstrTitle = m_title.c_str();

		if(GetOpenFileNameA(&ofn))
		{
			m_result = filename_full;
			is_selected_ok = true;
		}
	}
	return is_selected_ok;
}
bool FileDialog::show_save()
{
	bool is_selected_ok = false;
	{
		char filename_full[256] = "";
		strcpy(filename_full,m_default_name.c_str());
		auto filter = m_filters.getFilter();

		OPENFILENAMEA ofn = {0};
		ofn.lStructSize = sizeof(OPENFILENAMEA);//�\���̃T�C�Y
		ofn.hwndOwner = GetActiveWindow();//�E�B���h�E�n���h��
		ofn.lpstrFilter = &filter[0];//�t�B���^
		ofn.lpstrFile = filename_full;//�t�@�C�����t��
		ofn.nMaxFile = sizeof(filename_full);//�t�@�C�����t�� �T�C�Y
		ofn.lpstrFileTitle = nullptr;//�t�@�C����
		ofn.nMaxFileTitle = 0;//�t�@�C���� �T�C�Y
		ofn.Flags = OFN_NOCHANGEDIR;
		ofn.lpstrTitle = m_title.c_str();

		if(GetSaveFileNameA(&ofn))
		{
			m_result = filename_full;
			
			if(m_filters.count() > 0)
			{
				auto selected_extention = m_filters.getExtention(ofn.nFilterIndex-1);
				boost::filesystem::path path(m_result);
				if(path.extension().string() != selected_extention)
				{
					path.replace_extension(selected_extention);
					m_result = path.string();
				}
			}
			is_selected_ok = true;
		}
	}
	return is_selected_ok;
}
std::string FileDialog::get_filename()const
{
	return m_result;
}
std::string FileDialog::get_extention()const
{
	boost::filesystem::path path(m_result);
	return path.extension().string();
}
}//Platform
