// H:\04 代码\06 投影转换工具\Source\src\Deu2000\CDeuDlgExcel.cpp : 实现文件

#include "stdafx.h"
#include "DeuDlgExcel.h"

// CDeuDlgExcel 对话框
IMPLEMENT_DYNAMIC(CDeuDlgExcel, CDialog)
CDeuDlgExcel::CDeuDlgExcel(CWnd* pParent /*=NULL*/)
	: CDialog(CDeuDlgExcel::IDD, pParent)
	, m_in_d(_T(""))
	, m_lbt(0)
{
}

CDeuDlgExcel::~CDeuDlgExcel()
{
}

void CDeuDlgExcel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IN_D, m_in_d);
	DDX_Text(pDX, IDC_EDIT_IN_L, m_in_l);
	DDX_Text(pDX, IDC_EDIT_IN_H, m_in_h);
	DDX_Text(pDX, IDC_EDIT_OUT_D, m_out_d);
	DDX_Text(pDX, IDC_EDIT_OUT_L, m_out_l);
	DDX_Text(pDX, IDC_EDIT_OUT_H, m_out_h);
	DDX_Text(pDX, IDC_EDIT_OUT_BT, m_lbt);
}

BEGIN_MESSAGE_MAP(CDeuDlgExcel, CDialog)
	ON_BN_CLICKED(IDOK, &CDeuDlgExcel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDeuDlgExcel::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CDeuDlgExcel::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_in_d.Format(_T("%s"), src_x.c_str());
    m_in_l.Format(_T("%s"), src_y.c_str());
	m_in_h.Format(_T("%s"), src_z.c_str());

    m_out_d.Format(_T("%s"), des_x.c_str());
    m_out_l.Format(_T("%s"), des_y.c_str());
    m_out_h.Format(_T("%s"), des_z.c_str());

    m_lbt = lbt;

	UpdateData(FALSE);

	return TRUE;
}

void CDeuDlgExcel::OnBnClickedOk()
{
	UpdateData(TRUE);

    src_x = m_in_d;
	src_y = m_in_l;
	src_z = m_in_h;
	des_x = m_out_d;
	des_y = m_out_l;
	des_z = m_out_h;
    lbt = m_lbt;

	OnOK();
}

void CDeuDlgExcel::OnBnClickedCancel()
{
	OnCancel();
}