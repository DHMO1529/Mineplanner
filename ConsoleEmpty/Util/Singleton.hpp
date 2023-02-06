#ifndef UTIL_SINGLETON
#define UTIL_SINGLETON
/*
�����V���O���g�����[�e�B���e�B�@by GamePrograming Gems1
*/
#include <cassert>
namespace Util{
template<typename T> class Singleton
{
public:
	Singleton(){
		assert( !m_pSingleton && "�֐�->UsLib::Util::Singleton::Singleton() �G���[->���d�쐬");

		//Singleton<T>* �� T* �ł͈ʒu���Ⴄ��������Ȃ�
		//�Ȃ̂ŃY����␳����
		int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
		m_pSingleton = (T*)((int)this + offset);
	}
	virtual ~Singleton(){
		m_pSingleton = 0;
	}
	static T* pInstance(){
		return m_pSingleton;
	}
	static void Create()
	{
		new T();
	}
	//��������R���X�g���N�g
	template<class U>
	static void Create(const U& Arg0)
	{
		new T(Arg0);
	}
	template<class U,class V>
	static void Create(const U& Arg0,const V& Arg1)
	{
		new T(Arg0,Arg1);
	}
	template<class U,class V,class W>
	static void Create(const U& Arg0,const V& Arg1,const W& Arg2)
	{
		new T(Arg0,Arg1,Arg2);
	}
	template<class U,class V,class W,class X>
	static void Create(const U& Arg0,const V& Arg1,const W& Arg2,const X& Arg3)
	{
		new T(Arg0,Arg1,Arg2,Arg3);
	}

	static void Destory()
	{
		delete Singleton<T>::pInstance();
	}
private:
	Singleton(const Singleton&);
	void operator=(const Singleton&);

	static T* m_pSingleton;
};
template<typename T> T* Singleton<T>::m_pSingleton = 0;

}//Util
#endif
