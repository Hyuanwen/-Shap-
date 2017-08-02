// DeuDataSrcDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "DeuDlgDataSrc.h"
#include "DeuGlobal.h"
#include "DeuDlgDataSrcDetail.h"
#include "DeuTaskProcess.h"

IMPLEMENT_DYNAMIC(CDeuDlgDataSrc, CDialogSampleDlgBase)

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL
};

CDeuDlgDataSrc::CDeuDlgDataSrc(CWnd* pParent /*=NULL*/) 
	          : CDialogSampleDlgBase(CDeuDlgDataSrc::IDD, pParent)
{
}

CDeuDlgDataSrc::~CDeuDlgDataSrc()
{
}

void CDeuDlgDataSrc::DoDataExchange(CDataExchange* pDX)
{
	CDialogSampleDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UROLE_SRC, m_Listctrl);	
	DDX_Control(pDX, IDC_TREE1, m_Treectrl);	
}

BEGIN_MESSAGE_MAP(CDeuDlgDataSrc, CDialogSampleDlgBase)
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CDeuDlgDataSrc::OnNMRClickTree1)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CDeuDlgDataSrc::OnNMClickTree1)	
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_UROLE_SRC, &CDeuDlgDataSrc::OnNMDblclkListUroleSrc)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_UROLE_SRC, &CDeuDlgDataSrc::OnNMRClickListUroleSrc)
	ON_COMMAND(ID_DATA_DETAIL, OnShowDetail)
END_MESSAGE_MAP()

// CDeuDlgDataSrc ��Ϣ�������
BOOL CDeuDlgDataSrc::OnInitDialog()
{
	CDialogSampleDlgBase::OnInitDialog();
	
	//m_XmlReader.LoadXml("geodata.xml");

	//if (!m_wndStatusBar.Create(this) ||
	//	!m_wndStatusBar.SetIndicators(indicators,
	//	sizeof(indicators)/sizeof(UINT)))
	//{
	//	TRACE0("Failed to create status bar\n");
	//	return -1;      // fail to create
	//}
	//m_wndStatusBar.SetPaneInfo(0, ID_SEPARATOR, SBPS_STRETCH, 100);

	//VERIFY(InitCommandBars());
	//CXTPCommandBars* pCommandBars = GetCommandBars();
	//CXTPToolBar* pToolBar = pCommandBars->Add(_T("Standard"), xtpBarTop);
	//pToolBar->LoadToolBar(IDR_TOOLBAR1);

	this->SetResize(IDC_TREE1, SZ_TOP_LEFT, SZ_BOTTOM_LEFT);
	this->SetResize(IDC_LIST_UROLE_SRC, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	
	m_Listctrl.ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	DWORD dwStyle = m_Listctrl.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
	m_Listctrl.SetExtendedStyle(dwStyle);

	/*VERIFY(m_paneManager.InstallDockingPanes(this));
	m_paneManager.SetTheme(xtpPaneThemeOffice2003);
	m_paneManager.UseSplitterTracker(FALSE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetAlphaDockingContext(TRUE);

	CXTPDockingPane* pwndPane1 = m_paneManager.CreatePane(
		IDR_PANE1, CRect(50, 0,200, 120), xtpPaneDockLeft);
	
	pwndPane1->SetOptions(xtpPaneNoCaption|xtpPaneNoFloatable|xtpPaneNoCloseable|xtpPaneNoDockable);*/

	RefreshTreeCtrl();

	////GeoCentric --- �ռ�ֱ������
	//HTREEITEM hTreeGeoCentric = m_Treectrl.InsertItem("�ռ�ֱ������", hTree);
	//m_Treectrl.InsertItem("ȫ������", hTreeGeoCentric);
	//m_Treectrl.InsertItem("���ʹ������", hTreeGeoCentric);
	//m_Treectrl.Expand(hTreeGeoCentric, TVE_EXPAND);
	//m_treelist.push_back(hTreeGeoCentric);

	m_menu.LoadMenu(IDR_MENUCONTEXT);
	InitListCtrl(All);
	FillListCtrl(All);
	m_Listctrl.DeleteColumn(4);
	m_Listctrl.DeleteColumn(4);

	return TRUE;
}

void CDeuDlgDataSrc::OnSize(UINT nType, int cx, int cy)
{
	CDialogSampleDlgBase::OnSize(nType, cx, cy);

	/*CRect rcClient(150, 0, cx, cy);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, 0, 0, &rcClient);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rcClient, &rcClient);

	if (m_Listctrl.GetSafeHwnd())
	{
		m_Listctrl.MoveWindow(rcClient);
	}*/
}

// ���ؼ��Ҽ��˵�
void CDeuDlgDataSrc::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint m_point;
	::GetCursorPos(&m_point);	
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);

	*pResult = 0;
}

