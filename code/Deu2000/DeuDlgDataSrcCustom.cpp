// DeuDlgDataSrcCustom.cpp : ʵ���ļ�

#include "stdafx.h"
#include "DeuDlgDataSrcCustom.h"
#include "DeuGlobal.h"
#include "DeuDlgGeoDetic.h"
#include "DeuDlgProjected.h"

// CDeuDlgDataSrcCustom �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgDataSrcCustom, CXTResizeDialog)
CDeuDlgDataSrcCustom::CDeuDlgDataSrcCustom(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CDeuDlgDataSrcCustom::IDD, pParent)
{
}

CDeuDlgDataSrcCustom::~CDeuDlgDataSrcCustom()
{
}

void CDeuDlgDataSrcCustom::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1,  m_Listctrl);
	DDX_Control(pDX, IDC_TREE1,  m_Treectrl);
}

BEGIN_MESSAGE_MAP(CDeuDlgDataSrcCustom, CXTResizeDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDeuDlgDataSrcCustom::OnNMDblclkList1)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CDeuDlgDataSrcCustom::OnNMClickTree1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CDeuDlgDataSrcCustom::OnNMRClickTree1)
	ON_COMMAND(ID_GEODEITC_ADD, CreateGeoDetic)
	ON_COMMAND(ID_PROJECTED_ADD, CreateProjected)	
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &CDeuDlgDataSrcCustom::OnLvnKeydownList1)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDeuDlgDataSrcCustom::OnNMRClickList1)
	ON_COMMAND(ID_MODIFYGEODEITC, OnModifyGeoDetic)
	ON_COMMAND(ID_MODIFYPROJECTED, OnModifyProjected)
END_MESSAGE_MAP()

// CDeuDlgDataSrcCustom ��Ϣ�������
BOOL CDeuDlgDataSrcCustom::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	this->SetResize(IDC_TREE1, SZ_TOP_LEFT, SZ_BOTTOM_LEFT);
	this->SetResize(IDC_LIST1, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);

	m_Listctrl.ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	DWORD dwStyle = m_Listctrl.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
	m_Listctrl.SetExtendedStyle(dwStyle);

	////GeoCentric --- �ռ�ֱ������
	//HTREEITEM hTreeGeoCentric = m_Treectrl.InsertItem("�ռ�ֱ������", hTree);
	//m_Treectrl.InsertItem("ȫ������", hTreeGeoCentric);
	//m_Treectrl.InsertItem("���ʹ������", hTreeGeoCentric);
	//m_Treectrl.Expand(hTreeGeoCentric, TVE_EXPAND);
	//m_treelist.push_back(hTreeGeoCentric);

	m_menu.LoadMenu(IDR_MENUCONTEXT);
	
	m_rCustDataXml.LoadXml("CustomData.xml");
	m_rCustDataXml.MappingGustomData(&CustDataMapping);
	m_rCustDataXml.Free();

	InitListCtrl(All);
	FillListCtrl(All);
	m_Listctrl.DeleteColumn(4);
	m_Listctrl.DeleteColumn(4);

	RefreshTreeCtrl();

	hTreeHandle = hTreeRoot;	

	return TRUE;
}

