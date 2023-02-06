#ifndef MINEPLANNER_GRAPHIC_DRAWBLOCK_HPP
#define MINEPLANNER_GRAPHIC_DRAWBLOCK_HPP
#include "MinePlanner/Point.hpp"
#include "MinePlanner/Pose.hpp"
namespace MinePlanner{
namespace graphic{
//Å¶ó÷äsÇÕï`âÊÇµÇ‹ÇπÇÒ
void beginBlockDraw();
void endBlockDraw();
void drawBlock(const Point& point,int blockId,const Pose& pose);
void drawBlock(const Point& point,int blockId,const Pose& pose,float alpha);
void drawBlock(const Point& point,int blockId,const Pose& pose,float alpha,float size);
}//graphic
}//MinePlanner
#endif