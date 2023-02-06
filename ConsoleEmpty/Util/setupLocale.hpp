#ifndef UTIL_LOCALE
#define UTIL_LOCALE
#include <locale>
namespace Util{
inline void setupLocale()
{
	std::locale::global( std::locale("jpn") );
}
}//Util
#endif