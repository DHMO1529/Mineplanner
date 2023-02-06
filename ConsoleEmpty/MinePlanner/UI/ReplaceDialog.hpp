#ifndef MINEPLANNER_UI_REPLACEDIALOG
#define MINEPLANNER_UI_REPLACEDIALOG
#include <juce.h>
#include "MinePlanner/UI/Widget/BlockTypeComboBox.hpp"
#include "MinePlanner/UI/Widget/MyButton.hpp"
#include "MinePlanner/UI/Widget/MyCheckButton.hpp"
namespace MinePlanner{
namespace UI{
class ReplaceDialog : public DialogWindow,
										  public Widget::MyButton::MyListener,
											public Value::Listener
{
public:
	ReplaceDialog();
	~ReplaceDialog();

	virtual void closeButtonPressed();
	virtual void onMyButtonClicked(Widget::MyButton*);

	void show();
	bool isDecided()const;

	bool isFill()const;//塗りつぶしモード？
	bool isDelete()const;//消すモード？

	int getFrom()const;
	int getTo()const;

	virtual void valueChanged(Value& value);
private:
	Component m_component;
	Widget::BlockTypeComboBox m_blockTypeFrom;
	Widget::MyCheckButton m_fill;
	Value m_isFill;

	Widget::BlockTypeComboBox m_blockTypeTo;
	Widget::MyCheckButton m_delete;
	Value m_isDelete;

	Widget::MyButton m_decide;

	bool m_decided;
};
}//UI
}//MinePlanner
#endif