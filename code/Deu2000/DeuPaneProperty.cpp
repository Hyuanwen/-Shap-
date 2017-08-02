#include "stdafx.h"
#include "DeuPaneProperty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/********************************************

			属性任务树

*********************************************/

IMPLEMENT_DYNAMIC(CDeuPanelPropertyTree, CWnd)
CDeuPanelPropertyTree::CDeuPanelPropertyTree()
{

}

CDeuPanelPropertyTree::~CDeuPanelPropertyTree()
{
}

BEGIN_MESSAGE_MAP(CDeuPanelPropertyTree, CWnd)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CDeuPanelPropertyTree::OnSetFocus(CWnd* pOldWnd)
{
	//CWnd::OnSetFocus(pOldWnd);
	m_wndSolutionView.SetFocus();
}

void CDeuPanelPropertyTree::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	int nTop = 0;

	if (m_wndSolutionView.GetSafeHwnd())
	{
		m_wndSolutionView.MoveWindow(0, nTop, cx, cy - nTop);
		m_wndSolutionView.Invalidate(FALSE);
	}
}

int CDeuPanelPropertyTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	if (m_wndSolutionView.GetSafeHwnd() == 0)
	{
		if (!m_wndSolutionView.Create( WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
			CRect(0,0,0,0), this, 0xFF ))
		{
			TRACE0( "Unable to create tree control.\n" );
			return 0;
		}

		if (!CreateImageList(m_ilSolutionView, IDB_TREEIMG))
		{
			return 0;
		}

		m_wndSolutionView.SetImageList(&m_ilSolutionView, TVSIL_NORMAL);

		//创建树数据
		HTREEITEM htiParent = m_wndSolutionView.InsertItem(_T("数据"), 1, 1, TVI_ROOT);
		m_wndSolutionView.SetItemState (htiParent, TVIS_BOLD, TVIS_BOLD);

		//增加子节点
		m_wndSolutionView.InsertItem(_T("LoadData.xml"),1, 1, htiParent);
		m_wndSolutionView.Expand(htiParent, TVE_EXPAND);

		m_wndSolutionView.Expand(htiParent, TVE_EXPAND);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDeuPaneProperty dialog
CDeuPaneProperty::CDeuPaneProperty(CWnd* pParent /*=NULL*/)
	: CXTPDialog(CDeuPaneProperty::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeuPaneProperty::DoDataExchange(CDataExchange* pDX)
{
	CXTPDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDeuPaneProperty, CXTPDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeuPaneProperty message handlers
BOOL CDeuPaneProperty::OnInitDialog()
{
	CXTPDialog::OnInitDialog();

	VERIFY(m_paneManager.InstallDockingPanes(this));
	m_paneManager.SetTheme(xtpPaneThemeOffice2003);
	m_paneManager.UseSplitterTracker(FALSE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetAlphaDockingContext(TRUE);

	// Create docking panes.
	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(IDR_PANE1, CRect(0, 0, 250, 150), xtpPaneDockTop);
	pwndPane1->SetOptions(xtpPaneNoCaption|xtpPaneNoHideable|xtpPaneNoCloseable|xtpPaneNoFloatable|xtpPaneNoDockable);

	if (m_wndPropertyGrid.GetSafeHwnd() == 0)
	{
		m_wndPropertyGrid.Create( CRect(0, 0, 0, 0), this, 0 );
		m_wndPropertyGrid.SetOwner(this);
		m_wndPropertyGrid.SetTheme(xtpGridThemeWhidbey);

		CFont font;
		font.CreatePointFont(60, _T("Marlett"));

		LOGFONT lf;
		font.GetLogFont(&lf);

		// create custom items category.
		CXTPPropertyGridItem* pCustom   = m_wndPropertyGrid.AddCategory(_T("属性"));				

		// add multi level tree node.
		CXTPPropertyGridItem* pItemOne    = pCustom->AddChildItem(new CXTPPropertyGridItem(_T("显示名称"), _T("")));
		CXTPPropertyGridItem* pItemTwo    = pCustom->AddChildItem(new CXTPPropertyGridItem(_T("描述"), _T("")));
		CXTPPropertyGridItem* pItemThree  = pCustom->AddChildItem(new CXTPPropertyGridItem(_T("类型"), _T("")));		
		
		pCustom->Expand();
		m_wndPropertyGrid.HighlightChangedItems(TRUE);
	}

	return TRUE;
}

void CDeuPaneProperty::OnSysCommand(UINT nID, LPARAM lParam)
{	
	CXTPDialog::OnSysCommand(nID, lParam);	
}

void CDeuPaneProperty::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CXTPDialog::OnPaint();
	}
}

HCURSOR CDeuPaneProperty::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDeuPaneProperty::OnSize(UINT nType, int cx, int cy) 
{
	CXTPDialog::OnSize(nType, cx, cy);
	
	CRect rcClient(0, 0, cx, cy);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, 0, 0, &rcClient);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rcClient, &rcClient);

	if (m_wndPropertyGrid.GetSafeHwnd())
	{
		//m_wndPropertyGrid.MoveWindow(0, nTop, cx, cy - nTop);
		m_wndPropertyGrid.MoveWindow(rcClient);
		m_wndPropertyGrid.Invalidate(FALSE);
	}
}

LRESULT CDeuPaneProperty::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			switch(pPane->GetID())
			{
			case IDR_PANE1:
				m_wndTaskPanel.Create(_T("STATIC"), NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CXTPEmptyRect(), this, 0);
				pPane->Attach(&m_wndTaskPanel);
				break;
			default:
				int nIndex = pPane->GetID() - IDR_PANE1;
				ASSERT(nIndex >=0 &&  nIndex < sizeof(m_wndEdit) / sizeof(m_wndEdit[0]));
				CEdit& wndEdit = m_wndEdit[nIndex];

				// create and attach the edit control for this pane.
				if (!::IsWindow(wndEdit.m_hWnd))
				{
					if (!wndEdit.CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""),
						WS_CHILD|ES_AUTOVSCROLL|ES_MULTILINE|ES_WANTRETURN, CRect(0, 0,250, 120), this, pPane->GetID()))
					{
						TRACE0( "Error creating pane edit control.\n" );
					}
					wndEdit.SetFont(&m_fntEdit);
				}

				pPane->Attach(&wndEdit);
				break;
			}
		}

		return TRUE; // handled
	}

	return FALSE;
}



