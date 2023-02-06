#ifndef MINEPLANNER_STRING_CAST
#define MINEPLANNER_STRING_CAST
namespace MinePlanner{
/**
* std::string,std::wstring,juce::stringを相互に変換します。その他の型は不正です。コンパイルは通りません。
* @tamplate param 変換先の型
* @template param 変換元の型
*
* @param 変換元の文字列
* @return 変換後の文字列
*/
template<class destination,class source>
destination string_cast(const source& src);
}//MinePlanner
#endif