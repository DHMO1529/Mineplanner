#include "MinePlanner/graphic/Texture.hpp"

#include <vector>
#include <clx/unzip.h>
#include <juce.h>

#include "MinePlanner/ApplicationConstant.hpp"
#include "MinePlanner/graphic/gl.hpp"
namespace MinePlanner{
namespace graphic{
inline bool IsPow2(unsigned Val)
{
	if(Val == 0)
	{
		return false;
	}
	if( (Val & (Val-1)) == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}
class TextureImpl : public Texture
{
public:
	TextureImpl(const char* filename):
	 m_textureName(0)
	{
		clx::unzip unzip(ApplicationConstant::ZIP_ARCHIVE,ApplicationConstant::ZIP_PASSWORD);
		clx::unzip::iterator it = unzip.find(filename);
		if(it == unzip.end())
		{
			assert(0);
		}
		clx::unzip::stream_type& stream = *it;

		std::vector<char> bin_buffer;
		bin_buffer.reserve(33000);
		while(true)
		{
			char d = stream.get();
			if(stream.eof())
			{
				break;
			}
			bin_buffer.push_back(d);
		}

		Image image = ImageFileFormat::loadFrom(&bin_buffer[0],bin_buffer.size());
		const int WIDTH = image.getWidth();
		const int HEIGHT = image.getHeight();

		if(!IsPow2(WIDTH))
		{
			assert(0);
		}
		if(!IsPow2(HEIGHT))
		{
			assert(0);
		}
		Image::BitmapData bitmap(image,Image::BitmapData::readOnly);
		
		//argb -> rgba
		struct{
			unsigned operator()(const Colour& argb)
			{
				return argb.getRed() | argb.getGreen() << 8 | argb.getBlue() << 16 | argb.getAlpha() << 24;
			}
		}cast;

		//openglのテクスチャ座標に変更
		std::vector<unsigned> buf(WIDTH * HEIGHT);
		for(int j = 0 ; j < HEIGHT ; ++j)
		{
			int dsty = HEIGHT - 1 - j;
			int srcy = j;
			for(int i = 0 ; i < WIDTH ; ++i)
			{
				buf[dsty * WIDTH + i] = cast(bitmap.getPixelColour(i,srcy));
			}
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT,4);

		glGenTextures(1,&m_textureName);
		glBindTexture(GL_TEXTURE_2D,m_textureName);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D,0,4,WIDTH,HEIGHT,0,GL_RGBA,GL_UNSIGNED_BYTE,&buf[0]);

		glBindTexture(GL_TEXTURE_2D,0);
	}
	~TextureImpl()
	{
	 	if(m_textureName)
		{
			glDeleteTextures(1,&m_textureName);
			m_textureName = 0;
		}
	}

	virtual void bind()const
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,m_textureName);
	}
	virtual void unbind()const
	{
		glBindTexture(GL_TEXTURE_2D,0);
		glDisable(GL_TEXTURE_2D);
	}
private:
	unsigned m_textureName;
};
Texture::ptr Texture::createFromArchive(const char* filename)
{
	return Texture::ptr(new TextureImpl(filename));
}
}//graphic
}//MinePlanner