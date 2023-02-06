#ifndef UTIL_REVERSE_ENDIAN
#define UTIL_REVERSE_ENDIAN
#include <algorithm>
namespace Util{
template<class T>
T reverse_endian(T value)
{
  char * first = reinterpret_cast<char*>(&value);
  char* last = first + sizeof(T);
  std::reverse(first, last);
  return value;
}
}//Util
#endif