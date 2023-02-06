#include "MinePlanner/graphic/FpsCount.hpp"
#include "MinePlanner/graphic/FpsCounter.hpp"
#include "MinePlanner/graphic/NowFps.hpp"
#include <glm/glm.hpp>
namespace MinePlanner{
namespace graphic{
namespace{
FpsCounter g_fpsCounter;
}
void FpsCount()
{
	g_fpsCounter.update();
	g_fps = static_cast<int>(glm::round(g_fpsCounter.getFPS()));
}
}//graphic
}//MinePlanner