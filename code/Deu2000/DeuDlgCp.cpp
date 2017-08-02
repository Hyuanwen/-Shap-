// DeuDlgCp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DeuDlgCp.h"

// CDeuDlgCp �Ի���
IMPLEMENT_DYNAMIC(CDeuDlgCp, CDialog)
CDeuDlgCp::CDeuDlgCp(CWnd* pParent /*=NULL*/)
	     : CDialog(CDeuDlgCp::IDD, pParent)
{
	IsUpdate = FALSE;
}

CDeuDlgCp::~CDeuDlgCp()
{
}

void CDeuDlgCp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SRC_X, m_X_SRC);
	DDX_Text(pDX, IDC_EDIT_SRC_Y, m_Y_SRC);
	DDX_Text(pDX, IDC_EDIT_SRC_Z, m_Z_SRC);

	DDX_Text(pDX, IDC_EDIT_DEST_X, m_X_DEST);
	DDX_Text(pDX, IDC_EDIT_DEST_Y, m_Y_DEST);
	DDX_Text(pDX, IDC_EDIT_DEST_Z, m_Z_DEST);
}

BEGIN_MESSAGE_MAP(CDeuDlgCp, CDialog)
	ON_BN_CLICKED(IDC_BTNCP_CANCEL, &CDeuDlgCp::OnBnClickedBtncpCancel)
	ON_BN_CLICKED(IDC_BTNCP_OK, &CDeuDlgCp::OnBnClickedBtncpOk)
END_MESSAGE_MAP()

// CDeuDlgCp ��Ϣ�������
BOOL CDeuDlgCp::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(IsUpdate)
	{
		this->SetWindowText("�޸Ŀ��Ƶ�");
	}
	else
	{
		this->SetWindowText("���ӿ��Ƶ�");
	}

	return TRUE;
}

void CDeuDlgCp::OnBnClickedBtncpCancel()
{
	this->OnCancel();
}

void CDeuDlgCp::OnBnClickedBtncpOk()
{
	this->OnOK();
}
