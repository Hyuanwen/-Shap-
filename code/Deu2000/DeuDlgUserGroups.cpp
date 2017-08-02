// DeuUserGroupsDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "DeuDlgUserGroups.h"
#include "DeuDlgUserGroupsOpera.h"
#include "DeuSQLProvider.h"

// CDeuDlgUserGroups �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgUserGroups, CDialog)
CDeuDlgUserGroups::CDeuDlgUserGroups(CWnd* pParent /*=NULL*/)
	: CDialog(CDeuDlgUserGroups::IDD, pParent)
{
	m_strDesc[0] = "դ��ת������";
	m_strDesc[1] = "ʸ��ת������";
	m_strDesc[2] = "���ݿ�ת������";
	m_strDesc[3] = "դ���������";
	m_strDesc[4] = "ʸ���������";
	m_strDesc[5] = "���ݿ��������";
}

CDeuDlgUserGroups::~CDeuDlgUserGroups()
{
}

void CDeuDlgUserGroups::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_TreeUGroup);
}

BEGIN_MESSAGE_MAP(CDeuDlgUserGroups, CDialog)
	ON_BN_CLICKED(IDC_BTN_CREATE_UGROUP, &CDeuDlgUserGroups::OnBnClickedBtnCreateUgroup)
	ON_BN_CLICKED(IDC_BTN_UPDATE_UGROUP, &CDeuDlgUserGroups::OnBnClickedBtnUpdateUgroup)
	ON_BN_CLICKED(IDC_BTN_DEL_UGROUP, &CDeuDlgUserGroups::OnBnClickedBtnDelUgroup)
	ON_BN_CLICKED(IDC_BTN_UGROUP_CANCEL, &CDeuDlgUserGroups::OnBnClickedBtnCancelUgroup)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CDeuDlgUserGroups::OnTvnSelchangedTree1)	
END_MESSAGE_MAP()

// CDeuDlgUserGroups ��Ϣ�������
/*
===================================================
����:	  �������ؼ�����
����:     bool IsInit �Ƿ�Ϊ���μ������ݱ�ʶ��
true	  ���γ�ʼ��
false     �ڶ��μ���
����:	  2010-11-1
===================================================
*/
void CDeuDlgUserGroups::LoadTreeCtrl(bool IsInit)
{
	m_TreeUGroup.DeleteAllItems();
	m_TreeUGroup.SetImageList(&m_ImgList, TVSIL_NORMAL);

	HTREEITEM htreeitem = this->m_TreeUGroup.InsertItem("�����û���", TVI_ROOT);

	CDeuSQLite3Query m_query;
	CDeuSQLProvider m_SqlProvider;
	m_query = m_SqlProvider.GetGroupQueryObject();
	HTREEITEM m_hItem;
	while(!m_query.eof())
	{
		m_hItem = m_TreeUGroup.InsertItem(m_query.fieldValue(1), 0, 0, htreeitem);
		m_query.nextRow();
	}
	m_TreeUGroup.Expand(htreeitem, TVE_EXPAND);

	if(!IsInit)
	{
		//m_TreeUGroup.getitemco(m_hItem);
	}
}

void CDeuDlgUserGroups::OnBnClickedBtnCreateUgroup()
{
	CDeuDlgUserGroupsOpera m_Dlg;
	if(m_Dlg.DoModal() == IDOK)
	{
		this->LoadTreeCtrl();
	}
}

/*
===================================================
����:	  �����û������� add by hushichen 
����:	  2010-11-4
===================================================
*/
void CDeuDlgUserGroups::OnBnClickedBtnUpdateUgroup()
{
	HTREEITEM m_hTree;
	m_hTree = m_TreeUGroup.GetSelectedItem();

	if(m_hTree != NULL && (m_hTree != m_TreeUGroup.GetRootItem()))
	{
		CString m_strName;
		m_strName = m_TreeUGroup.GetItemText(m_TreeUGroup.GetSelectedItem());

		CDeuDlgUserGroupsOpera m_DlgGroupOperator;
		m_DlgGroupOperator.m_nStatus = 1;
		m_DlgGroupOperator.m_strSelectedName = m_strName;
		if(m_DlgGroupOperator.DoModal() == IDOK)
		{ 
			CStringArray m_array;
			CDeuSQLProvider m_DeuSQLProvider;
			m_DeuSQLProvider.GetUserGroupByName(m_TreeUGroup.GetItemText(m_TreeUGroup.GetSelectedItem()), &m_array);

			/* դ����� */
			CStatic* p_sge = (CStatic*)this->GetDlgItem(IDC_SGE);
			p_sge->SetWindowText(m_array.GetAt(4)+"  "+m_strDesc[0]);

			/* ʸ����� */
			CStatic* p_sle = (CStatic*)this->GetDlgItem(IDC_SLE);
			p_sle->SetWindowText(m_array.GetAt(3)+"  "+m_strDesc[1]);

			/* ���ݿ���� */
			CStatic* p_dbe = (CStatic*)this->GetDlgItem(IDC_DBE);
			p_dbe->SetWindowText(m_array.GetAt(5)+"  "+m_strDesc[2]);

			/* դ��ת�� */
			CStatic* p_sgc = (CStatic*)this->GetDlgItem(IDC_SGC);
			p_sgc->SetWindowText(m_array.GetAt(1)+"  "+m_strDesc[3]);

			/* ʸ��ת�� */
			CStatic* p_slc = (CStatic*)this->GetDlgItem(IDC_SLC);
			p_slc->SetWindowText(m_array.GetAt(0)+"  "+m_strDesc[4]);

			/* ���ݿ�ת�� */
			CStatic* p_dbc = (CStatic*)this->GetDlgItem(IDC_DBC);
			p_dbc->SetWindowText(m_array.GetAt(2)+"  "+m_strDesc[5]);
		}
	}
	else
	{
		MessageBox("��ѡ��Ҫ���µ��û���", "ϵͳ��ʾ", MB_OK|MB_ICONINFORMATION);
	}
}