//�������ڵ�
void CDeuDlgDataSrc::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	DWORD         dwpos = GetMessagePos();
	TVHITTESTINFO ht = {0};   
	ht.pt.x = GET_X_LPARAM(dwpos);
	ht.pt.y = GET_Y_LPARAM(dwpos);
	::MapWindowPoints(HWND_DESKTOP,pNMHDR->hwndFrom, &ht.pt, 1); //����Ļ����ת���ɿؼ�����
	TreeView_HitTest(pNMHDR->hwndFrom, &ht);				     //ȷ�����������һ��

	if(ht.hItem == hTreeGeoDetic)
	{
		m_Listctrl.DeleteAllItems();
		InitListCtrl(GeoDetic);
		FillListCtrl(GeoDetic);

		hTreeHandle = hTreeGeoDetic;
	}
	else if(ht.hItem == hTreeProjected)
	{
		m_Listctrl.DeleteAllItems();
		InitListCtrl(GeoProjected);
		FillListCtrl(GeoProjected);

		hTreeHandle = hTreeProjected;
	}
	/*else if(m_Treectrl.GetParentItem(ht.hItem) == hTreeGeoDetic)
	{
		m_Listctrl.DeleteAllItems();
		InitListCtrl(GeoProjected);
		DWORD dwType = m_Treectrl.GetItemData(ht.hItem);
		switch(dwType)
		{
		case 54:
			LoadGeodeticPeking54Data();
			break;
		case 80:
			LoadGeodeticXiAn80Data();
			break;
		case 84:
			LoadGeodeticWGS84Data();
			break;
		case 2000:
			LoadGeodeticCGCS2000Data();
			break;
		}
	}*/
	else if(m_Treectrl.GetParentItem(ht.hItem) == hTreeProjected)
	{
		m_Listctrl.DeleteAllItems();
		InitListCtrl(GeoProjected);
		DWORD dwType = m_Treectrl.GetItemData(ht.hItem);		
		LoadSelectedPorjected(m_Treectrl.GetItemText(ht.hItem));

		hTreeHandle = hTreeProjected;
	}
	else
	{
		InitListCtrl(All);
		FillListCtrl(All);
		m_Listctrl.DeleteColumn(4);
		m_Listctrl.DeleteColumn(4);

		hTreeHandle = hTreeRoot;
	}
}

//GeoDetic --- �������
void CDeuDlgDataSrc::InitListCtrl(CoordinateType _CoodinateType)
{
	switch(_CoodinateType)
	{
	case GeoDetic:		//�������
		{
			m_Listctrl.DeleteAllItems();
			m_Listctrl.InsertColumn(0, _T("���"), LVCFMT_LEFT, 50);
			m_Listctrl.InsertColumn(1, _T("�����������"), LVCFMT_LEFT, 100);
			m_Listctrl.InsertColumn(2, _T("��Χ"), LVCFMT_LEFT, 100);
			m_Listctrl.InsertColumn(3, _T("������"), LVCFMT_LEFT, 200);
			m_Listctrl.InsertColumn(4, _T("��ػ�׼"), LVCFMT_LEFT, 80);
			m_Listctrl.InsertColumn(5, _T("����ϵ����"), LVCFMT_LEFT, 80);
			m_Listctrl.InsertColumn(6, _T("��ע"), LVCFMT_LEFT, 80);			
		}
		break;

	case GeoProjected:	//ͶӰ����
		{			
			//����ListCtrlͷ
			int n = m_Listctrl.GetHeaderCtrl()->GetItemCount();
			while(n >= 0)
			{
				m_Listctrl.DeleteColumn(n-1);
				n--;
			}
			m_Listctrl.InsertColumn(0, _T("���"), LVCFMT_LEFT, 50);
			m_Listctrl.InsertColumn(1, _T("ͶӰ����ϵ"), LVCFMT_LEFT, 100);
			m_Listctrl.InsertColumn(2, _T("��Χ"), LVCFMT_LEFT, 100);
			m_Listctrl.InsertColumn(3, _T("������"), LVCFMT_LEFT, 200);
			m_Listctrl.InsertColumn(4, _T("���"), LVCFMT_LEFT, 80);
			m_Listctrl.InsertColumn(5, _T("����ϵ����"), LVCFMT_LEFT, 80);
			m_Listctrl.InsertColumn(6, _T("��ע"), LVCFMT_LEFT, 80);	
		}
		break;

	case GeoCentic:		//�ռ�ֱ������
		{
			m_Listctrl.DeleteAllItems();

			//����ListCtrlͷ
			int n = m_Listctrl.GetHeaderCtrl()->GetItemCount();
			while(n >= 0)
			{
				m_Listctrl.DeleteColumn(n-1);
				n--;
			}
		}
		break;

	default:
		{
			//����ListCtrlͷ
			int n = m_Listctrl.GetHeaderCtrl()->GetItemCount();
			while(n >= 0)
			{
				m_Listctrl.DeleteColumn(n-1);
				n--;
			}
			m_Listctrl.InsertColumn(0, _T("���"), LVCFMT_LEFT, 50);
			m_Listctrl.InsertColumn(1, _T("����ϵ����"), LVCFMT_LEFT, 120);
			m_Listctrl.InsertColumn(2, _T("��Χ"), LVCFMT_LEFT, 200);
			m_Listctrl.InsertColumn(3, _T("������"), LVCFMT_LEFT, 200);
			m_Listctrl.InsertColumn(4, _T(""), LVCFMT_LEFT, 0);
			m_Listctrl.InsertColumn(5, _T(""), LVCFMT_LEFT, 0);
			m_Listctrl.InsertColumn(6, _T("��ע"), LVCFMT_LEFT, 80);
		}
		break;
	}
}