//GeoDetic --- �������
void CDeuDlgDataSrcCustom::InitListCtrl(CoordinateType _CoodinateType)
{
	//����ListCtrlͷ
	int n = m_Listctrl.GetHeaderCtrl()->GetItemCount();
	while(n >= 0)
	{
		m_Listctrl.DeleteColumn(n-1);
		n--;
	}

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
		}
		break;

	default:
		{
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
void CDeuDlgDataSrcCustom::FillListCtrl(CoordinateType _CoodinateType)
{
	CString str;
	switch(_CoodinateType)
	{
	case GeoDetic:		//�������
		{
			m_Listctrl.DeleteAllItems();
			int nCount = this->m_Listctrl.GetItemCount();
			for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
			{		 
				str.Format("%d", (nCount+1));
				m_Listctrl.InsertItem(nCount, NULL);
				m_Listctrl.SetItemText(nCount, 0, str);
				m_Listctrl.SetItemText(nCount, 1, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
				m_Listctrl.SetItemText(nCount, 2, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
				m_Listctrl.SetItemText(nCount, 3, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
				m_Listctrl.SetItemText(nCount, 4, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
				m_Listctrl.SetItemText(nCount, 5, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
				m_Listctrl.SetItemText(nCount, 6, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);	
				nCount++;
			}
		}
		break;

	case GeoProjected:	//ͶӰ����
		{
			m_Listctrl.DeleteAllItems();
			int nCount = this->m_Listctrl.GetItemCount();
			for(int n=0; n<CustDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
			{
				str.Format("%d", (nCount+1));
				m_Listctrl.InsertItem(nCount, NULL);
				m_Listctrl.SetItemText(nCount, 0, str);
				m_Listctrl.SetItemText(nCount, 1, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text);
				m_Listctrl.SetItemText(nCount, 2, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._name.text);
				m_Listctrl.SetItemText(nCount, 3, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._pointStyle._name.text);
				m_Listctrl.SetItemText(nCount, 4, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text);
				m_Listctrl.SetItemText(nCount, 5, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._projection.text);
				m_Listctrl.SetItemText(nCount, 6, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._remark.text);
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

void CDeuDlgDataSrcCustom::LoadGeodeticPeking54Data()
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._tranStandard == Peking54)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
			m_Listctrl.SetItemText(nCount, 5, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
			m_Listctrl.SetItemText(nCount, 6, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);
			nCount++;
		}
	}
}

void CDeuDlgDataSrcCustom::LoadGeodeticXiAn80Data()
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._tranStandard == XiAn80)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
			m_Listctrl.SetItemText(nCount, 5, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
			m_Listctrl.SetItemText(nCount, 6, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);
			nCount++;
		}
	}
}

void CDeuDlgDataSrcCustom::LoadGeodeticWGS84Data()
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		if(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._tranStandard == WGS84)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
			m_Listctrl.SetItemText(nCount, 5, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
			m_Listctrl.SetItemText(nCount, 6, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);
			nCount++;
		}
	}
}

void CDeuDlgDataSrcCustom::LoadGeodeticCGCS2000Data()
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{		 
		if(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._tranStandard == CGCS2000)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._datum._name.text);
			m_Listctrl.SetItemText(nCount, 5, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n).type);
			m_Listctrl.SetItemText(nCount, 6, CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._remark.text);
			nCount++;		
		}
	}
}

void CDeuDlgDataSrcCustom::LoadSelectedPorjected(CString strGeoDetic)
{
	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<CustDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		if(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text == strGeoDetic)
		{
			str.Format("%d", (nCount+1));
			m_Listctrl.InsertItem(nCount, NULL);
			m_Listctrl.SetItemText(nCount, 0, str);
			m_Listctrl.SetItemText(nCount, 1, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text);
			m_Listctrl.SetItemText(nCount, 2, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._name.text);
			m_Listctrl.SetItemText(nCount, 3, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._pointStyle._name.text);
			m_Listctrl.SetItemText(nCount, 4, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text);
			m_Listctrl.SetItemText(nCount, 5, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._projection.text);
			m_Listctrl.SetItemText(nCount, 6, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._remark.text);
			nCount++;
		}
	}
}

void CDeuDlgDataSrcCustom::LoadAllPorjected()
{
	m_Listctrl.DeleteAllItems();

	CString str;
	int nCount = this->m_Listctrl.GetItemCount();
	for(int n=0; n<CustDataMapping.ProjectedNode.pProjectedSeries.GetCount(); n++)
	{
		str.Format("%d", (nCount+1));
		m_Listctrl.InsertItem(nCount, NULL);
		m_Listctrl.SetItemText(nCount, 0, str);
		m_Listctrl.SetItemText(nCount, 1, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._name.text);
		m_Listctrl.SetItemText(nCount, 2, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._envelope._name.text);
		m_Listctrl.SetItemText(nCount, 3, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._pointStyle._name.text);
		m_Listctrl.SetItemText(nCount, 4, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._geodeticPointor.text);
		m_Listctrl.SetItemText(nCount, 5, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._projection.text);
		m_Listctrl.SetItemText(nCount, 6, CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(n)._remark.text);
		nCount++;
	}
}