void CDeuDlgUserGroups::OnBnClickedBtnDelUgroup()
{
	if(IDYES == MessageBox("ȷ��ɾ���û��飿", "ϵͳ��ʾ", MB_YESNO|MB_ICONINFORMATION))
	{
		if(m_TreeUGroup.GetItemText(m_TreeUGroup.GetSelectedItem()) == "��������Ա")
		{
			MessageBox("����ɾ�����û���", "ϵͳ��ʾ", MB_OK|MB_ICONINFORMATION);
		}
		else
		{
			CDeuSQLProvider m_DeuSQLProvider;
			BOOL m_bIsOk = m_DeuSQLProvider.DelUserGroupByName(m_TreeUGroup.GetItemText(m_TreeUGroup.GetSelectedItem()));
			if(m_bIsOk)
			{
				this->LoadTreeCtrl();

				CStatic* p_sgc = (CStatic*)this->GetDlgItem(IDC_SGC);
				p_sgc->SetWindowText("  "+m_strDesc[0]);

				CStatic* p_slc = (CStatic*)this->GetDlgItem(IDC_SLC);
				p_slc->SetWindowText("  "+m_strDesc[1]);

				CStatic* p_dbc = (CStatic*)this->GetDlgItem(IDC_DBC);
				p_dbc->SetWindowText("  "+m_strDesc[2]);

				CStatic* p_sge = (CStatic*)this->GetDlgItem(IDC_SGE);
				p_sge->SetWindowText("  "+m_strDesc[3]);

				CStatic* p_sle = (CStatic*)this->GetDlgItem(IDC_SLE);
				p_sle->SetWindowText("  "+m_strDesc[4]);

				CStatic* p_dbe = (CStatic*)this->GetDlgItem(IDC_DBE);
				p_dbe->SetWindowText("  "+m_strDesc[5]);
			}
		}
	}
}

BOOL CDeuDlgUserGroups::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*  ��ʼ��ͼƬ */
	m_ImgList.Create(16,16,ILC_COLOR32|ILC_MASK, 1,0);
	m_ImgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_UGROUP));

	/*  ���οռ�������� */
	LoadTreeCtrl(TRUE);

	return TRUE;
}

/*   ������νڵ��¼�  */
void CDeuDlgUserGroups::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	/*
	DWORD dwpos = GetMessagePos();
	TVHITTESTINFO ht={0};

	ht.pt.x = GET_X_LPARAM(dwpos);
	ht.pt.y = GET_Y_LPARAM(dwpos);
	::MapWindowPoints(HWND_DESKTOP, pNMHDR->hwndFrom, &ht.pt, 1);

	TreeView_HitTest(pNMHDR->hwndFrom, &ht);
	*/

	if(m_TreeUGroup.GetSelectedItem() != m_TreeUGroup.GetRootItem())
	{
		CStringArray m_array;
		CDeuSQLProvider m_DeuSQLProvider;
		m_DeuSQLProvider.GetUserGroupByName(m_TreeUGroup.GetItemText(m_TreeUGroup.GetSelectedItem()), &m_array);

		/* դ����� */
		CStatic* p_sge = (CStatic*)this->GetDlgItem(IDC_SGE);
		p_sge->SetWindowText(m_array.GetAt(4)+"  "+m_strDesc[0]);

		/* ʸ����� */
		CStatic* p_sle = (CStatic*)this->GetDlgItem(IDC_SLE);
		p_sle->SetWindowText(m_array.GetAt(3)+"  "+m_strDesc[1]);

		/* ���ݿ���� */
		CStatic* p_dbe = (CStatic*)this->GetDlgItem(IDC_DBE);
		p_dbe->SetWindowText(m_array.GetAt(5)+"  "+m_strDesc[2]);

		/* դ��ת�� */
		CStatic* p_sgc = (CStatic*)this->GetDlgItem(IDC_SGC);
		p_sgc->SetWindowText(m_array.GetAt(1)+"  "+m_strDesc[3]);

		/* ʸ��ת�� */
		CStatic* p_slc = (CStatic*)this->GetDlgItem(IDC_SLC);
		p_slc->SetWindowText(m_array.GetAt(0)+"  "+m_strDesc[4]);

		/* ���ݿ�ת�� */
		CStatic* p_dbc = (CStatic*)this->GetDlgItem(IDC_DBC);
		p_dbc->SetWindowText(m_array.GetAt(2)+"  "+m_strDesc[5]);

	}

	*pResult = 0;
}

void CDeuDlgUserGroups::OnBnClickedBtnCancelUgroup()
{
	this->OnCancel();
}
