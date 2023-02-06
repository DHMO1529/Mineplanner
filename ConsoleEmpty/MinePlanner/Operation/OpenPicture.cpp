#include "MinePlanner/Operation/OpenPicture.hpp"

#include <vector>
#include <fstream>
#include <juce.h>
#include "MinePlanner/DataBase/DataBase.hpp"
#include "MinePlanner/Color.hpp"
#include "MinePlanner/World.hpp"
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/GlobalConfig.hpp"
namespace MinePlanner{
namespace Operation{
void OpenPicture(const std::string& filename)
{
	std::ifstream ifs(filename,std::ios::binary);
	ifs.seekg(0,std::ios::end);
	std::vector<char> buffer( static_cast<int>(ifs.tellg()) );
	ifs.seekg(0,std::ios::beg);
	ifs.read(&buffer[0],buffer.size());

	Image image = ImageFileFormat::loadFrom(&buffer[0],buffer.size());
	if(image.isNull())
	{
		NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"�G���[",
			L"png�摜�ǂݍ��݂Ɏ��s���܂����B\n�t�@�C�������Ă���\��������܂��B");
		return;
	}

	const int w = image.getWidth();
	const int h = image.getHeight();

	Image::BitmapData bitmap(image,Image::BitmapData::readOnly);

	for(int y = 0 ; y < h ; ++y)
	{
		for(int x = 0 ; x < w ; ++x)
		{
			Colour c = bitmap.getPixelColour(x,y);
			if(c.getAlpha() == 0)
			{
				continue;
			}
			Color color(c.getRed(),c.getGreen(),c.getBlue());
			const int blockId = DataBase::getNearColorBlockID(color);

			World::instance().add(Point(x,h-y-1,0),blockId,Pose());
		}
	}

	//�h�b�g�G�͗֊s�������ق����Y��Ɍ�����
	g_config->getBlockContourEnableValueObject().setValue(false);
}
}//Operation
}//MinePlanner