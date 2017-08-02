// DeuDlgOracle.cpp : ʵ���ļ�

#include "stdafx.h"
#include "DeuDlgOracle.h"
#include "DeuGlobal.h"

// CDeuDlgOracle �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgOracle, CDialog)
CDeuDlgOracle::CDeuDlgOracle(TranformType _ParentType, CWnd* pParent /*=NULL, */, BOOL IsOut)
			  :CDialog(CDeuDlgOracle::IDD, pParent)
{
	_TType = _ParentType;
	switch (_ParentType)
	{
	case VECTOR:
		p_Parent_Vector = (CDeuVectorTranDlg*)pParent;
		break;

	case RASTER:
		p_Parent_Raster = (CDeuRasterTranDlg*)pParent;
		break;
	}
	_IsOut = IsOut;
}

CDeuDlgOracle::~CDeuDlgOracle()
{
}

void CDeuDlgOracle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ORA_USERS, m_ora_user);
	DDX_Control(pDX, IDC_EDIT_ORA_PWD, m_ora_pwd);
	DDX_Control(pDX, IDC_EDIT_ORA_SID, m_ora_sid);
}

BEGIN_MESSAGE_MAP(CDeuDlgOracle, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CDeuDlgOracle::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CONNTEST, &CDeuDlgOracle::OnBnClickedBtnConntest)
END_MESSAGE_MAP()

// CDeuDlgOracle ��Ϣ�������
BOOL CDeuDlgOracle::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

void CDeuDlgOracle::OnBnClickedBtnOk()
{
	if(!_IsOut)
	{
		if(IsConnectOracle(TRUE))
		{	
			this->OnOK();
		}
	}
	else if(_IsOut)
	{
		if(IsConnectOracle(FALSE))
		{	
			this->OnOK();
		}
	}
}

void CDeuDlgOracle::OnBnClickedBtnConntest()
{
	if(IsConnectOracle())
	{
		MessageBox("���ӳɹ�!", "ϵͳ��ʾ", MB_OK|MB_ICONINFORMATION);
	}
}

//����ͻ�����64λORACLE�ͻ��ˣ�conn->Open����ʧ��
//�о�OCCI�������ݿ⣬conn->Open�������ӳɹ�
//����gdal��OGRSFDriverRegistrar::Openʱ����Ȼ��Ҫnet�������������ӳɹ��������޸�gdalԴ��ſɣ��ʴ˴���Ȼ��oci����
BOOL CDeuDlgOracle::IsConnectOracle(BOOL IsFill)
{
	m_ora_sid.GetWindowText(strSID);
	m_ora_user.GetWindowText(strUser);
	m_ora_pwd.GetWindowText(strPwd);

	_ConnectionPtr conn;
	conn.CreateInstance(__uuidof(Connection));

	try
	{		
		HRESULT hr = conn->Open((_bstr_t)("Provider=oraoledb.oracle.1; user id="+strUser+"; password="+strPwd+"; Data Source="+strSID+"; persist security info=false"), (_bstr_t)strUser, (_bstr_t)strPwd, adConnectUnspecified);
		if(FAILED(hr))
		{			
			MessageBox("����ʧ��!", "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
			return FALSE;
		}
	
		strConn = "Provider=oraoledb.oracle.1; Data Source="+strSID+"; User Id="+strUser+"; Password="+strPwd+"; persist security info=false";

		if(IsFill)
		{
			_RecordsetPtr rst = conn->Execute("select * from tabs", NULL, adCmdText);
			
			rst->MoveFirst();
			while(!rst->_EOF)
			{
				switch (_TType)
				{
				case VECTOR:
					{
						p_Parent_Vector->_TablesList.Add(rst->GetCollect("TABLE_NAME"));
					}
					break;
				case RASTER:
					{
						p_Parent_Raster->_TablesList.Add(rst->GetCollect("TABLE_NAME"));
					}
					break;
				}

				rst->MoveNext();
			}

			rst->Close();
		}
		
		conn->Close();
	}
	catch(_com_error e) 
	{ 				
		MessageBox("����ʧ��:\r\n    "+e.Description(), "ϵͳ��ʾ", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

BOOL CDeuDlgOracle::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnBnClickedBtnOk();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