void CDeuDlgDataSrcCustom::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if(pNMItemActivate->iItem != -1)
	{
		CString m_strSelectItem;
		m_strSelectItem = m_Listctrl.GetItemText(pNMItemActivate->iItem, 1);
		
		CDeuDlgDataSrcCustomDetail m_Dlg(FALSE);
		m_Dlg.m_Name = m_strSelectItem; //m_Listctrl.GetItemText(m_Listctrl.GetSelectionMark(), 1);
		
		CDeuTaskProcess task;
		char *sz_Type = task.FindCustomCoordType(m_Dlg.m_Name); 

		if(StrCmp(sz_Type, "1") == 0) //GEODETIC
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

	*pResult = 0;
}

//�ڵ���
void CDeuDlgDataSrcCustom::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	DWORD   dwpos = GetMessagePos();
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

//�Ҽ��˵�
void CDeuDlgDataSrcCustom::OnNMRClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	CPoint m_point;
	DWORD  dwpos = GetMessagePos();

	TVHITTESTINFO ht = {0};   
	ht.pt.x = GET_X_LPARAM(dwpos);
	ht.pt.y = GET_Y_LPARAM(dwpos);
	::MapWindowPoints(HWND_DESKTOP,pNMHDR->hwndFrom, &ht.pt, 1); //����Ļ����ת���ɿؼ�����
	TreeView_HitTest(pNMHDR->hwndFrom, &ht);				     //ȷ�����������һ��

	if(ht.hItem == hTreeGeoDetic)
	{
		::GetCursorPos(&m_point);	
		m_menu.GetSubMenu(2)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);
	}
	else if(m_Treectrl.GetParentItem(ht.hItem) == hTreeGeoDetic)
	{
		::GetCursorPos(&m_point);	
		m_menu.GetSubMenu(2)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);
	}
	else if(ht.hItem == hTreeProjected)
	{
		::GetCursorPos(&m_point);	
		m_menu.GetSubMenu(3)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);
	}
	else if(m_Treectrl.GetParentItem(ht.hItem) == hTreeProjected)
	{
		::GetCursorPos(&m_point);	
		m_menu.GetSubMenu(3)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, m_point.x, m_point.y, this);
	}
}

//ˢ����Ŀ¼
void CDeuDlgDataSrcCustom::RefreshTreeCtrl()
{
	m_Treectrl.DeleteAllItems();

	HTREEITEM hItemTmp;
	hTreeRoot = m_Treectrl.InsertItem("����ϵͳ", TVI_ROOT);
	m_Treectrl.SetItemState(hTreeRoot, TVIS_BOLD, TVIS_BOLD);
	hTreeGeoDetic = m_Treectrl.InsertItem("�������", hTreeRoot);
	hTreeProjected = m_Treectrl.InsertItem("ͶӰ����", hTreeRoot);

	for(int n=0; n<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); n++)
	{
		//hItemTmp = m_Treectrl.InsertItem(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text, hTreeGeoDetic);
		hItemTmp = m_Treectrl.InsertItem(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(n)._name.text, hTreeProjected);
		//m_Treectrl.SetItemData(hItemTmp, 54);
	}

	//m_Treectrl.Expand(hTreeGeoDetic, TVE_EXPAND);
	m_Treectrl.Expand(hTreeProjected, TVE_EXPAND);
	m_Treectrl.Expand(hTreeRoot, TVE_EXPAND);
}

