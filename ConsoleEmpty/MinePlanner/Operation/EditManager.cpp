#include "MinePlanner/Operation/EditManager.hpp"

#include <sstream>
#include <boost/filesystem.hpp>

#include "MinePlanner/World.hpp"
#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/UI/MainWindow.hpp"

namespace MinePlanner{
namespace Operation{
EditManager::EditManager():
 m_unredo()
,m_isEdited(false)
,m_filename()
{
	m_unredo = UnRedoSystem::create();
}
EditManager::~EditManager()
{
}
void EditManager::undo()
{
	m_unredo->undo();
	edited();
}
void EditManager::redo()
{
	m_unredo->redo();
	edited();
}
void EditManager::dowork(Operation::Work::ptr work)
{
	if(!work)
	{
		assert(0);
	}
	m_unredo->execute(work);
	edited();
}
void EditManager::saved()
{
	m_isEdited = false;
	updateTitleBar();
}
void EditManager::edited()
{
	m_isEdited = true;
	updateTitleBar();
}
bool EditManager::isSaved()const
{
	return !m_isEdited;
}
void EditManager::setFilename(const std::string filename)
{
	m_filename = filename;
	updateTitleBar();
}
std::string EditManager::getFilename()const
{
	return m_filename;
}
void EditManager::updateTitleBar()const
{
	std::stringstream ss;
	if(m_filename.empty())
	{
		ss << "–³‘è";
	}
	else
	{
		boost::filesystem::path path(m_filename);
		std::string name = path.filename().string();
		ss << name;
	}
	if(!isSaved())
	{
		ss << "*";
	}
	ss << " - " << ApplicationConstant::NAME;

	UI::setWindowTitle(ss.str());
}
void EditManager::allClear()
{
	m_unredo->clear();
	World::instance().clear();
}
}//Operation
}//MinePlanner