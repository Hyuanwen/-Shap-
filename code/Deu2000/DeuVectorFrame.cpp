// DeuVectorFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuVectorFrame.h"
#include "DeuGlobalParam.h"
#include "DeuGlobalMainFrm.h"

// CDeuVectorFrame
IMPLEMENT_DYNCREATE(CDeuVectorFrame, CMDIChildWnd)
CDeuVectorFrame::CDeuVectorFrame()
{
	lstrcpy(sz_ModuleType, "IsVector");
}

CDeuVectorFrame::~CDeuVectorFrame()
{

}

BEGIN_MESSAGE_MAP(CDeuVectorFrame, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CDeuVectorFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//创建面板
	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeOffice);
	//m_paneManager.UseSplitterTracker(FALSE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetAlphaDockingContext(TRUE);

	CXTPDockingPane *p_panel = m_paneManager.CreatePane(ID_VECTORPANEL, CRect(0, 0, 180, 120), xtpPaneDockLeft);

	m_PaneVector.Create(IDD_DLG_PANEL_TAB, this);
	m_PaneVector.MoveWindow(0, 0, 180, 120);
	m_PaneVector.p_View = (CDeuVectorView*)_ViewVectorList.GetAt(_ViewVectorList.GetCount()-1);

	p_panel->Attach(&m_PaneVector);
	p_panel->SetTitle("矢量转换任务");
	p_panel->SetOptions(xtpPaneNoCloseable|xtpPaneNoFloatable|xtpPaneNoDockable);

	//增加对应任务树节点
	::SendMessage(((CDeuGlobalMainFrame*)AfxGetMainWnd())->m_wndTaskPanel.m_hWnd, WM_TASK_VECTOR, NULL, NULL);

	return 0;
}
