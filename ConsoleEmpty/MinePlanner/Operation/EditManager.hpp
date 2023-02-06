#ifndef MINEPLANNER_OPERATION_EDITMANAGER
#define MINEPLANNER_OPERATION_EDITMANAGER
#include <string>
#include "Util/Singleton.hpp"
#include "MinePlanner/Operation/UnRedoSystem.hpp"

namespace MinePlanner{
namespace Operation{
class EditManager : public Util::Singleton<EditManager>
{
public:
	EditManager();
	~EditManager();

	//作業をここに送信すれば自動的にアンドゥをサポート
	void dowork(Operation::Work::ptr work);
	void undo();
	void redo();

	void saved();
	void edited();
	bool isSaved()const;
	void setFilename(const std::string filename);
	std::string getFilename()const;
	void updateTitleBar()const;

	//redo,undo,worldをクリア　ファイル名はそのまま
	void allClear();
private:
	UnRedoSystem::ptr m_unredo;

	bool m_isEdited;
	std::string m_filename;
};
}//Operation
}//MinePlanner
inline MinePlanner::Operation::EditManager* g_pEditManager()
{
	return MinePlanner::Operation::EditManager::pInstance();
}
#endif