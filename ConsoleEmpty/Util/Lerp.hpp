#ifndef UTIL_LERP
#define UTIL_LERP
namespace Util{
template<class T>
class Lerp
{
public:
	Lerp(const T& X0,const T& Y0,const T& X1,const T& Y1)
	{
		a = (Y1 - Y0) / (X1 - X0);
		b = Y0 - a * X0;
	}
	T operator()(const T& Arg)const
	{
		return a * Arg + b;
	}
	T GetA()const
	{
		return a;
	}
	T GetB()const
	{
		return b;
	}
private:
	float a,b;
};
typedef Lerp<float> Lerpf;
typedef Lerp<double> Lerpd;
}//Util
#endif