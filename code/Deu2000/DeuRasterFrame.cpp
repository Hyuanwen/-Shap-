// DeuRasterFrame.cpp : ʵ���ļ�

#include "stdafx.h"
#include "DeuRasterFrame.h"
#include "DeuGlobalParam.h"
#include "DeuGlobalMainFrm.h"

// CDeuRasterFrame
IMPLEMENT_DYNCREATE(CDeuRasterFrame, CMDIChildWnd)
CDeuRasterFrame::CDeuRasterFrame()
{
	lstrcpy(sz_ModuleType, "IsRaster");
}

CDeuRasterFrame::~CDeuRasterFrame()
{
}

BEGIN_MESSAGE_MAP(CDeuRasterFrame, CMDIChildWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CDeuRasterFrame ��Ϣ�������
int CDeuRasterFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;	
	}

	//�������
	PanelManager.InstallDockingPanes(this);	
	PanelManager.SetTheme(xtpPaneThemeOffice);
	//PanelManager.UseSplitterTracker(FALSE);
	PanelManager.SetShowContentsWhileDragging(TRUE);
	PanelManager.SetAlphaDockingContext(TRUE);
	PanelManager.SetThemedFloatingFrames(TRUE);

	//p_panel = PanelManager.CreatePane(IDR_PANE1, CRect(0, 0, 200,120), xtpPaneDockLeft);
	CXTPDockingPane *p_panel = PanelManager.CreatePane(ID_RASTERPANEL, CRect(0, 0, 180, 120), xtpPaneDockLeft);
	m_PaneRaster.Create(IDD_DLG_PANEL_TAB, this);

	/*
		������2�ִ���취��
			1.�����ӿ��ָ��
				ȱ��: ʹ�ñ�����ͼ���󲻷��㣬�����ƿ��ӿ��ֱ������ͼ������Ϣ

			2.������ͼָ��
				�ô�: ����Ŀ���ȷ�������ȷ������ɶ��Ժ�
	*/
	m_PaneRaster.p_View = (CDeuRasterView*)_ViewRasterList.GetAt(_ViewRasterList.GetCount()-1);
	//m_PaneVector.MoveWindow(0, 0, 180, 120);
	p_panel->Attach(&m_PaneRaster);
	p_panel->SetTitle("դ��ת������");
	p_panel->SetOptions(xtpPaneNoCloseable|xtpPaneNoFloatable|xtpPaneNoDockable);

	//֪ͨ���������Ӷ�Ӧ�ڵ�
	::SendMessage(((CDeuGlobalMainFrame*)AfxGetMainWnd())->m_wndTaskPanel.m_hWnd, WM_TASK_RASTER, NULL, NULL);

	return 0;
}