#ifndef MINEPLANNER_STRING_CAST
#define MINEPLANNER_STRING_CAST
namespace MinePlanner{
/**
* std::string,std::wstring,juce::string�𑊌݂ɕϊ����܂��B���̑��̌^�͕s���ł��B�R���p�C���͒ʂ�܂���B
* @tamplate param �ϊ���̌^
* @template param �ϊ����̌^
*
* @param �ϊ����̕�����
* @return �ϊ���̕�����
*/
template<class destination,class source>
destination string_cast(const source& src);
}//MinePlanner
#endif