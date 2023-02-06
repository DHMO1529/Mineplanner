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
Tag�́A���O�A�^�O�^�C�v�A�f�[�^(payload)������
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

	//type��pay�̐����������Ă��Ȃ��ꍇ�Astd::bad_cast�𓊂��܂��B
	void setPayload(TagType type,boost::any pay);

	//�^���Ԉ���Ă����ꍇ�Astd::bad_cast�𓊂��܂��B
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

	//���� : �@�����������Ă���q�̒����炵���T���܂���B�q�̎q�A�̂悤�ɍċA�I�ɂ͒��ׂ܂���B
	//�@�@�@ �A�����͔�r�Ώۂł͂���܂���
	Tag::ptr getTagFromName(const std::string& tagName)const;

	//tagType��TAG_Compound�̎��A�v�f��ǉ����܂��B
	//�����łȂ��ꍇ�͉������܂���B
	//���O�����Ԃ�ƁAstd::invalid_argument�𓊂��܂��B
	void addCompoundChild(Tag::ptr child);

	//tagType��TAG_Compound�̎��A�v�f���폜���܂��B
	//�����łȂ��ꍇ�͉������܂���B
	void removeCompoundChild(const std::string& removeName);

	//tagType��TAG_Compound�̎��A�v�f��S�폜���܂��B
	void clearCompoundChild();

	//tagType��TAG_List�̎��A�v�f��ǉ����܂��B
	void addListChild(TagType tag,boost::any pay);

	//tagType��TAG_List�̎��A�v�f��S�폜���܂��B
	void clearListChild();

	//type��pay�̐����������Ă��Ȃ��ꍇ�Astd::bad_cast�𓊂��܂��B
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