#include "nbt/Tag.hpp"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

namespace nbt{
//private
Tag::Tag():
 name()
,tagType()
,payload(){}

Tag::ptr Tag::makeTag(const std::string& name,TagType tagType,boost::any payload)
{
	Tag::ptr p(new Tag());
	p->setName(name);
	p->setPayload(tagType,payload);
	return p;
}
Tag::ptr Tag::makeListTag(const std::string& name)
{
	return Tag::makeTag(name,TAG_List,Tag::payloadType_list());
}
Tag::ptr Tag::makeCompoundTag(const std::string& name)
{
	return Tag::makeTag(name,TAG_Compound,Tag::payloadType_compound());
}
void Tag::setPayload(TagType type,boost::any pay)
{
	try{
		switch(type)
		{
		case TAG_Byte:
			boost::any_cast<payloadType_byte>(pay);
			break;
		case TAG_Short:
			boost::any_cast<payloadType_short>(pay);
			break;
		case TAG_Int:
			boost::any_cast<payloadType_int>(pay);
			break;
		case TAG_Long:
			boost::any_cast<payloadType_long>(pay);
			break;
		case TAG_Float:
			boost::any_cast<payloadType_float>(pay);
			break;
		case TAG_Double:
			boost::any_cast<payloadType_double>(pay);
			break;
		case TAG_Byte_Array:
			boost::any_cast<payloadType_byteArray>(pay);
			break;
		case TAG_String:
			boost::any_cast<payloadType_string>(pay);
			break;
		case TAG_List:
			boost::any_cast<payloadType_list>(pay);
			break;
		case TAG_Compound:
			boost::any_cast<payloadType_compound>(pay);
			break;
		default:
			throw std::runtime_error("void Tag::setPayload(TagType type,boost::any pay)");
			break;
		}
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	tagType = type;
	payload = pay;
}
Tag::payloadType_byte Tag::getBytePayload()const
{
	try{
		return boost::any_cast<payloadType_byte>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_byte();
}
Tag::payloadType_short Tag::getShortPayload()const
{
	try{
		return boost::any_cast<payloadType_short>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_short();
}
Tag::payloadType_int Tag::getIntPayload()const
{
	try{
		return boost::any_cast<payloadType_int>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_int();
}
Tag::payloadType_long Tag::getLongPayload()const
{
	try{
		return boost::any_cast<payloadType_long>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_long();
}
Tag::payloadType_float Tag::getFloatPayload()const
{
	try{
		return boost::any_cast<payloadType_float>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_float();
}
Tag::payloadType_double Tag::getDoublePayload()const
{
	try{
		return boost::any_cast<payloadType_double>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_double();
}
Tag::payloadType_byteArray Tag::getByteArrayPayload()const
{
	try{
		return boost::any_cast<payloadType_byteArray>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_byteArray();
}
Tag::payloadType_string Tag::getStringPayload()const
{
	try{
		return boost::any_cast<payloadType_string>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_string();
}
Tag::payloadType_list Tag::getListPayload()const
{
	try{
		return boost::any_cast<payloadType_list>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_list();
}
Tag::payloadType_compound Tag::getCompoundPayload()const
{
	try{
		return boost::any_cast<payloadType_compound>(payload);
	}
	catch(boost::bad_any_cast&)
	{
		throw std::bad_cast();
	}

	throw std::runtime_error("Tag::payloadType_byte Tag::getBytePayload()const");
	return Tag::payloadType_compound();
}

Tag::ptr Tag::getTagFromName(const std::string& tagName)const
{
	if(tagType != TAG_List && tagType != TAG_Compound)
	{
		return Tag::ptr();
	}

	std::vector<Tag::ptr> tags = boost::any_cast<const std::vector<Tag::ptr>>(payload);
	BOOST_FOREACH(ptr p,tags)
	{
		if(p->getName() == tagName)
		{
			return p;
		}
	}
	return Tag::ptr();
}

void Tag::addCompoundChild(Tag::ptr child)
{
	if(tagType != TAG_Compound)
	{
		return;
	}

	const std::string childName = child->getName();
	payloadType_compound tags = this->getCompoundPayload();
	BOOST_FOREACH(Tag::ptr p,tags)
	{
		if(p->getName() == childName)
		{
			throw std::invalid_argument("");
		}
	}
	tags.push_back(child);
	payload = tags;
}
void Tag::removeCompoundChild(const std::string& removeName)
{
	if(tagType != TAG_Compound)
	{
		return;
	}
	payloadType_compound tags = this->getCompoundPayload();
	for(std::vector<Tag::ptr>::iterator It = tags.begin() ; It != tags.end() ; ++It)
	{
		if((*It)->getName() == removeName)
		{
			tags.erase(It);
			break;
		}
	}
	payload = tags;
}
void Tag::clearCompoundChild()
{
	if(tagType != TAG_Compound)
	{
		return;
	}
	payload = payloadType_compound();
}
void Tag::addListChild(TagType tag,boost::any pay)
{
	if(tagType != TAG_List)
	{
		return;
	}
	payloadType_list list = this->getListPayload();
	list.push_back(Tag::makeTag("",tag,pay));
	payload = list;
}
void Tag::clearListChild()
{
	if(tagType != TAG_List)
	{
		return;
	}
	payload = payloadType_list();
}
std::string Tag::toString()const
{
	switch(tagType)
	{
	case TAG_Byte:
		{
			const unsigned char c = this->getBytePayload();
			char buf[3];
			sprintf_s(buf,sizeof(buf),"%x",c);
			return name + "[byte] = " + std::string(buf) + "\n";
		}
		break;
	case TAG_Short:
		return name + "[short] = " + boost::lexical_cast<std::string,payloadType_short>( this->getShortPayload() ) + "\n";
		break;
	case TAG_Int:
		return name + "[int] = " + boost::lexical_cast<std::string,payloadType_int>( this->getIntPayload() ) + "\n";
		break;
	case TAG_Long:
		return name + "[int64] = " + boost::lexical_cast<std::string,payloadType_long>( this->getLongPayload() ) + "\n";
		break;
	case TAG_Float:
		return name + "[float] = " + boost::lexical_cast<std::string,payloadType_float>( this->getFloatPayload() ) + "\n";
		break;
	case TAG_Double:
		return name + "[double] = " + boost::lexical_cast<std::string,payloadType_double>( this->getDoublePayload() ) + "\n";
		break;
	case TAG_Byte_Array:
		{
			std::stringstream ss;

			payloadType_byteArray byteArray = this->getByteArrayPayload();
			ss << name << "[binary(" << byteArray.size() << ")] «" << std::endl;

			BOOST_FOREACH(payloadType_byte b,byteArray)
			{
				const unsigned char c = b;
				char buf[3];
				sprintf_s(buf,sizeof(buf),"%x",c);
				ss << buf;
			}
			ss << std::endl;
			return ss.str();
		}
		break;
	case TAG_String:
			return name + "[string] = " + this->getStringPayload() + "\n";
		break;
	case TAG_List:
		{
			std::stringstream ss;
			payloadType_list tagList = this->getListPayload();

			ss << name << "[list(" << tagList.size() << ")] ->" << std::endl;

			BOOST_FOREACH(Tag::ptr p,tagList)
			{
				ss << p->toString();
			}
			return ss.str();
		}
		break;
	case TAG_Compound:
		{
			std::stringstream ss;
			ss << name << "[compound] -> " << std::endl;
			payloadType_compound compound = this->getCompoundPayload();
			BOOST_FOREACH(Tag::ptr p,compound)
			{
				ss << p->toString();
			}
			return ss.str();
		}
		break;
	}
	return "";
}


}//nbt