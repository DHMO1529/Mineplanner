#ifndef MINEPLANNER_UI_WIDGET_MYNUMERICUPDOWN
#define MINEPLANNER_UI_WIDGET_MYNUMERICUPDOWN
#include <juce.h>
namespace MinePlanner{
namespace UI{
namespace Widget{
class MyNumericUpDown : public Component,
	public SettableTooltipClient,
												public KeyListener
{
public:
	//true���Ə㉺�L�[�ɔ�������
	MyNumericUpDown(bool isRedistKeyEventCatch = false);
	~MyNumericUpDown();
	
	void setText(const String& text);
	void setToolTip(const String& tooltip);
	void setRange(int min,int max);
	void setLabelColour(int colourId,const Colour& colour);

	void setValue(int value);
	int getValue()const;

	void referTo(const Value& value_double);

	//�����R�[���o�b�N
	virtual bool keyPressed(const KeyPress& key,Component*);
private:
	void upValue();
	void downValue();

	Label m_label;
	Slider m_slider;
};
}//Widget
}//UI
}//MinePlanner
#endif