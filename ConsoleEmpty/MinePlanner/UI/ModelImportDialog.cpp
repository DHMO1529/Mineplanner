#include "MinePlanner/UI/ModelImportDialog.hpp"

#include <sstream>

#include "MinePlanner/UI/MainWindow.hpp"
#include "MinePlanner/string_cast.hpp"
namespace MinePlanner{
namespace UI{
const int MAX_SIZE = 256;
ModelImportDialog::ModelImportDialog(const std::string& targetFilename):
 DialogWindow(L"���f���ǂݍ��ݐݒ�",Colours::lightgrey,false)
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
	m_targetFileLabel.setText(L"�Ώۃt�@�C����",false);
	m_component.addAndMakeVisible(&m_targetFileLabel);
	h += m_targetFileLabel.getHeight();

	m_targetFile.setReadOnly(true);

	m_targetFile.setSize(280,25);
	m_targetFile.setTopLeftPosition(10,h);
	m_targetFile.setText(string_cast<String,std::string>(targetFilename));
	m_component.addAndMakeVisible(&m_targetFile);
	h += m_targetFile.getHeight();

	h += 10;
	m_size.setText(L"�T�C�Y");
	m_size.setValue(32);
	m_size.setTopLeftPosition(10,h);
	m_size.setRange(1,MAX_SIZE);
	m_component.addAndMakeVisible(&m_size);
	h += m_size.getHeight();

	h += 15;
	m_decide.setText(L"�ǂݍ��݊J�n");
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
		//�吙�Ȃ����H���ꉞ�m�F
		bool result = NativeMessageBox::showOkCancelBox(
			AlertWindow::QuestionIcon,
			L"����",
			L"���ɑ傫�ȃT�C�Y�͂o�b�X�y�b�N�ɂ���ẮA\n�s����ȓ���������N�����\��������܂��B\n���s���܂����H");
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