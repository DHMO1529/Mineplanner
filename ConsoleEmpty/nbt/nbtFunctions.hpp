#ifndef NBT_NBTFUNCTIONS
#define NBT_NBTFUNCTIONS
#include "nbt/Tag.hpp"
namespace nbt{
Tag::ptr read_nbt(const char* filename);
void write_nbt(Tag::ptr tag,const char* filename);
}//nbt
#endif