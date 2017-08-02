// DeuVectorProjectFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuVectorProjectFrame.h"
#include "DeuGlobalParam.h"
#include "DeuGlobalMainFrm.h"

// CDeuVectorProjectFrame
IMPLEMENT_DYNCREATE(CDeuVectorProjectFrame, CMDIChildWnd)
CDeuVectorProjectFrame::CDeuVectorProjectFrame()
{
	lstrcpy(sz_ModuleType, "IsVector");
}

CDeuVectorProjectFrame::~CDeuVectorProjectFrame()
{
}

BEGIN_MESSAGE_MAP(CDeuVectorProjectFrame, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CDeuVectorProjectFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	m_PaneVectorProject.Create(IDD_DLG_PANEL_TAB, this);
	m_PaneVectorProject.MoveWindow(0, 0, 180, 120);
	m_PaneVectorProject.p_View = (CDeuVectorProjectView*)_ViewVectorList.GetAt(_ViewVectorList.GetCount()-1);

	p_panel->Attach(&m_PaneVectorProject);
	p_panel->SetTitle("矢量投影任务");
	p_panel->SetOptions(xtpPaneNoCloseable|xtpPaneNoFloatable|xtpPaneNoDockable);
		
	//增加对应任务树节点
	::SendMessage(((CDeuGlobalMainFrame*)AfxGetMainWnd())->m_wndTaskPanel.m_hWnd, WM_TASK_VECTOR, NULL, NULL);

	return 0;
}
