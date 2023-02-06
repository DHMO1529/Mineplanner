#include "MinePlanner/UI/ModelImportDialog.hpp"

#include <sstream>

#include "MinePlanner/UI/MainWindow.hpp"
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace UI{
const int MAX_SIZE = 256;
ModelImportDialog::ModelImportDialog(const std::string& targetFilename):
 DialogWindow(L"モデル読み込み設定",Colours::lightgrey,false)
,m_component()
,m_targetFileLabel()
,m_targetFile()
,m_size()
,m_decide()
,m_decided(false)
{
	m_component.setSize(300,170);

	int h = 0;

	h += 10;
	m_targetFileLabel.setBounds(5,h,280,30);
	m_targetFileLabel.setText(L"対象ファイル名",false);
	m_component.addAndMakeVisible(&m_targetFileLabel);
	h += m_targetFileLabel.getHeight();

	m_targetFile.setReadOnly(true);

	m_targetFile.setSize(280,25);
	m_targetFile.setTopLeftPosition(10,h);
	m_targetFile.setText(string_cast<String,std::string>(targetFilename));
	m_component.addAndMakeVisible(&m_targetFile);
	h += m_targetFile.getHeight();

	h += 10;
	m_size.setText(L"サイズ");
	m_size.setValue(32);
	m_size.setTopLeftPosition(10,h);
	m_size.setRange(1,MAX_SIZE);
	m_component.addAndMakeVisible(&m_size);
	h += m_size.getHeight();

	h += 15;
	m_decide.setText(L"読み込み開始");
	m_decide.addListener(this);
	m_decide.setTopLeftPosition(100,h);
	m_component.addAndMakeVisible(&m_decide);

	this->setContentOwned(&m_component,true);
}
ModelImportDialog::~ModelImportDialog()
{
}
void ModelImportDialog::closeButtonPressed()
{
	this->setVisible(false);
}
void ModelImportDialog::onMyButtonClicked(Widget::MyButton*)
{
	if(m_size.getValue() > 150)
	{
		//大杉ないか？を一応確認
		bool result = NativeMessageBox::showOkCancelBox(
			AlertWindow::QuestionIcon,
			L"注意",
			L"非常に大きなサイズはＰＣスペックによっては、\n不安定な動作を引き起こす可能性があります。\n続行しますか？");
		if(!result)
		{
			return;
		}
	}
	m_decided = true;
	this->setVisible(false);
}
void ModelImportDialog::show()
{
	const int x = UI::getWindowX();
	const int y = UI::getWindowY();
	this->setTopLeftPosition(x+200,y+100);

	this->runModalLoop();
}
bool ModelImportDialog::isDecided()const
{
	return m_decided;
}
int ModelImportDialog::getSize()const
{
	return m_size.getValue();
}
}//UI
}//MinePlanner