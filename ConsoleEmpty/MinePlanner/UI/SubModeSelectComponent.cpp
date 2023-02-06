#include "MinePlanner/UI/SubModeSelectComponent.hpp"

#include "MinePlanner/Operation/SelectionManager.hpp"
#include "MinePlanner/Operation/EditManager.hpp"
#include "MinePlanner/Operation/BatchWork.hpp"
#include "MinePlanner/Operation/ClipBoard.hpp"
#include "MinePlanner/Operation/HideBuffer.hpp"

#include "MinePlanner/UI/ReplaceDialog.hpp"
#include "MinePlanner/World.hpp"
#include "MinePlanner/getBlockPose.hpp"

namespace MinePlanner{
namespace UI{
static SubModeSelectComponent* pInstance = 0;
SubModeSelectComponent::SubModeSelectComponent():
 Component()
,m_hide()
,m_show()
,m_replace()
,m_copy()
,m_cut()
,m_paste()
{
	const int LEFT = 5;
	int h = 5;

	//隠す
	m_hide.setText(L"選択範囲を隠す");
	m_hide.setTopLeftPosition(LEFT,h);
	m_hide.addListener(this);
	this->addAndMakeVisible(&m_hide);
	h += m_hide.getHeight();
	h += 5;

	//表示
	m_show.setText(L"表示");
	m_show.setTopLeftPosition(LEFT,h);
	m_show.addListener(this);
	this->addAndMakeVisible(&m_show);
	h += m_show.getHeight();
	h += 15;


	//選択範囲の塗りつぶし
	m_replace.setText(L"選択範囲の一斉置換");
	m_replace.setTopLeftPosition(LEFT,h);
	m_replace.addListener(this);
	this->addAndMakeVisible(&m_replace);
	h += m_replace.getHeight();
	h += 15;

	//コピー
	m_copy.setText(L"コピー");
	m_copy.setToolTip(L"ショートカット : Ctrl + C");
	m_copy.setTopLeftPosition(LEFT,h);
	m_copy.addListener(this);
	m_copy.addShortCut(KeyPress('C',ModifierKeys::ctrlModifier,L''));
	this->addAndMakeVisible(&m_copy);
	h += m_copy.getHeight();
	h += 5;

	//切り取り
	m_cut.setText(L"切り取り");
	m_cut.setToolTip(L"ショートカット : Ctrl + X");
	m_cut.setTopLeftPosition(LEFT,h);
	m_cut.addListener(this);
	m_cut.addShortCut(KeyPress('X',ModifierKeys::ctrlModifier,L''));
	this->addAndMakeVisible(&m_cut);
	h += m_cut.getHeight();
	h += 5;

	//貼り付け
	m_paste.setText(L"貼り付け");
	m_paste.setToolTip(L"ショートカット : Ctrl + V");
	m_paste.setTopLeftPosition(LEFT,h);
	m_paste.addListener(this);
	m_paste.addShortCut(KeyPress('V',ModifierKeys::ctrlModifier,L''));
	this->addAndMakeVisible(&m_paste);
	h += m_paste.getHeight();

	updateDisplay();

	pInstance = this;
}
void SubModeSelectComponent::updateDisplay()
{
	m_hide.setEnabled( g_pSelectionManager()->isSelecting() );
	m_show.setEnabled( g_pHideBuffer()->isHide() );
	m_replace.setEnabled( g_pSelectionManager()->isSelecting() );
	m_copy.setEnabled( g_pSelectionManager()->isSelecting() );
	m_cut.setEnabled( g_pSelectionManager()->isSelecting() );
	m_paste.setEnabled( g_pClipBoard()->hasData() );
}
void SubModeSelectComponent::onMyButtonClicked(Widget::MyButton* arg)
{
	if(&m_hide == arg)
	{
		g_pHideBuffer()->hide();
	}
	else if(&m_show == arg)
	{
		g_pHideBuffer()->show();
	}
	else if(&m_replace == arg)
	{
		if(g_pSelectionManager()->isSelecting())
		{
			UI::ReplaceDialog rd;
			rd.show();

			if(rd.isDecided())
			{
				if(rd.isDelete())
				{
					if(rd.isFill())
					{
						PointSet points = g_pSelectionManager()->getSelectedPoints();
						Operation::Work::ptr work = Operation::BatchWork::createBatchDelete(points);
						g_pEditManager()->dowork(work);
					}
					else
					{
						const int delete_id = rd.getFrom();
						PointSet delete_points = PointSet::create();
						auto get_delete_points = [delete_id,&delete_points](const Point& point)
						{
							if(World::instance().isExist(point)){
								const int id = World::instance().getBlockID(point);
								if(id == delete_id){
									delete_points.add(point);
								}
							}
						};
						PointSet selected_points = g_pSelectionManager()->getSelectedPoints();
						selected_points.for_each(get_delete_points);

						Operation::Work::ptr work = Operation::BatchWork::createBatchDelete(delete_points);
						g_pEditManager()->dowork(work);
					}
				}
				else
				{
					if(rd.isFill())
					{
						PointSet points = g_pSelectionManager()->getSelectedPoints();
						const int to_id = rd.getTo();
						Operation::Work::ptr work = Operation::BatchWork::createBatchFill(points,to_id,getBlockPose(to_id));
						g_pEditManager()->dowork(work);
					}
					else
					{
						PointSet points = g_pSelectionManager()->getSelectedPoints();
						const int to_id = rd.getTo();
						Operation::Work::ptr work = Operation::BatchWork::createBatchReplace(points,rd.getFrom(),to_id,getBlockPose(to_id));
						g_pEditManager()->dowork(work);
					}
				}
			}
		}
	}
	else if(&m_copy == arg)
	{
		g_pClipBoard()->copy();
	}
	else if(&m_cut == arg)
	{
		g_pClipBoard()->cut();
	}
	else if(&m_paste == arg)
	{
		g_pClipBoard()->paste();
	}
}

SubModeSelectComponent* getSubModeSelectComponent()
{
	return pInstance;
}
}//UI
}//MinePlanner