//������ݵ��б�
void CDeuDlgDataSrc::FillListCtrl(CoordinateType _CoodinateType)
{
	CString str;

	switch(_CoodinateType)
	{
	case GeoDetic:		//�������
		{
			m_Listctrl.DeleteAllItems();
			int nCount = this->m_Listctrl.GetItemCount();
			for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
			{		 
				str.Format("%d", (nCount+1));
				m_Listctrl.InsertItem(nCount, NULL);
				m_Listctrl.SetItemText(nCount, 0, str);
				m_Listctrl.SetItemText(nCount, 1, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
				m_Listctrl.SetItemText(nCount, 2, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
				m_Listctrl.SetItemText(nCount, 3, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
				m_Listctrl.SetItemText(nCount, 4, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
				m_Listctrl.SetItemText(nCount, 5, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
				m_Listctrl.SetItemText(nCount, 6, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);	
				nCount++;
			}
		}
		break;

	case GeoProjected:	//ͶӰ����
		{
			m_Listctrl.DeleteAllItems();
			int nCount = this->m_Listctrl.GetItemCount();
			for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
			{
				str.Format("%d", (nCount+1));
				m_Listctrl.InsertItem(nCount, NULL);
				m_Listctrl.SetItemText(nCount, 0, str);
				m_Listctrl.SetItemText(nCount, 1, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text);
				m_Listctrl.SetItemText(nCount, 2, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._name.text);
				m_Listctrl.SetItemText(nCount, 3, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._pointStyle._name.text);
				m_Listctrl.SetItemText(nCount, 4, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text);
				m_Listctrl.SetItemText(nCount, 5, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._projection.text);
				m_Listctrl.SetItemText(nCount, 6, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._remark.text);
				nCount++;
			}
		}
		break;

	case GeoCentic:		//�ռ�ֱ������
		{
			//����
		}
		break;
	default:
		m_Listctrl.DeleteAllItems();
		LoadGeodeticPeking54Data();
		LoadGeodeticXiAn80Data();
		LoadGeodeticWGS84Data();
		LoadGeodeticCGCS2000Data();
		LoadAllPorjected();
		break;
	}
}

void CDeuDlgDataSrc::LoadGeodeticPeking54Data()
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._tranStandard == Peking54)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
			m_Listctrl.SetItemText(nCount, 5, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
			m_Listctrl.SetItemText(nCount, 6, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);
			nCount++;
		}
	}
}

void CDeuDlgDataSrc::LoadGeodeticXiAn80Data()
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._tranStandard == XiAn80)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
			m_Listctrl.SetItemText(nCount, 5, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
			m_Listctrl.SetItemText(nCount, 6, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);
			nCount++;
		}
	}
}

