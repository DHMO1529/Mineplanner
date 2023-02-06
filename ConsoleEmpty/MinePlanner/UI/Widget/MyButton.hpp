#ifndef MINEPLANNER_UI_WIDGET_MYBUTTON
#define MINEPLANNER_UI_WIDGET_MYBUTTON
#include <juce.h>
#include <vector>
namespace MinePlanner{
namespace UI{
namespace Widget{
class MyButton : public Component,public Button::Listener
{
public:
	class MyListener
	{
	public:
		virtual void onMyButtonClicked(MyButton*) = 0;
	};

	MyButton();
	void setText(const String& text);
	void setToolTip(const String& tooltip);
	void addListener(MyListener* listener);
	void addShortCut(const KeyPress& key);

	//�I�[�o�[���C�h�ł͂Ȃ����Ǐ㏑��
	void setColour(int colourId,const Colour& colour);

	//�R�[���o�b�N�@�g�p�҂͋C�ɂ��Ȃ�
	virtual void buttonClicked(Button* button);
private:
	TextButton m_button;
	typedef std::vector<MyListener*> Listeners;
	Listeners m_listeners;
};
}//Widget
}//UI
}//MinePlanner
#endif