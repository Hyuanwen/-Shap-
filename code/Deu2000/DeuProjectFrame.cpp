// DeuRasterFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuProjectFrame.h"
#include "DeuGlobalParam.h"
#include "DeuGlobalMainFrm.h"

// CDeuProjectFrame
IMPLEMENT_DYNCREATE(CDeuProjectFrame, CMDIChildWnd)
CDeuProjectFrame::CDeuProjectFrame()
{
	lstrcpy(sz_ModuleType, "IsRaster");
}


CDeuProjectFrame::~CDeuProjectFrame()
{
}

BEGIN_MESSAGE_MAP(CDeuProjectFrame, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CDeuProjectFrame 消息处理程序

int CDeuProjectFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;	

	//增加面板
	PanelManager.InstallDockingPanes(this);	
	PanelManager.SetTheme(xtpPaneThemeOffice);
	//PanelManager.UseSplitterTracker(FALSE);
	PanelManager.SetShowContentsWhileDragging(TRUE);
	PanelManager.SetAlphaDockingContext(TRUE);
	PanelManager.SetThemedFloatingFrames(TRUE);

	//p_panel = PanelManager.CreatePane(IDR_PANE1, CRect(0, 0, 200,120), xtpPaneDockLeft);
	CXTPDockingPane *p_panel = PanelManager.CreatePane(ID_RASTERPANEL, CRect(0, 0, 180, 120), xtpPaneDockLeft);
	m_PaneProject.Create(IDD_DLG_PANEL_TAB, this);

	/*
		这里有2种处理办法：
			1.传入子框架指针
				缺点: 使用遍历视图对象不方便，所以绕开子框架直接与视图交互消息

			2.传入视图指针
				好处: 对象目标的确定简洁明确，代码可读性好
	*/
	m_PaneProject.p_View = (CDeuProjectView*)_ViewRasterList.GetAt(_ViewRasterList.GetCount()-1);

	//m_PaneVector.MoveWindow(0, 0, 180, 120);
	p_panel->Attach(&m_PaneProject);
	p_panel->SetTitle("投影转换任务");
	p_panel->SetOptions(xtpPaneNoCloseable|xtpPaneNoFloatable|xtpPaneNoDockable);

	//通知任务树增加对应节点
	::SendMessage(((CDeuGlobalMainFrame*)AfxGetMainWnd())->m_wndTaskPanel.m_hWnd, WM_TASK_RASTER, NULL, NULL);

	return 0;
}