// DeuDlgUserOpera.cpp : 实现文件

#include "stdafx.h"
#include "DeuDlgUsersOpera.h"
#include "DeuSQLProvider.h"
#include "DeuGlobal.h"

// CDeuDlgUsersOpera 对话框
IMPLEMENT_DYNAMIC(CDeuDlgUsersOpera, CDialog)
CDeuDlgUsersOpera::CDeuDlgUsersOpera(CWnd* pParent, DWORD m_dwType)
	: CDialog(CDeuDlgUsersOpera::IDD, pParent)
{
	this->m_dwWndType = m_dwType;
}

CDeuDlgUsersOpera::~CDeuDlgUsersOpera()
{
}

void CDeuDlgUsersOpera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_username);
	DDX_Control(pDX, IDC_EDIT_USERPWD, m_userpwd);
	DDX_Control(pDX, IDC_LIST_UROLE_SRC, m_list_src);
	DDX_Control(pDX, IDC_LIST_UROLE_DEST, m_list_dest);
	DDX_Control(pDX, IDC_BTN_UROLE_SELECT, m_btn_select);
	DDX_Control(pDX, IDC_BTN_UROLE_SELECTALL, m_btn_selectall);
	DDX_Control(pDX, IDC_BTN_UROLE_REMOVE, m_btn_remove);
	DDX_Control(pDX, IDC_BTN_UROLE_REMOVEALL, m_btn_removeall);
	DDX_Control(pDX, IDC_BTN_USERS_SAVE, m_btn_save);
}

BEGIN_MESSAGE_MAP(CDeuDlgUsersOpera, CDialog)
	ON_BN_CLICKED(IDC_BTN_USERS_CANCEL, &CDeuDlgUsersOpera::OnBnClickedBtnUsersCancel)
	ON_BN_CLICKED(IDC_BTN_USERS_SAVE, &CDeuDlgUsersOpera::OnBnClickedBtnUsersSave)
	ON_BN_CLICKED(IDC_BTN_UROLE_SELECT, &CDeuDlgUsersOpera::OnBnClickedBtnUroleSelect)
	ON_BN_CLICKED(IDC_BTN_UROLE_SELECTALL, &CDeuDlgUsersOpera::OnBnClickedBtnUroleSelectall)
	ON_BN_CLICKED(IDC_BTN_UROLE_REMOVE, &CDeuDlgUsersOpera::OnBnClickedBtnUroleRemove)
	ON_BN_CLICKED(IDC_BTN_UROLE_REMOVEALL, &CDeuDlgUsersOpera::OnBnClickedBtnUroleRemoveall)
END_MESSAGE_MAP()

// CDeuDlgUsersOpera 消息处理程序
void CDeuDlgUsersOpera::OnBnClickedBtnUsersCancel()
{
	this->OnCancel();
}

