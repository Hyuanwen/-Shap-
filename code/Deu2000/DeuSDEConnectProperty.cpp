// DeuSDEConnectProperty.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "DeuSDEConnectProperty.h"
#include "ArcSDEConnection.h"


// CDeuSDEConnectProperty 对话框

IMPLEMENT_DYNAMIC(CDeuSDEConnectProperty, CDialog)

CDeuSDEConnectProperty::CDeuSDEConnectProperty(CWnd* pParent /*=NULL*/)
	: CDialog(CDeuSDEConnectProperty::IDD, pParent)
{

	m_Workspace = NULL;
}

CDeuSDEConnectProperty::~CDeuSDEConnectProperty()
{
}

void CDeuSDEConnectProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_SERVER, m_edit_server);
	DDX_Control(pDX, IDC_ED_SERVICE, m_edit_service);
	DDX_Control(pDX, IDC_ED_DATABASE, m_edit_database);
	DDX_Control(pDX, IDC_ED_USERNAME, m_edit_username);
	DDX_Control(pDX, IDC_ED_PASSWORD, m_edit_password);
	DDX_Control(pDX, IDC_ED_VERSION, m_edit_version);
	DDX_Control(pDX, IDC_CHECK1, m_checkbox_version);
}


BEGIN_MESSAGE_MAP(CDeuSDEConnectProperty, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, &CDeuSDEConnectProperty::OnBnClickedCheck1)
	ON_BN_CLICKED(IDOK, &CDeuSDEConnectProperty::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CDeuSDEConnectProperty::OnBnClickedBtnConnect)
END_MESSAGE_MAP()


// CDeuSDEConnectProperty 消息处理程序

BOOL CDeuSDEConnectProperty::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_checkbox_version.SetCheck(1);
	m_edit_version.SetWindowText(_T("sde.DEFAULT"));
	m_edit_version.EnableWindow(FALSE);

	CButton*   pOK = (CButton*)GetDlgItem(IDOK);
	pOK->EnableWindow(FALSE);

	InitCtrls();

	UpdateData(FALSE);
	return TRUE;
}
void CDeuSDEConnectProperty::OnBnClickedBtnTest()
{

}

void CDeuSDEConnectProperty::OnBnClickedCheck1()
{
	if (m_checkbox_version.GetCheck())
	{
		m_edit_version.EnableWindow(FALSE);
	}
	else
	{
		m_edit_version.EnableWindow(TRUE);
	}

}

void CDeuSDEConnectProperty::OnBnClickedOk()
{
	/*CArcSDEConnection						SdeConnection;
	this->GetSDEInfo();
	if (SUCCEEDED(SdeConnection.ConnectToSDE(strServer, strInstance, strDatabase, strUsername, strPassword, strVersion, &m_Workspace)))
	{
		AfxMessageBox(_T("Connection Succeeded"));
		OnOK();
	}
	else
	{
		AfxMessageBox(_T("Connection Failed"));
	}*/
	OnOK();
	
}

void CDeuSDEConnectProperty::GetSDEInfo()
{
	UpdateData();

	m_edit_server.GetWindowText(strServer);
	m_edit_service.GetWindowText(strInstance);
	m_edit_database.GetWindowText(strDatabase);
	m_edit_username.GetWindowText(strUsername);
	m_edit_password.GetWindowText(strPassword);
	m_edit_version.GetWindowText(strVersion);
}


IWorkspacePtr CDeuSDEConnectProperty::GetWorkspace() const
{
	return m_Workspace;
}


void CDeuSDEConnectProperty::OnBnClickedBtnConnect()
{

	CArcSDEConnection						SdeConnection;
	this->GetSDEInfo();

	//判断是否输入值
	if (strServer.IsEmpty())
	{
		AfxMessageBox(_T("请输入SDE服务器的IP"));
		return;
	}

	if (strInstance.IsEmpty())
	{
		AfxMessageBox(_T("请输入SDE服务器实例"));
		return;
	}

	if (strUsername.IsEmpty())
	{
		AfxMessageBox(_T("请输入用户名"));
		return;
	}

	if (strPassword.IsEmpty())
	{
		AfxMessageBox(_T("请输入密码"));
		return;
	}

	if (strVersion.IsEmpty())
	{
		AfxMessageBox(_T("请输入版本信息"));
		return;
	}

	if (SdeConnection.ConnectToSDE(strServer, strInstance, strDatabase, strUsername, strPassword, strVersion, &m_Workspace) == S_OK)
	{
		AfxMessageBox(_T("Connection Succeeded"));
		CButton*	pOK = (CButton*)GetDlgItem(IDOK);
		pOK->EnableWindow();
	}
	else
	{
		char							szError[128] = {0};
		sprintf_s(szError, "连接IP为%s的服务器失败!", strServer);
		LOGSTR(szError);
		AfxMessageBox(_T("Connection Failed"));
	}

}

CString CDeuSDEConnectProperty::GetConnString() const
{
	return strServer;
}

void CDeuSDEConnectProperty::SetParam(STR_SDE_PARAM param)
{
	m_param = param;
}

void CDeuSDEConnectProperty::InitCtrls()
{
	 	m_edit_server.SetWindowText(m_param.strServer);
	 	m_edit_service.SetWindowText(m_param.strService);
	 	m_edit_database.SetWindowText(m_param.strDatabase);
	 	m_edit_username.SetWindowText(m_param.strUsername);
	 	m_edit_password.SetWindowText(m_param.strPassword);
	 	
		if (!m_param.strVersion.IsEmpty())
		{
			m_edit_version.SetWindowText(m_param.strVersion);
		}
}

STR_SDE_PARAM CDeuSDEConnectProperty::GetParam()
{
	STR_SDE_PARAM	param;
	param.strServer = strServer;
	param.strService = strInstance;
	param.strDatabase = strDatabase;
	param.strUsername = strUsername;
	param.strPassword = strPassword;
	param.strVersion = strVersion;

	return param;
}
