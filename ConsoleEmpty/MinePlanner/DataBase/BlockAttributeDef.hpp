#ifndef MINEPLANNER_DATABASE_BLOCKATTRIBUTEDEF_HPP
#define MINEPLANNER_DATABASE_BLOCKATTRIBUTEDEF_HPP
namespace MinePlanner{
namespace DataBase{
enum orient_type{
	ORIENT_TYPE_NONE = 0,/*��]���Ȃ�*/
	ORIENT_TYPE_YAXIS,/*Y��]�͂��� ex)�J�{�`��*/
	/*ORIENT_TYPE_XYAXIS,*/ /*XY��]���� ex) �s�X�g��*/ /*�ۗ�*/
};
enum draw_type{
	DRAW_TYPE_CUBE = 0,
	DRAW_TYPE_MODEL,
};
}//DataBase
}//MinePlanner
#endif