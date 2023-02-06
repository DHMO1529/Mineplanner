#include "MinePlanner/graphic/FpsCounter.hpp"
#include <boost/foreach.hpp>
namespace MinePlanner{
namespace graphic{
FpsCounter::FpsCounter():
 m_TimeList()
,m_timer()
,m_fps(0)
{
}
FpsCounter::~FpsCounter()
{
}
void FpsCounter::update()
{
	if(m_TimeList.size() >= SamplingNum)
	{
		m_TimeList.pop_front();
	}
	m_TimeList.push_back(m_timer.elapsed() * 1000.0);
	m_timer.restart();

	double Sum = 0;
	BOOST_FOREACH(const double& Value,m_TimeList)
	{
		Sum += Value;
	}
	double AverageTime = Sum / static_cast<double>(m_TimeList.size());
	m_fps = 1000.0 / AverageTime;
}
double FpsCounter::getFPS()const
{
	return m_fps;
}
}//graphic
}//MinePlanner
