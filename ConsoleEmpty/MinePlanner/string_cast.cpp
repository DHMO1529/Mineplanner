#include "MinePlanner/string_cast.hpp"

#include <string>
#include <juce.h>
/**
* ���C�h�����񁨃}���`�o�C�g������
* @param str �ϊ����郏�C�h������
* @return �ϊ���}���`�o�C�g������
*/
inline std::string toMultiString(const std::wstring& str)
{
	std::vector<char> buf(str.length() * MB_CUR_MAX + 1);
	wcstombs(&buf[0],str.c_str(), str.length() * MB_CUR_MAX + 1);
	return &buf[0];
}
/**
* �}���`�o�C�g�����񁨃��C�h������
* @param str �ϊ�����}���`�o�C�g������
* @return �ϊ��ハ�C�h������
*/
inline std::wstring toWideString(const std::string& str)
{
	std::vector<wchar_t> buf(str.length() + 1);
	mbstowcs(&buf[0], str.c_str(), str.length() + 1);
	return &buf[0];
}

namespace MinePlanner{
//std::string -> std::wstring
template<>
std::wstring string_cast<std::wstring,std::string>(const std::string& src)
{
	return toWideString(src);
}
//std::string -> juce::String
template<>
juce::String string_cast<String,std::string>(const std::string& src)
{
	return juce::String( toWideString(src).c_str() );
}

//std::wstring -> std::string
template<>
std::string string_cast<std::string,std::wstring>(const std::wstring& src)
{
	return toMultiString(src);
}
//std::wstring -> juce::String
template<>
juce::String string_cast<juce::String,std::wstring>(const std::wstring& src)
{
	return juce::String( src.c_str() );
}

//juce::String -> std::string
template<>
std::string string_cast<std::string,juce::String>(const juce::String& src)
{
	return toMultiString(std::wstring( src.toUTF16() ));
}
//juce::String -> std::wstring
template<>
std::wstring string_cast<std::wstring,juce::String>(const juce::String& src)
{
	return std::wstring( src.toUTF16() );
}
}//MinePlanner