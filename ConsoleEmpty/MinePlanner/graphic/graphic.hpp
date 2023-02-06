#ifndef MINEPLANNER_GRAPHIC_GRAPHIC
#define MINEPLANNER_GRAPHIC_GRAPHIC

/**
* グラフィックを担当する
* このへっだのみをインクルード
*/

#include "MinePlanner/graphic/Rendering.hpp"
#include "MinePlanner/graphic/getFps.hpp"
#include "MinePlanner/graphic/SetResolution.hpp"
#include "MinePlanner/graphic/GetResolution.hpp"
#include "MinePlanner/graphic/DrawLookAt.hpp"
#include "MinePlanner/graphic/Camera.hpp"
#include "MinePlanner/graphic/DrawRect.hpp"
#include "MinePlanner/graphic/DrawContour.hpp"
#include "MinePlanner/graphic/DrawArrangeXYZ.hpp"
#include "MinePlanner/graphic/DrawBlock.hpp"

#include "MinePlanner/graphic/DrawSelectPointSet.hpp"
#include "MinePlanner/graphic/DrawTransparentBlockSet.hpp"

namespace MinePlanner{
namespace graphic{
void init();
void fin();
}//graphic
}//MinePlanner
#endif