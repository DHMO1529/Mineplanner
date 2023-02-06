#include "nbt/nbtFunctions.hpp"

#pragma warning(push)
#pragma warning(disable:4244)

#include <fstream>
#include <boost/detail/endian.hpp>
#include <boost/foreach.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "Util/reverse_endian.hpp"
namespace nbt{
//読み出し
class NbtIStream
{
public:
	typedef std::ifstream super;
	NbtIStream(const char* filename):
	 ifs(filename,std::ios::binary | std::ios::in)
	,gzFilter()
	,in(&gzFilter)
	{
		gzFilter.push(boost::iostreams::gzip_decompressor());
		gzFilter.push(ifs);
	}
	bool fail()
	{
		return in.fail();
	}
	char readByte()
	{
		return in.get();
	}
	short readShort()
	{
		return this->read<short>();
	}
	int readInt()
	{
		return this->read<int>();
	}
	long long int readInt64()
	{
		return this->read<long long int>();
	}
	float readFloat()
	{
		return this->read<float>();
	}
	double readDouble()
	{
		return this->read<double>();
	}
	std::string readString()
	{
		short nameLength = this->readShort();
		std::vector<char> buf(nameLength + 1);
		in.read(&buf[0],nameLength);
		buf[nameLength] = '\0';
		return std::string(&buf[0]);
	}
	void close()
	{
		ifs.close();
	}
private:
	template<class T>
	T read()
	{
		union{
			T value;
			char bin[sizeof(T)];
		}toValue;

		for(int i = 0 ; i < sizeof(toValue.bin) ; ++i)
		{
			toValue.bin[i] = in.get();
		}
#ifdef BOOST_LITTLE_ENDIAN
		toValue.value = Util::reverse_endian(toValue.value);
#endif
		return toValue.value;
	}
	std::ifstream ifs;
	boost::iostreams::filtering_streambuf<boost::iostreams::input> gzFilter;
	std::istream in;
};

class NbtReader
{
public:
	NbtReader(const char* filename):
	 ns(filename)
	{
	}
	Tag::ptr read()
	{
		if(ns.fail()){return Tag::ptr();}

		try
		{
			return this->readTag();
		}
		catch(std::bad_cast&)
		{
			throw std::runtime_error("");
		}
		return Tag::ptr();
	}
	void clear()
	{
		ns.close();
	}
private:
	//丸々タグロード
	Tag::ptr readTag()
	{
		char tag = ns.readByte();

		if(tag == TAG_End)
		{
			return Tag::ptr();//エンドならnullを返す
		}

		std::string name = ns.readString();

		return readTagPayload(name,static_cast<TagType>(tag));
	}
	//中身のみロード
	Tag::ptr readTagPayload(const std::string& name,TagType type)
	{
		switch(type)
		{
		case TAG_Byte:
			return Tag::makeTag(name,TAG_Byte,ns.readByte());
			break;
		case TAG_Short:
			return Tag::makeTag(name,TAG_Short,ns.readShort());
			break;
		case TAG_Int:
			return Tag::makeTag(name,TAG_Int,ns.readInt());
			break;
		case TAG_Long:
			return Tag::makeTag(name,TAG_Long,ns.readInt64());
			break;
		case TAG_Float:
			return Tag::makeTag(name,TAG_Float,ns.readFloat());
			break;
		case TAG_Double:
			return Tag::makeTag(name,TAG_Double,ns.readDouble());
		case TAG_Byte_Array:
			{
				int arraySize = ns.readInt();
				Tag::payloadType_byteArray byteArray(arraySize);
				for(int i = 0 ; i < arraySize ; ++i)
				{
					byteArray[i] = ns.readByte();
				}
				return Tag::makeTag(name,TAG_Byte_Array,byteArray);
			}
			break;
		case TAG_String:
			return Tag::makeTag(name,TAG_String,ns.readString());
			break;
		case TAG_List:
			//listは名前なしの配列
			{
				char listTag = ns.readByte();
				int listSize = ns.readInt();
				Tag::payloadType_list payload(listSize);
				for(int i = 0 ; i < listSize ; ++i)
				{
					payload[i] = readTagPayload("",static_cast<TagType>(listTag));
				}
				return Tag::makeTag(name,TAG_List,payload);
			}
			break;
		case TAG_Compound:
			{
				Tag::payloadType_compound payload;
				for(;;)
				{
					Tag::ptr add = readTag();
					if(!add)
					{
						break;
					}
					else
					{
						payload.push_back(add);
					}
				}
				return Tag::makeTag(name,TAG_Compound,payload);
			}
			break;
		default:
			assert(0);
			break;
		}
		
		assert(0);

		return Tag::ptr();
	}
	NbtIStream ns;
};
Tag::ptr read_nbt(const char* filename)
{
	NbtReader nbtReader(filename);
	return nbtReader.read();
}

//書き出し
class NbtOStream
{
public:
	NbtOStream(const char* filename):
	 ofs(filename,std::ios::binary | std::ios::out)
	,gzFilter()
	,out(&gzFilter)
	{
		gzFilter.push(boost::iostreams::gzip_compressor());
		gzFilter.push(ofs);
	}
	bool fail()
	{
		return out.fail();
	}
	void writeByte(char b)
	{
		out.put(b);
	}
	void writeShort(short s)
	{
		this->write(s);
	}
	void writeInt(int i)
	{
		this->write(i);
	}
	void writeInt64(long long int i)
	{
		this->write(i);
	}
	void writeFloat(float f)
	{
		this->write(f);
	}
	void writeDouble(double d)
	{
		this->write(d);
	}
	void writeString(const std::string& str)
	{
		this->writeShort(static_cast<short>(str.length()));
		out.write(str.c_str(),str.length());
	}
	void close()
	{
		ofs.close();
	}
private:
	template<class T>
	void write(T val)
	{
		union{
			T value;
			char bin[sizeof(T)];
		}fromValue;
		fromValue.value = val;

#ifdef BOOST_LITTLE_ENDIAN
		fromValue.value = Util::reverse_endian(fromValue.value);
#endif
		out.write(fromValue.bin,sizeof(T));
	}

