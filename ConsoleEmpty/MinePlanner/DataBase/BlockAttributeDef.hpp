#ifndef MINEPLANNER_DATABASE_BLOCKATTRIBUTEDEF_HPP
#define MINEPLANNER_DATABASE_BLOCKATTRIBUTEDEF_HPP
namespace MinePlanner{
namespace DataBase{
enum orient_type{
	ORIENT_TYPE_NONE = 0,/*回転しない*/
	ORIENT_TYPE_YAXIS,/*Y回転はする ex)カボチャ*/
	/*ORIENT_TYPE_XYAXIS,*/ /*XY回転する ex) ピストン*/ /*保留*/
};
enum draw_type{
	DRAW_TYPE_CUBE = 0,
	DRAW_TYPE_MODEL,
};
}//DataBase
}//MinePlanner
#endif