#ifndef MINEPLANNER_LOG_LOGMANAGER
#define MINEPLANNER_LOG_LOGMANAGER
#include "Util/Singleton.hpp"
#include "MinePlanner/Log/Logger.hpp"
namespace MinePlanner{
namespace Log{
//���O�������݂ɃO���[�o���ȃA�N�Z�X���
class LogManager : public Util::Singleton<LogManager>
{
public:
	LogManager():m_logger()
	{
		m_logger = Log::Logger::create();
	}
	void post(const std::string& line)const
	{
		m_logger->post(line);
	}
private:
	Log::Logger::ptr m_logger;
};
}//Log
}//MinePlanner
inline MinePlanner::Log::LogManager* g_pLogManager()
{
	return MinePlanner::Log::LogManager::pInstance();
}
#endif
