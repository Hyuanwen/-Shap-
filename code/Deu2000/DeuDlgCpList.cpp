// DeuDlgCpList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuDlgCpList.h"

// CDeuDlgCpList �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgCpList, CDialog)
CDeuDlgCpList::CDeuDlgCpList(CWnd* pParent /*=NULL*/)
	         : CDialog(CDeuDlgCpList::IDD, pParent)
{
}

CDeuDlgCpList::~CDeuDlgCpList()
{
}

void CDeuDlgCpList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_Grid);  
	DDX_Text(pDX, IDC_EDIT_CPNUM, m_CpNum);
}

BEGIN_MESSAGE_MAP(CDeuDlgCpList, CDialog)
	ON_BN_CLICKED(IDC_BTN_SETLIST, &CDeuDlgCpList::OnBnClickedButtonSetList)
	ON_BN_CLICKED(IDOK, &CDeuDlgCpList::OnBnClickedOk)
END_MESSAGE_MAP()

// CDeuDlgCpList ��Ϣ�������
BOOL CDeuDlgCpList::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Grid.SetRowCount(2);
	m_Grid.SetColumnCount(6);

	m_Grid.SetItemText(0, 0, _T("    Դ���Ƶ�X   "));
	m_Grid.SetItemText(0, 1, _T("    Դ���Ƶ�Y   "));
	m_Grid.SetItemText(0, 2, _T("    Դ���Ƶ�Z   "));

	m_Grid.SetItemText(0, 3, _T("  Ŀ����Ƶ�X  "));
	m_Grid.SetItemText(0, 4, _T("  Ŀ����Ƶ�Y  "));
	m_Grid.SetItemText(0, 5, _T("  Ŀ����Ƶ�Z  "));

	m_Grid.SetItemState(0, 0, GVIS_READONLY);
	m_Grid.SetItemState(0, 1, GVIS_READONLY);
	m_Grid.SetItemState(0, 2, GVIS_READONLY);
	m_Grid.SetItemState(0, 3, GVIS_READONLY);
	m_Grid.SetItemState(0, 4, GVIS_READONLY);
	m_Grid.SetItemState(0, 5, GVIS_READONLY);

	//�����п�
	m_Grid.SetColumnWidth(0,110);
	m_Grid.SetColumnWidth(1,110);
	m_Grid.SetColumnWidth(2,110);
	m_Grid.SetColumnWidth(3,110);
	m_Grid.SetColumnWidth(4,110);
	m_Grid.SetColumnWidth(5,110);

	//�����и�
	m_Grid.SetRowHeight(0, 30);
	m_Grid.SetRowHeight(1, 30);

	m_CpNum = 1;

	UpdateData(FALSE);

	return TRUE;
}

void CDeuDlgCpList::OnBnClickedButtonSetList()
{
	UpdateData(TRUE);

	m_Grid.SetRowCount(m_CpNum+1);

	//ѭ�������еĸ߶�
	for (int i = 1; i < m_CpNum+1; i++)
	{
		m_Grid.SetRowHeight(i, 30);
	}
}

void CDeuDlgCpList::OnBnClickedOk()
{
	ControlPoint                               tmpControlPoint;
	CTpErrProc                                 ErrProc;
	CString                                    str;

	//�����ݴ���
	m_ControlPoint.Reset();

	//����ܵ�����
	for (int i = 1; i < m_Grid.GetRowCount(); i++)
	{
		str = m_Grid.GetItemText(i,0);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("��Чֵ!"));
			return;
		}
		sprintf(tmpControlPoint.des_x, "%s", str);

		str = m_Grid.GetItemText(i,1);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("��Чֵ!"));
			return;
		}
		sprintf(tmpControlPoint.des_y, "%s", str);

		str = m_Grid.GetItemText(i,2);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("��Чֵ!"));
			return;
		}
		sprintf(tmpControlPoint.des_z, "%s", str);

		str = m_Grid.GetItemText(i,3);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("��Чֵ!"));
			return;
		}
		sprintf(tmpControlPoint.res_x, "%s", str);

		str = m_Grid.GetItemText(i,4);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("��Чֵ!"));
			return;
		}
		sprintf(tmpControlPoint.res_y, "%s", str);

		str = m_Grid.GetItemText(i,5);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("��Чֵ!"));
			return;
		}
		sprintf(tmpControlPoint.res_z, "%s", str);

		m_ControlPoint.Append(&tmpControlPoint, &ErrProc);
	}
	
	OnOK();
}
