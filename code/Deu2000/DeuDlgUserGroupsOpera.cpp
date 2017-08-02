// DeuDlgUserGroupsOpera.cpp : 实现文件

#include "stdafx.h"
#include "DeuGlobal.h"
#include "DeuDlgUserGroupsOpera.h"
#include "DeuSQLProvider.h"

// CDeuDlgUserGroupsOpera 对话框
IMPLEMENT_DYNAMIC(CDeuDlgUserGroupsOpera, CDialog)
CDeuDlgUserGroupsOpera::CDeuDlgUserGroupsOpera(CWnd* pParent /*=NULL*/)
	: CDialog(CDeuDlgUserGroupsOpera::IDD, pParent)
{
	m_nStatus = 0;
}

CDeuDlgUserGroupsOpera::~CDeuDlgUserGroupsOpera()
{
}

void CDeuDlgUserGroupsOpera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHK_SGC, m_ChkSg_C);
	DDX_Control(pDX, IDC_CHK_SLC, m_ChkSl_C);
	DDX_Control(pDX, IDC_CHK_DBC, m_ChkDb_C);
	DDX_Control(pDX, IDC_CHK_SGE, m_ChkSg_E);
	DDX_Control(pDX, IDC_CHK_SLE, m_ChkSl_E);
	DDX_Control(pDX, IDC_CHK_DBE, m_ChkDb_E);
	DDX_Control(pDX, IDC_EDIT_UGROUPNAME, m_edit_ugroup);
}

BEGIN_MESSAGE_MAP(CDeuDlgUserGroupsOpera, CDialog)
	ON_BN_CLICKED(IDC_BTN_UGROUP_SAVE, &CDeuDlgUserGroupsOpera::OnBnClickedBtnUgroupSave)
	ON_BN_CLICKED(IDC_BTN_UGROUP_CANCEL, &CDeuDlgUserGroupsOpera::OnBnClickedBtnUgroupCancel)
END_MESSAGE_MAP()

// CDeuDlgUserGroupsOpera 消息处理程序
void CDeuDlgUserGroupsOpera::OnBnClickedBtnUgroupSave()
{
	CDeuSQLProvider m_SqlProvider;

	CString strIsSgC;
	CString strIsSlC;
	CString strIsDbC;

	CString strIsSgE;
	CString strIsSlE;
	CString strIsDbE;

	if(m_ChkSl_E.GetCheck()) strIsSlE = "√"; else strIsSlE = "×";
	if(m_ChkSg_E.GetCheck()) strIsSgE = "√"; else strIsSgE = "×";
	if(m_ChkDb_E.GetCheck()) strIsDbE = "√"; else strIsDbE = "×";

	if(m_ChkSl_C.GetCheck()) strIsSlC = "√"; else strIsSlC = "×";
	if(m_ChkSg_C.GetCheck()) strIsSgC = "√"; else strIsSgC = "×";
	if(m_ChkDb_C.GetCheck()) strIsDbC = "√"; else strIsDbC = "×";

	m_edit_ugroup.GetWindowText(m_UserGroupName);

	if(m_nStatus == 0)
	{
		if(!m_SqlProvider.GetUserGroupByName(m_UserGroupName))
		{
			int nRet;
			nRet = m_SqlProvider.CreateUserGroup(m_UserGroupName, strIsSgE, strIsSlE, strIsDbE, strIsSgC, strIsSlC, strIsDbC);

			if(nRet == 1)
			{		
				this->OnOK();
			}
			else if(nRet == -1)
			{
				MessageBox("用户组重名",NULL, MB_OK|MB_ICONEXCLAMATION);
			}
			else
			{
				MessageBox("操作失败",NULL, MB_OK|MB_ICONINFORMATION);
				this->OnCancel();
			}
		}
		else
		{
			MessageBox("用户组名已存在",NULL, MB_OK|MB_ICONINFORMATION);
		}
	}

	/* 更新操作 */
	else if(m_nStatus == 1)
	{
		BOOL m_bRet;
		m_bRet = m_SqlProvider.UpdateUserGroup(m_strSelectedName, strIsSlE, strIsSgE, strIsDbE, strIsSlC, strIsSgC, strIsDbC);

		/* 更新全局缓存的权限 */
		LoadPowerInfo(&GobalUserInfo);

		if(m_bRet)
		{
			this->OnOK();
		}
		else
		{
			this->OnCancel();
		}
	}
}

void CDeuDlgUserGroupsOpera::OnBnClickedBtnUgroupCancel()
{
	this->OnCancel();
}

BOOL CDeuDlgUserGroupsOpera::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(this->m_nStatus == 0)
	{
		this->m_edit_ugroup.SetReadOnly(FALSE);
		this->SetWindowText("创建用户组");
	}
	else
	{
		this->SetWindowText("更新用户组");
		this->m_edit_ugroup.SetReadOnly(TRUE);
		CStringArray m_array;
		CDeuSQLProvider m_SqlProvider;
		m_SqlProvider.GetUserGroupByName(m_strSelectedName, &m_array);

		if(m_array.GetCount() > 0 )
		{
			m_edit_ugroup.SetWindowText(m_strSelectedName);

			if(m_array.GetAt(0) == "√")
			{
				m_ChkSl_E.SetCheck(1);
			}

			if(m_array.GetAt(1) == "√")
			{
				m_ChkSg_E.SetCheck(1);;	
			}

			if(m_array.GetAt(2) == "√")
			{
				m_ChkDb_E.SetCheck(1);;	
			}

			if(m_array.GetAt(3) == "√")
			{
				m_ChkSl_C.SetCheck(1);
			}

			if(m_array.GetAt(4) == "√")
			{
				m_ChkSg_C.SetCheck(1);
			}

			if(m_array.GetAt(5) == "√")
			{
				m_ChkDb_C.SetCheck(1);
			}
		}
	}

	return TRUE;
}
