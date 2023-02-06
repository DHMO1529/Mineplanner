#ifndef MINEPLANNER_DATABASE_RAWBLOCKDATA_HPP
#define MINEPLANNER_DATABASE_RAWBLOCKDATA_HPP
namespace MinePlanner{
namespace DataBase{
//schematicやMinecraftセーブデータの生形式データ
class RawBlockData
{
public:
	RawBlockData():m_id(0),m_extention(0){}
	unsigned char getId()const
	{
		return m_id;
	}
	unsigned char getExtention()const
	{
		return m_extention;
	}
	static RawBlockData make(unsigned char id,unsigned char extention)
	{
		RawBlockData rbd;
		rbd.m_id = id;
		rbd.m_extention = extention;
		return rbd;
	}
private:
	unsigned char m_id;
	unsigned char m_extention;
};
}//DataBase
}//MinePlanner
#endif