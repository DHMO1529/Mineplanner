#ifndef MINEPLANNER_GRAPHIC_FPSCOUNTER
#define MINEPLANNER_GRAPHIC_FPSCOUNTER
#include <boost/timer.hpp>
#include <list>
namespace MinePlanner{
namespace graphic{
class FpsCounter
{
public:
	FpsCounter();
	~FpsCounter();

	void update();
	double getFPS()const;
private:
		enum{SamplingNum = 50,};
	std::list<double> m_TimeList;
	boost::timer m_timer;
	double m_fps;
};
}//graphic
}//MinePlanner
#endif
