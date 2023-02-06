#include "MinePlanner/UI/MakeSnapShot.hpp"

#include "MinePlanner/UI/Widget/OpenglScreen.hpp"
#include "MinePlanner/graphic/gl.hpp"

#include <vector>
namespace MinePlanner{
namespace UI{
Image MakeSnapShot()
{
	auto component = Widget::OpenGLScreen::getInstance();
	const int w = component->getWidth();
	const int h = component->getHeight();

	std::vector<unsigned> buffer(w * h);
	glReadPixels(0,0,w,h,GL_RGBA,GL_UNSIGNED_BYTE,reinterpret_cast<void*>(&buffer[0]));
	
	Image image(Image::RGB,w,h,true);
	Image::BitmapData bitmap(image,Image::BitmapData::writeOnly);
	for(int y = 0 ; y < h ; ++y)
	{
		for(int x = 0 ; x < w ; ++x)
		{
			const unsigned gl_color_data = buffer[ w * y + x ];
			const unsigned char r = gl_color_data & 0xff;
			const unsigned char g = (gl_color_data & 0xff00) >> 8;
			const unsigned char b = (gl_color_data & 0xff0000) >> 16;
			Colour color(r,g,b);
			bitmap.setPixelColour(x,h - y - 1,color);
		}
	}
	return image;
}
}//UI
}//MinePlanner
