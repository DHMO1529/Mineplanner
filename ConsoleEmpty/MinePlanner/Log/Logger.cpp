#include "MinePlanner/Log/Logger.hpp"

#include <time.h>
#include <fstream>
#include <limits>
#include <juce.h>

#include "MinePlanner/Log/DebugPrint.hpp"
#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace Log{
const std::string LOG_FILENAME = "MinePlannerLog.txt";

inline std::string getTimeString()
{
	time_t Time = time(NULL);
	tm* date = localtime(&Time);

	char str[256];
	strftime(str, 255, "%Y年 %B %d日 %A %p%I時%M分", date);
	return std::string(str);
}

//ファイルに書き込むジョブ
class LogJob : public ThreadPoolJob
{
public:
	LogJob(std::ofstream& stream,std::string line):
	 m_ofstream(stream)
	,m_line(line)
	,ThreadPoolJob(String::empty){}

	virtual JobStatus runJob()
	{
		DebugPrint(m_line);
		m_ofstream << m_line << std::endl;
		m_ofstream.flush();
		return jobHasFinishedAndShouldBeDeleted;
	}
	virtual void removedFromQueue(){}
private:
	std::ofstream& m_ofstream;
	std::string m_line;
};

class LoggerImpl : public Logger
{
public:
	LoggerImpl():m_ofs(LOG_FILENAME),m_pool(1)
	{
		m_ofs << ApplicationConstant::NAME << " Log" << std::endl;
		m_ofs << "program start = " << getTimeString() << std::endl;

	}
	~LoggerImpl()
	{
		while(true)
		{
			if(m_pool.getNumJobs() == 0)
			{
				break;
			}

			ThreadPoolJob* job = m_pool.getJob(0);
			m_pool.waitForJobToFinish(job,std::numeric_limits<int>::max());
		}

		m_ofs << "program end = " << getTimeString() << std::endl;
	}
	virtual void post(const std::string& line)
	{
		m_pool.addJob(new LogJob(m_ofs,line));
	}
private:
	std::ofstream m_ofs;
	ThreadPool m_pool;
};

Logger::ptr Logger::create()
{
	return ptr(new LoggerImpl());
}
}//Log
}//MinePlanner