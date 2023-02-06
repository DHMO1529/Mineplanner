#ifndef MINEPLANNER_UI_MYLOOKANDFEEL
#define MINEPLANNER_UI_MYLOOKANDFEEL
#include <juce.h>
namespace MinePlanner{
namespace UI{
/**
* �����ڂ�ύX����@��Ƀt�H���g
* �t�H���g����{��t�H���g�ɂ��Ȃ��Ɠ��{��\���ł��Ȃ��炵��
* �f�t�H�ł������Ăق�������
*/
class MyLookAndFeel : public LookAndFeel
{
public:
	MyLookAndFeel()
	{
		this->setDefaultSansSerifTypefaceName(DEFAULT_FONT_NAME);
	}
	
	virtual const Font getAlertWindowMessageFont()
	{
		return Font(DEFAULT_FONT_NAME,20,Font::plain);
	}
	virtual const Font getAlertWindowFont()
	{
		return Font(DEFAULT_FONT_NAME,18,Font::plain);
	}

	/**
	* TextButton�p�̃t�H���g�ݒ�
	* @param button �ݒ肷��{�^��
	*/
	virtual const Font getFontForTextButton(TextButton& button)
	{
		if(button.getName() == L"ModeButton")
		{
			return Font(DEFAULT_FONT_NAME,20,Font::plain);
		}

		return Font(DEFAULT_FONT_NAME,15,Font::plain);
	}
	virtual const Font getPopupMenuFont()
	{
		return Font(DEFAULT_FONT_NAME,15,Font::plain);
	}
	virtual const Font getMenuBarFont(MenuBarComponent&, int, const String&)
	{
		return Font(DEFAULT_FONT_NAME,15,Font::plain);
	}
	virtual const Font getComboBoxFont(ComboBox&)
	{
		return Font(DEFAULT_FONT_NAME,15,Font::plain);
	}
private:
	static const String DEFAULT_FONT_NAME;
};
}//UI
}//MinePlanner
#endif