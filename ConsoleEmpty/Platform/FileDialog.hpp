#ifndef PLATFORM_FILEDIALOG_HPP
#define PLATFORM_FILEDIALOG_HPP
#include <string>
#include <vector>
namespace Platform{
/**
* ���݂�win�p
* �ۑ��A�J���_�C�A���O��\������
*/
class FileDialog
{
public:
	/**
	* �t�B���^�[���
	*/
	class Filter{
	public:
		Filter(const char* ext,const char* disc);
		std::string getExtention()const;
		std::string getDiscliption()const;
	private:
		std::string extention;
		std::string discliption;
	};
	/**
	* �t�B���^�[���'s ���[�U�[�͂�������g���ׂ�
	*/
	class Filters{
	public:
		Filters();
		/**
		* �t�B���^�[��ǉ�
		* @param ext �g���q
		* @param disc ����
		* 
		* ex) Filters filters; filters.add("*.png;*.jpg","�摜�t�@�C��{*.png;*.jpg}");
		*/
		void add(const char* ext,const char* disc);

		/**
		* �t�B���^�[�̐����擾����
		* @return �t�B���^�[�̐�
		*/
		int count()const;

		/**
		* ���[�U�[�͎g�p���Ȃ��@�t�B���^��������擾����
		* @return �t�B���^������
		*/
		std::vector<char> getFilter()const;

		/**
		* ���[�U�[�͎g�p���Ȃ��@�g���q���擾����
		* @param n �z���0����n�܂�C���f�b�N�X
		* @return �g���q
		*/
		std::string getExtention(int n)const;
	private:
		std::vector<FileDialog::Filter> m_filters;
	};

	/**
	* �R���X�g���N�^
	* @param title �^�C�g���o�[
	* @param default_name �ŏ��ɏo��t�@�C����
	* @param filters �t�@�C���̃t�B���^�[
	*/
	FileDialog(const char* title,const char* default_name,const Filters& filters);

	/**
	* �J���_�C�A���O��\��
	*/
	bool show_open();

	/**
	* �ۑ��_�C�A���O��\��
	*/
	bool show_save();

	/**
	* �I�����ꂽ�t�@�C���̐�΃p�X���擾����
	*/
	std::string get_filename()const;

	/**
	* �I�����ꂽ�t�@�C���̊g���q���擾����
	*/
	std::string get_extention()const;
private:
	std::string m_title;
	std::string m_default_name;
	Filters m_filters;
	std::string m_result;
};
}//Platform
#endif