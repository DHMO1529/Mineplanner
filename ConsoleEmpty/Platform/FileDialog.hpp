#ifndef PLATFORM_FILEDIALOG_HPP
#define PLATFORM_FILEDIALOG_HPP
#include <string>
#include <vector>
namespace Platform{
/**
* 現在はwin用
* 保存、開くダイアログを表示する
*/
class FileDialog
{
public:
	/**
	* フィルター情報
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
	* フィルター情報's ユーザーはこちらを使うべし
	*/
	class Filters{
	public:
		Filters();
		/**
		* フィルターを追加
		* @param ext 拡張子
		* @param disc 説明
		* 
		* ex) Filters filters; filters.add("*.png;*.jpg","画像ファイル{*.png;*.jpg}");
		*/
		void add(const char* ext,const char* disc);

		/**
		* フィルターの数を取得する
		* @return フィルターの数
		*/
		int count()const;

		/**
		* ユーザーは使用しない　フィルタ文字列を取得する
		* @return フィルタ文字列
		*/
		std::vector<char> getFilter()const;

		/**
		* ユーザーは使用しない　拡張子を取得する
		* @param n 配列の0から始まるインデックス
		* @return 拡張子
		*/
		std::string getExtention(int n)const;
	private:
		std::vector<FileDialog::Filter> m_filters;
	};

	/**
	* コンストラクタ
	* @param title タイトルバー
	* @param default_name 最初に出るファイル名
	* @param filters ファイルのフィルター
	*/
	FileDialog(const char* title,const char* default_name,const Filters& filters);

	/**
	* 開くダイアログを表示
	*/
	bool show_open();

	/**
	* 保存ダイアログを表示
	*/
	bool show_save();

	/**
	* 選択されたファイルの絶対パスを取得する
	*/
	std::string get_filename()const;

	/**
	* 選択されたファイルの拡張子を取得する
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