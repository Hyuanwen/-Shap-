// DeuDlgLogin.cpp : 实现文件

#include "stdafx.h"
#include "DeuDlgLogin.h"
#include "DeuGlobal.h"
#include "DeuSQLProvider.h"

IMPLEMENT_DYNAMIC(CDeuDlgLogin, CXTPDialog)
CDeuDlgLogin::CDeuDlgLogin(CWnd* pParent /*=NULL*/)
	: CXTPDialog(CDeuDlgLogin::IDD, pParent)
{
    m_sEdit_Account = _T("");
	m_sEdit_Userpwd= _T("");
	//XTPSkinManager()->LoadSkin(GetStylesPath() + _T("\\Office2007.cjstyles"), _T("NormalBlack.ini"));
}

CDeuDlgLogin::~CDeuDlgLogin()
{
}

void CDeuDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CXTPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ACCOUNT, m_Edit_Account);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_Edit_Account);
	DDX_Control(pDX, IDC_EDIT_USERPWD, m_Edit_Userpwd);
	DDX_Control(pDX, IDC_BTN_LOGIN_ENTER, m_btnLogin);
}

BEGIN_MESSAGE_MAP(CDeuDlgLogin, CXTPDialog)
	ON_BN_CLICKED(IDC_BTN_LOGIN_ENTER, &CDeuDlgLogin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_LOGIN_CANCEL, &CDeuDlgLogin::OnBnClickedBtnCancel)	
END_MESSAGE_MAP()

// CDeuDlgLogin 消息处理程序
BOOL CDeuDlgLogin::OnInitDialog()
{
	CXTPDialog::OnInitDialog();
	
	//加载标题
	char sz_tip[MAX_PATH];
	LoadString(AfxGetInstanceHandle(),IDR_MAINFRAME, sz_tip, sizeof(sz_tip));
	this->SetWindowText(sz_tip);

	//设置图标
	HICON hIco = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
	this->SetIcon(hIco, FALSE);	

    CDeuSQLite3Query m_query;
	CDeuSQLProvider m_SqlProvider;
	m_query = m_SqlProvider.GetUsersQueryObject();
	while(!m_query.eof())
	{
		m_Edit_Account.AddString(m_query.fieldValue("users_name"));
	    m_query.nextRow();
	}

	UpdateData();
	
	return TRUE;  //return TRUE unless you set the focus to a control，异常: OCX 属性页应返回 FALSE
}

void CDeuDlgLogin::OnBnClickedButton1()
{
	UpdateData(TRUE);

	CString str1, str2;
	m_Edit_Account.GetWindowText(str1);
	m_Edit_Userpwd.GetWindowText(str2);
	if(str1.IsEmpty())
	{
		MessageBox("请输入账号","登陆提示", MB_OK|MB_ICONWARNING);
	}
	else if(str2.IsEmpty())
	{
		MessageBox("请输入密码", "登陆提示", MB_OK|MB_ICONWARNING);
	}
	else
	{
		CDeuSQLProvider m_Sqlite;
		CStringArray m_array;
		m_Sqlite.GetUser(str1, str2, &m_array);

		if(m_array.GetCount() == 0)
		{
			MessageBox(_T("登录信息不正确，登录失败！"),NULL,0);
			
		}
		else
		{		
			GobalUserInfo.strName = str1;
			//加载并缓存用户权限信息
			LoadPowerInfo(&GobalUserInfo);

			this->OnOK();
		}
	}
}

void CDeuDlgLogin::OnBnClickedBtnCancel()
{
	//释放内存，防止泄露
	CDeuXmlReader m_XmlReader;
	m_XmlReader.ReleaseGeoDataMapping(&GeoDataMapping);
	m_XmlReader.ReleseTaskMapping(&TasksMapping);

	this->OnCancel();
}

BOOL CDeuDlgLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
		OnBnClickedButton1();
		return TRUE; 
		
	}	

	return CXTPDialog::PreTranslateMessage(pMsg);
}