void CDeuDlgUsersOpera::OnBnClickedBtnUsersSave()
{
	/* 用户账号，密码信息 */
	CString m_strUserName, m_strUserPwd, m_strUserGroupId;

	m_username.GetWindowText(m_strUserName);
	m_userpwd.GetWindowText(m_strUserPwd);

	if(m_strUserName.IsEmpty())
	{
		MessageBox("请输入用户名", "系统提示", MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	else if(m_strUserPwd.IsEmpty())
	{
		MessageBox("请输入密码", "系统提示", MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	CDeuSQLProvider m_SqlProvider;

	if(m_list_dest.GetCount() > 0)
	{
		/* 用户组ID */
		CString m_strTmpName, m_strTmpId;
		for(int n=0; n<m_list_dest.GetCount(); n++)
		{
			m_list_dest.GetText(n, m_strTmpName);

			m_SqlProvider.GetUserGroupIdByName(m_strTmpName, &m_strTmpId);

			m_strUserGroupId += m_strTmpId+",";
		}

		m_strUserGroupId.TrimRight(",");
	}

	bool m_nRet;

	/* 创建保存 */
	if(m_dwWndType == 1)
	{
		//保存前检查重名
		if(!m_SqlProvider.CheckUserExist(m_strUserName))
		{
			m_nRet = m_SqlProvider.CreateUser(m_strUserName, m_strUserPwd, m_strUserGroupId);
		}
		else
		{
			MessageBox("账号已存在", "系统提示", MB_OK|MB_ICONINFORMATION);
			m_nRet = false;
			return;
		}
		
	}	
	/* 更新保存 */
	else if(m_dwWndType == 2)
	{
		m_nRet = m_SqlProvider.UpdateUser(m_strCurName, m_strUserName, m_strUserPwd, m_strUserGroupId);

		/* 更新全局权限 */
		if(m_strCurName == p_cUserName) LoadPowerInfo(&GobalUserInfo);
	}

	if(m_nRet)
	{
		this->OnOK();
	}
	else
	{
		this->OnCancel();
	}
}

BOOL CDeuDlgUsersOpera::OnInitDialog()
{
	CDialog::OnInitDialog();

	/* 初始化用户组数据 */
	CDeuSQLite3Query m_query;
	CDeuSQLProvider m_SqlProvider;
	m_query = m_SqlProvider.GetGroupQueryObject();

	/*  动态修改窗口标题 */
	switch(m_dwWndType)
	{
	case 1:
		{
			this->SetWindowText("增加用户");
			while(!m_query.eof())
			{
				this->m_list_src.AddString(m_query.fieldValue("usergroup_name"));
				m_query.nextRow();
			}
		}
		break;

	case 2:
		{
			this->SetWindowText("修改用户");
			CStringArray m_array;
			CDeuSQLProvider m_SqlProvider;
			m_SqlProvider.GetUser(this->m_strCurName, &m_array);

			m_username.SetWindowText(m_array.GetAt(0));
			m_userpwd.SetWindowText(m_array.GetAt(1));

			//p_EditUserName->SetWindowText();
			//TRACE("%s", m_array.GetAt(2));
			while(!m_query.eof())
			{
				//寻找匹配用户组
				if(m_array.GetAt(2).Find(m_query.fieldValue("usergroup_id"), 0) != -1)
					this->m_list_dest.AddString(m_query.fieldValue("usergroup_name"));

				this->m_list_src.AddString(m_query.fieldValue("usergroup_name"));
				m_query.nextRow();
			}
		}
		break;
	}

	return TRUE;
}

void CDeuDlgUsersOpera::OnBnClickedBtnUroleSelect()
{
	if(this->m_list_src.GetCurSel() == -1) 
	{ 
		MessageBox("请选择用户组", "系统提示", MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	CString m_strListText, m_strSelectedText;
	BOOL    IsExist = FALSE;

	//排除重复的数据
	m_list_src.GetText(m_list_src.GetCurSel(), m_strSelectedText);
	char *szSrc = (char*)(LPCTSTR)m_strSelectedText;

	if(m_list_src.GetCount() > m_list_dest.GetCount())
	{
		for(int n=0; n<m_list_dest.GetCount(); n++)
		{
			m_list_dest.GetText(n, m_strListText);
			char *szDest = (char*)(LPCTSTR)m_strListText;

			//判断该角色是否存在
			if(strcmp(szSrc, szDest) == 0)
			{
				MessageBox("该用户组已存在", "系统提示",MB_OK|MB_ICONINFORMATION);
				IsExist = TRUE;
				break;
			}
		}

		if(IsExist == FALSE)
		{
			m_list_dest.AddString(m_strSelectedText);
		}
	}
	else
	{
		MessageBox("已全选", "系统提示",MB_OK|MB_ICONINFORMATION);
	}

}

void CDeuDlgUsersOpera::OnBnClickedBtnUroleSelectall()
{
	OnBnClickedBtnUroleRemoveall();

	CString m_strTmp;
	for(int n=0; n<m_list_src.GetCount(); n++)
	{
		m_list_src.GetText(n, m_strTmp);
		m_list_dest.AddString(m_strTmp);
	}
}

void CDeuDlgUsersOpera::OnBnClickedBtnUroleRemove()
{
	int nCurSel;

	if((m_list_dest.GetCount() > 0) 
		&& (m_list_dest.GetCurSel() != -1))
	{		
		nCurSel = m_list_dest.GetCurSel();
		m_list_dest.DeleteString(nCurSel);
		m_list_dest.SetCurSel(nCurSel);
	}
	else
	{
		AfxMessageBox("请选择移除项");
	}
}

void CDeuDlgUsersOpera::OnBnClickedBtnUroleRemoveall()
{
	while(m_list_dest.GetCount() > 0) 
	{
		m_list_dest.DeleteString(0);
	}
}
