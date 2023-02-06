#ifndef MINEPLANNER_GRAPHIC_RESOURCE_HPP
#define MINEPLANNER_GRAPHIC_RESOURCE_HPP
#include "MinePlanner/graphic/Texture.hpp"
#include "MinePlanner/graphic/DisplayList.hpp"
namespace MinePlanner{
namespace graphic{
void InitResource();
void FinResource();

Texture::ptr getTexture();
DisplayList getArrowDisplayList();
DisplayList getBlockDisplayList(int blockId);
DisplayList getContourDisplayList();
}//graphic
}//MinePlanner
#endif