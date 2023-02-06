#ifndef NBT_TAG
#define NBT_TAG
#include <string>
#include <sstream>
#include <vector>
#include <exception>

#include <boost/shared_ptr.hpp>
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include "nbt/TagType.hpp"
namespace nbt{
/*
Tagは、名前、タグタイプ、データ(payload)を持つ
*/
class Tag : private boost::noncopyable
{
public:
	typedef boost::shared_ptr<Tag> ptr;
	typedef boost::shared_ptr<const Tag> cptr;

	typedef char payloadType_byte;
	typedef short payloadType_short;
	typedef int payloadType_int;
	typedef long long int payloadType_long;
	typedef float payloadType_float;
	typedef double payloadType_double;
	typedef std::vector<payloadType_byte> payloadType_byteArray;
	typedef std::string payloadType_string;
	typedef std::vector<Tag::ptr> payloadType_list;
	typedef std::vector<Tag::ptr> payloadType_compound;

	void setName(const std::string& newName){name = newName;}
	std::string getName()const              {return name;}
	
	TagType getTagType()const{return tagType;}

	//typeとpayの整合性が取れていない場合、std::bad_castを投げます。
	void setPayload(TagType type,boost::any pay);

	//型が間違っていた場合、std::bad_castを投げます。
	payloadType_byte getBytePayload()const;
	payloadType_short getShortPayload()const;
	payloadType_int getIntPayload()const;
	payloadType_long getLongPayload()const;
	payloadType_float getFloatPayload()const;
	payloadType_double getDoublePayload()const;
	payloadType_byteArray getByteArrayPayload()const;
	payloadType_string getStringPayload()const;
	payloadType_list getListPayload()const;
	payloadType_compound getCompoundPayload()const;

	std::string toString()const;

	//注意 : ①自分が持っている子の中からしか探しません。子の子、のように再帰的には調べません。
	//　　　 ②自分は比較対象ではありません
	Tag::ptr getTagFromName(const std::string& tagName)const;

	//tagTypeがTAG_Compoundの時、要素を追加します。
	//そうでない場合は何もしません。
	//名前がかぶると、std::invalid_argumentを投げます。
	void addCompoundChild(Tag::ptr child);

	//tagTypeがTAG_Compoundの時、要素を削除します。
	//そうでない場合は何もしません。
	void removeCompoundChild(const std::string& removeName);

	//tagTypeがTAG_Compoundの時、要素を全削除します。
	void clearCompoundChild();

	//tagTypeがTAG_Listの時、要素を追加します。
	void addListChild(TagType tag,boost::any pay);

	//tagTypeがTAG_Listの時、要素を全削除します。
	void clearListChild();

	//typeとpayの整合性が取れていない場合、std::bad_castを投げます。
	static Tag::ptr makeTag(const std::string& name,TagType tagType,boost::any payload);
	static Tag::ptr makeListTag(const std::string& name);
	static Tag::ptr makeCompoundTag(const std::string& name);
private:
	Tag();
private:
	std::string name;
	TagType tagType;
	boost::any payload;
};
}//nbt
#endif