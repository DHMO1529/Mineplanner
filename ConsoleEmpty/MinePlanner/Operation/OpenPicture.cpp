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
		NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"エラー",
			L"png画像読み込みに失敗しました。\nファイルが壊れている可能性があります。");
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

	//ドット絵は輪郭が無いほうが綺麗に見える
	g_config->getBlockContourEnableValueObject().setValue(false);
}
}//Operation
}//MinePlanner