void CDeuDlgDataSrc::LoadGeodeticWGS84Data()
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._tranStandard == WGS84)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
			m_Listctrl.SetItemText(nCount, 5, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
			m_Listctrl.SetItemText(nCount, 6, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);
			nCount++;
		}
	}
}

void CDeuDlgDataSrc::LoadGeodeticCGCS2000Data()
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{		 
		if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._tranStandard == CGCS2000)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
			m_Listctrl.SetItemText(nCount, 5, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
			m_Listctrl.SetItemText(nCount, 6, GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);
			nCount++;		
		}
	}
}

void CDeuDlgDataSrc::OnClose()
{
	CXTPDialogBase<CXTResizeDialog>::OnClose();
}

//˫��CListCtrlĳ����¼
void CDeuDlgDataSrc::OnNMDblclkListUroleSrc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if(pNMItemActivate->iItem != -1){
		m_strSelectItem = m_Listctrl.GetItemText(pNMItemActivate->iItem, 1);
		this->OnOK();
	}

	*pResult = 0;
}

void CDeuDlgDataSrc::OnNMRClickListUroleSrc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if(pNMItemActivate->iItem != -1)
	{
		CPoint pt;
		::GetCursorPos(&pt);
		m_menu.GetSubMenu(1)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}

void CDeuDlgDataSrc::OnShowDetail()
{
	CDeuDlgDataSrcDetail m_Dlg;
	m_Dlg.m_Name = m_Listctrl.GetItemText(m_Listctrl.GetSelectionMark(), 1);
	CDeuTaskProcess task;
	char *sz_Type = task.FindCoordType(m_Dlg.m_Name); 
	if(StrCmp(sz_Type, "1") == 0)      //GEODETIC
	{
		m_Dlg._coordtype = GeoDetic;	
	}
	else if(StrCmp(sz_Type, "3") == 0) //PLANE
	{
		m_Dlg._coordtype = GeoProjected;
	}
	else
	{
		m_Dlg._coordtype = All;
	}
	
	m_Dlg.DoModal();
}

void CDeuDlgDataSrc::LoadSelectedPorjected(CString strGeoDetic)
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		if(GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text == strGeoDetic)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text);
			m_Listctrl.SetItemText(nCount, 5, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._projection.text);
			m_Listctrl.SetItemText(nCount, 6, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._remark.text);
			nCount++;
		}
	}
}

void CDeuDlgDataSrc::LoadAllPorjected()
{
	m_Listctrl.DeleteAllItems();

	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<GeoDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		str.Format("%d", (nCount+1));
		m_Listctrl.InsertItem(nCount, NULL);
		m_Listctrl.SetItemText(nCount, 0, str);
		m_Listctrl.SetItemText(nCount, 1, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text);
		m_Listctrl.SetItemText(nCount, 2, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._name.text);
		m_Listctrl.SetItemText(nCount, 3, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._pointStyle._name.text);
		m_Listctrl.SetItemText(nCount, 4, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text);
		m_Listctrl.SetItemText(nCount, 5, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._projection.text);
		m_Listctrl.SetItemText(nCount, 6, GeoDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._remark.text);
		nCount++;
	}
}

//ˢ����Ŀ¼
void CDeuDlgDataSrc::RefreshTreeCtrl()
{
	m_Treectrl.DeleteAllItems();

	HTREEITEM hItemTmp;
	hTreeRoot = m_Treectrl.InsertItem("����ϵͳ", TVI_ROOT);
	m_Treectrl.SetItemState(hTreeRoot, TVIS_BOLD, TVIS_BOLD);
	hTreeGeoDetic = m_Treectrl.InsertItem("�������", hTreeRoot);
	hTreeProjected = m_Treectrl.InsertItem("ͶӰ����", hTreeRoot);
	
	//���˶�������
	for(int m=0; m<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); m++)
	{	
		for(int k=m+1; k<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); k++)
		{
			if(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(m)._name.text == GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(k)._name.text){
				//delete GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(k);
				GeoDataMapping.GeodeticNode.pGeodeticSeries.RemoveAt(k);
			}
		}
	}
	
	for(int n=0; n<GeoDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{	
		hItemTmp = m_Treectrl.InsertItem(GeoDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text, hTreeProjected);
		//m_Treectrl.SetItemData(hItemTmp, 54);
	}

	//m_Treectrl.Expand(hTreeGeoDetic, TVE_EXPAND);
	m_Treectrl.Expand(hTreeProjected, TVE_EXPAND);
	m_Treectrl.Expand(hTreeRoot, TVE_EXPAND);
}