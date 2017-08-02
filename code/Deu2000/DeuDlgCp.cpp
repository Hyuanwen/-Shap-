// DeuDlgCp.cpp : 实现文件
//

#include "stdafx.h"
#include "DeuDlgCp.h"

// CDeuDlgCp 对话框
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

// CDeuDlgCp 消息处理程序
BOOL CDeuDlgCp::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(IsUpdate)
	{
		this->SetWindowText("修改控制点");
	}
	else
	{
		this->SetWindowText("增加控制点");
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