	std::ofstream ofs;
	boost::iostreams::filtering_streambuf<boost::iostreams::output> gzFilter;
	std::ostream out;
};

class NbtWriter
{
public:
	NbtWriter(const char* filename):ns(filename){}

	void write(Tag::ptr tag)
	{
		if(ns.fail()){return;}

		if(!tag){return;}

		try
		{
			writeTag(tag);
		}
		catch(std::bad_cast&)
		{
			throw std::runtime_error("");
		}
	}

private:
	void writeTag(Tag::ptr tag)
	{
		ns.writeByte(static_cast<char>(tag->getTagType()));
		ns.writeString(tag->getName());

		writeTagPayload(tag);
	}
	void writeTagPayload(Tag::ptr tag)
	{
		switch(tag->getTagType())
		{
		case TAG_Byte:
			ns.writeByte(tag->getBytePayload());
			break;
		case TAG_Short:
			ns.writeShort(tag->getShortPayload());
			break;
		case TAG_Int:
			ns.writeInt(tag->getIntPayload());
			break;
		case TAG_Long:
			ns.writeInt64(tag->getLongPayload());
			break;
		case TAG_Float:
			ns.writeFloat(tag->getFloatPayload());
			break;
		case TAG_Double:
			ns.writeDouble(tag->getDoublePayload());
			break;
		case TAG_Byte_Array:
			{
				Tag::payloadType_byteArray byteArray = tag->getByteArrayPayload();
				ns.writeInt(byteArray.size());//size
				BOOST_FOREACH(char b,byteArray)
				{
					ns.writeByte(b);
				}
			}
			break;
		case TAG_String:
			ns.writeString(tag->getStringPayload());
			break;
		case TAG_List:
			{
				Tag::payloadType_list list = tag->getListPayload();
				if(list.empty())
				{
					ns.writeByte(TAG_Byte);
				}
				else
				{
					ns.writeByte(list[0]->getTagType());//tagType
				}
				
				ns.writeInt(list.size());

				BOOST_FOREACH(Tag::ptr p,list)
				{
					writeTagPayload(p);
				}
			}
			break;
		case TAG_Compound:
			{
				Tag::payloadType_compound payload = tag->getCompoundPayload();
				BOOST_FOREACH(Tag::ptr p,payload)
				{
					writeTag(p);
				}
				ns.writeByte(TAG_End);
			}
			break;
		default:
			assert(0);
			break;
		}
	}

	NbtOStream ns;
};

void write_nbt(Tag::ptr tag,const char* filename)
{
	NbtWriter nbtWriter(filename);
	nbtWriter.write(tag);
}
}//nbt

#pragma warning(pop)