void CDeuDlgDataSrcCustom::OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	
	if(pLVKeyDow->wVKey == VK_DELETE)
	{
		if(MessageBox("ȷ��Ҫɾ��ѡ������ϵ��", "ϵͳ��ʾ", MB_OKCANCEL|MB_ICONEXCLAMATION) == IDCANCEL) return;

		CString strSelected;
		strSelected = m_Listctrl.GetItemText(m_Listctrl.GetSelectionMark(), 1);

		if(hTreeHandle == hTreeRoot)
		{
			CDeuTaskProcess task;
			char *sz_Type = task.FindCustomCoordType(strSelected);

			if(lstrcmp(sz_Type, "1") == 0)	   //GeoDetic
			{
				for(int m=0; m<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); m++)
				{
					if(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(m)._name.text == strSelected){
						//delete CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(m);
						CustDataMapping.ProjectedNode.pProjectedSeries.RemoveAt(m);
						break;
					}
				}

				RefreshTreeCtrl();
			}
			else if(lstrcmp(sz_Type, "3") == 0) //Projected
			{
				for(int m=0; m<CustDataMapping.ProjectedNode.pProjectedSeries.GetCount(); m++)
				{
					if(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(m)._name.text == strSelected){
						//delete CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(m);
						CustDataMapping.ProjectedNode.pProjectedSeries.RemoveAt(m);
						break;
					}
				}
			}

			InitListCtrl(All);
			FillListCtrl(All);
			m_Listctrl.DeleteColumn(4);
			m_Listctrl.DeleteColumn(4);
		}
		else if(hTreeHandle == hTreeGeoDetic)
		{
			for(int m=0; m<CustDataMapping.GeodeticNode.pGeodeticSeries.GetCount(); m++)
			{
				if(CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(m)._name.text == strSelected)
				{
					//delete CustDataMapping.GeodeticNode.pGeodeticSeries.GetAt(m);
					CustDataMapping.GeodeticNode.pGeodeticSeries.RemoveAt(m);
					break;
				}
			}

			m_Listctrl.DeleteAllItems();
			InitListCtrl(GeoDetic);
			FillListCtrl(GeoDetic);

			RefreshTreeCtrl();
		}
		else if(hTreeHandle == hTreeProjected)
		{
			for(int m=0; m<CustDataMapping.ProjectedNode.pProjectedSeries.GetCount(); m++)
			{
				if(CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(m)._name.text == strSelected){
					//delete CustDataMapping.ProjectedNode.pProjectedSeries.GetAt(m);
					CustDataMapping.ProjectedNode.pProjectedSeries.RemoveAt(m);
					break;
				}
			}

			LoadAllPorjected();
		}

		m_wCustDataXml.BuildCustomDataXml(GetStylesPath()+"\\CustomData.xml", &CustDataMapping);
	}

	*pResult = 0;
}

void CDeuDlgDataSrcCustom::OnClose()
{
	Release_GeoXml(&CustDataMapping);
	CXTResizeDialog::OnClose();
}

void CDeuDlgDataSrcCustom::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);	
	if(pNMItemActivate->iItem != -1)
	{
		CPoint pt;
		::GetCursorPos(&pt);

		if(hTreeHandle == hTreeGeoDetic)
		{
			m_menu.GetSubMenu(4)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);
		}
		else if(hTreeHandle == hTreeProjected)
		{
			m_menu.GetSubMenu(5)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, this);
		}
	}

	*pResult = 0;
}

//�����������
void CDeuDlgDataSrcCustom::CreateGeoDetic()
{
	CDeuDlgGeoDetic m_dlg;
	if(m_dlg.DoModal() == IDOK)
	{
		RefreshTreeCtrl();
		this->FillListCtrl(All);
	}
	LoadMapping();
}

//����ͶӰ����
void CDeuDlgDataSrcCustom::CreateProjected()
{
	CDeuDlgProjected m_dlg;
	if(m_dlg.DoModal())
	{
		this->FillListCtrl(All);
	}
	LoadMapping();

	//CDeuDlgEllipManager m_DataSrcDlg;
	//if (m_DataSrcDlg.DoModal() == IDOK)
	//{
	//	CEdit* p_edit = (CEdit*)GetDlgItem(IDC_EDIT_COORINATE_INPUT);
	//	if(!m_DataSrcDlg.m_strEllipName.IsEmpty())
	//	{
	//		p_edit->SetWindowText(m_DataSrcDlg.m_strEllipName);
	//	}

	//	//���ÿ��Ƶ����������ϵ
	//	m_Controlpoint_Dlg.SetSrcCoorType(m_DataSrcDlg.m_strEllipName);
	//}
}

void CDeuDlgDataSrcCustom::OnModifyGeoDetic()
{
	CDeuDlgGeoDetic m_dlg(TRUE);
	m_dlg.m_strCoordName = m_Listctrl.GetItemText(m_Listctrl.GetSelectionMark(), 1);
	if(m_dlg.DoModal() == IDOK)
	{
		RefreshTreeCtrl();
		this->FillListCtrl(All);
	}
	LoadMapping();
}

void CDeuDlgDataSrcCustom::OnModifyProjected()
{
	CDeuDlgProjected m_dlg(TRUE);
	m_dlg.m_strCoordName = m_Listctrl.GetItemText(m_Listctrl.GetSelectionMark(), 1);
	if(m_dlg.DoModal())
	{
		this->FillListCtrl(All);
	}
	LoadMapping();
}