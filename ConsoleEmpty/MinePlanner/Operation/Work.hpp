#ifndef MINEPLANNER_OPERATION_WORK
#define MINEPLANNER_OPERATION_WORK
#include <boost/shared_ptr.hpp>
/**
* ワールドに対する操作を定義する
* 操作は必ず元に戻せる
* 作ったら即exeする、作ってからワールドは編集されないものとする
*/
namespace MinePlanner{
namespace Operation{
class Work
{
public:
	virtual ~Work(){}
public:
	/**
	* 操作を実行する
	* @return 成功したならtrue それ以外はfalse
	*/
	virtual bool exe() = 0;

	//元に戻す
	virtual void undo() = 0;

	//やり直す 一度exeで成功しているので絶対成功するべきだ
	virtual void redo() = 0;
public:
	typedef boost::shared_ptr<Work> ptr;
};
}//Operation
}//MinePlanner
#endif