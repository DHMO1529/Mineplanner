#ifndef MINEPLANNER_UI_MODELIMPORTDIALOG
#define MINEPLANNER_UI_MODELIMPORTDIALOG
#include <string>
#include <juce.h>
#include "MinePlanner/UI/Widget/MyNumericUpDown.hpp"
#include "MinePlanner/UI/Widget/MyButton.hpp"
#include "MinePlanner/UI/Widget/BlockTypeComboBox.hpp"
namespace MinePlanner{
namespace UI{
class ModelImportDialog : public DialogWindow,
										 public Widget::MyButton::MyListener
{
public:
	ModelImportDialog(const std::string& targetFilename);
	~ModelImportDialog();

	virtual void closeButtonPressed();
	virtual void onMyButtonClicked(Widget::MyButton*);

	void show();
	bool isDecided()const;

	int getSize()const;
private:
	Component m_component;
	Label m_targetFileLabel;
	TextEditor m_targetFile;
	Widget::MyNumericUpDown m_size;
	Widget::MyButton m_decide;
	bool m_decided;
};
}//UI
}//MinePlanner
#endif