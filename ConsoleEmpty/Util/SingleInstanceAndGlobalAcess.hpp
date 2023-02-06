#ifndef UTIL_SINGLEINSTANCE_AND_GLOBALACESS
#define UTIL_SINGLEINSTANCE_AND_GLOBALACESS
#include <cassert>
namespace Util{
template<typename T> 
class SingleInstanceAndGlobalAcess
{
public:
	SingleInstanceAndGlobalAcess()
	{
		assert( !m_pGrobal );
		//Singleton<T>* Ç∆ T* Ç≈ÇÕà íuÇ™à·Ç§Ç©Ç‡ÇµÇÍÇ»Ç¢
		//Ç»ÇÃÇ≈ÉYÉåÇï‚ê≥Ç∑ÇÈ
		int offset = (int)(T*)1 - (int)(SingleInstanceAndGlobalAcess<T>*)(T*)1;
		m_pGrobal = (T*)((int)this + offset);
	}
	~SingleInstanceAndGlobalAcess()
	{
		m_pGrobal = 0;
	}
	static T* getInstance()
	{
		assert( m_pGrobal );
		return m_pGrobal;
	}
private:
	SingleInstanceAndGlobalAcess(const SingleInstanceAndGlobalAcess&);
	void operator=(const SingleInstanceAndGlobalAcess&);
private:
	static T* m_pGrobal;
};
template<typename T>
T* SingleInstanceAndGlobalAcess<T>::m_pGrobal = 0;
}//Util
#endif