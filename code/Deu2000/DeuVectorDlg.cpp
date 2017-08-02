// XTPDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuVectorDlg.h"









// CXTPDialog 对话框

IMPLEMENT_DYNAMIC(CDeuVectorDlg, CXTPDialog)

CDeuVectorDlg::CDeuVectorDlg(CWnd* pParent /*=NULL*/)
	: CXTPDialog(CDeuVectorDlg::IDD, pParent)
{

}

CDeuVectorDlg::~CDeuVectorDlg()
{
}

void CDeuVectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDeuVectorDlg, CXTPDialog)
	ON_WM_SIZE()
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
END_MESSAGE_MAP()


// CXTPDialog 消息处理程序

BOOL CDeuVectorDlg::OnInitDialog()
{
	CXTPDialog::OnInitDialog();

	////创建面板
	//m_paneManager.InstallDockingPanes(this);
	//m_paneManager.SetTheme(xtpPaneThemeNativeWinXP);
	//m_paneManager.UseSplitterTracker(FALSE);
	//m_paneManager.SetShowContentsWhileDragging(TRUE);
	////m_paneManager.SetAlphaDockingContext(TRUE);

	//CXTPDockingPane *p_panel = m_paneManager.CreatePane(ID_VECTORPANEL, CRect(0, 0, 180, 120), xtpPaneDockLeft);
	

	//创建TabCtrl
	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, IDC_TAB1);
	m_wndTabControl.SetOwner(this);
	m_wndTabControl.GetPaintManager()->SetAppearance(xtpTabAppearancePropertyPage2003);
	m_wndTabControl.GetPaintManager()->m_bHotTracking = TRUE;
	m_wndTabControl.GetPaintManager()->m_bShowIcons = TRUE;	
	m_wndTabControl.GetPaintManager()->DisableLunaColors(FALSE);
	m_wndTabControl.ShowCloseItemButton();

	for(int n=0; n<2; n++)
	{
		m_wndTabControl.InsertItem(n, "Test1");
	}

	return TRUE;
}



void CDeuVectorDlg::OnSize(UINT nType, int cx, int cy)
{
	CXTPDialog::OnSize(nType, cx, cy);

	CRect rcClient(0, 0, cx, cy);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, 0, 0, &rcClient);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rcClient, &rcClient);

	if(m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(rcClient);
	}

}



LRESULT CDeuVectorDlg::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{		
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			switch(pPane->GetID())
			{
			case ID_VECTORPANEL:
				m_PaneVector.Create(IDD_DLG_PANELVECTOR, this);
				m_PaneVector.MoveWindow(0, 0, 180, 120);
				pPane->Attach(&m_PaneVector);
				break;

			//default:

			//	int nIndex = pPane->GetID() - IDR_PROPERTYPANE;
			//	//int nIndex = 6;
			//	ASSERT(nIndex >=0 &&  nIndex < sizeof(m_wndPanes) / sizeof(m_wndPanes[0]));

			//	// create and attach the edit control for this pane.
			//	if (!::IsWindow(m_wndPanes[nIndex].m_hWnd))
			//	{
			//		if (!m_wndPanes[nIndex].CreateEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
			//			WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE, CRect(0, 0, 200, 120), this, 0))
			//		{
			//			TRACE0( "Error creating pane edit control.\n" );
			//		}
			//		//AdjustStyle(GetDockingPaneManager()->GetCurrentTheme());
			//	}
			//	pPane->Attach(&m_wndPanes[nIndex]);
			//	break;
			}
		}        

		return TRUE; // handled
	}
	return FALSE;
}
