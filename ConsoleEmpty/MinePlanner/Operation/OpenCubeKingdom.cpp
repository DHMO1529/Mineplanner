#include "MinePlanner/Operation/OpenCubeKingdom.hpp"
#include <juce.h>
#include <fstream>
#include <exception>

#include <boost/lexical_cast.hpp>
#include "MinePlanner/Color.hpp"
#include "MinePlanner/World.hpp"
#include "MinePlanner/string_cast.hpp"
#include "MinePlanner/DataBase/DataBase.hpp"
namespace MinePlanner{
namespace Operation{
void OpenCubeKingdom(const std::string& filename)
{
	std::ifstream ifs(filename);

	//BlockID
	const int WHITEWOOL_ID = 24;

	//�w�b�_�ǂݎ��
	static char buffer[256];
	ifs.getline(buffer,sizeof(buffer));
	if(strcmp(buffer,"CubeKingdom") != 0)
	{
		NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon,L"�G���[",
			L"�L���[�u�L���O�_���t�@�C���ǂݍ��݂Ɏ��s���܂����B\n�t�@�C�������Ă���\��������܂��B");
		return;
	}

	int IsNonTextureCube = 0;
	int IsTextureCube = 0;
	ifs.getline(buffer,sizeof(buffer));
	sscanf(buffer,"%d %d",&IsNonTextureCube,&IsTextureCube);

	//�e�N�X�`���Ȃ��L���[�u������
	int OFFSET = -100;
	if(IsNonTextureCube)
	{
		ifs.getline(buffer,sizeof(buffer));
		const int BOXEL_NUM = boost::lexical_cast<int>(std::string(buffer));

		for(int i = 0 ; i < BOXEL_NUM ; ++i)
		{
			int x,y,z;
			unsigned color0x;
			ifs.getline(buffer,sizeof(buffer));
			sscanf(buffer,"%d %d %d %x",&x,&y,&z,&color0x);

			unsigned char r = (color0x & 0x00ff0000) >> 16;
			unsigned char g = (color0x & 0x0000ff00) >> 8;
			unsigned char b = (color0x & 0x000000ff);
			Color color(r,g,b);
			const int id = DataBase::getNearColorBlockID(color);

			Point p(x + OFFSET,y + OFFSET,-(z + OFFSET));

			World::instance().add(p,id,Pose());
		}
	}

	if(IsTextureCube)
	{
		ifs.getline(buffer,sizeof(buffer));//�e�N�X�`����

		ifs.getline(buffer,sizeof(buffer));
		const int BOXEL_NUM = boost::lexical_cast<int>(std::string(buffer));

		for(int i = 0 ; i < BOXEL_NUM ; ++i)
		{
			int x,y,z;

			ifs.getline(buffer,sizeof(buffer));
			sscanf(buffer,"%d %d %d",&x,&y,&z);

			Point p(x + OFFSET,y + OFFSET,-(z + OFFSET));

			World::instance().add(p,WHITEWOOL_ID,Pose());
		}
	}
}
}//Operation
}//MinePlanner
