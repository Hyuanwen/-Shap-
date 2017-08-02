// SetTransParams.cpp : 实现文件

#include "stdafx.h"
#include "resource.h"
#include "SetTransParams.h"

IMPLEMENT_DYNAMIC(CSetTransParams, CDialog)
CSetTransParams::CSetTransParams(bool IsVector, bool IsBursa, _Params params, _Params invparams, CWnd* pParent /*=NULL*/)
			   : CDialog(CSetTransParams::IDD, pParent)
{
	m_IsVector = IsVector;
	m_IsBursa = IsBursa;
	m_params = params;
	m_invparams = invparams;
}

CSetTransParams::~CSetTransParams()
{
}

void CSetTransParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_X_SRC, m_Ed_X_Src);
	DDX_Text(pDX, IDC_ED_Y_SRC, m_Ed_Y_Src);
	DDX_Text(pDX, IDC_ED_Z_SRC, m_Ed_Z_Src);
	DDX_Text(pDX, IDC_ED_XO_SRC, m_Ed_XO_Src);
	DDX_Text(pDX, IDC_ED_YO_SRC, m_Ed_YO_Src);
	DDX_Text(pDX, IDC_ED_ZO_SRC, m_Ed_ZO_Src);
	DDX_Text(pDX, IDC_ED_K_SRC, m_Ed_K_Src);
	DDX_Text(pDX, IDC_ED_X_DES, m_Ed_X_Des);
	DDX_Text(pDX, IDC_ED_Y_DES, m_Ed_Y_Des);
	DDX_Text(pDX, IDC_ED_Z_DES, m_Ed_Z_Des);
	DDX_Text(pDX, IDC_ED_XO_DES, m_Ed_XO_Des);
	DDX_Text(pDX, IDC_ED_YO_DES, m_Ed_YO_Des);
	DDX_Text(pDX, IDC_ED_ZO_DES, m_Ed_ZO_Des);
	DDX_Text(pDX, IDC_ED_K_DES, m_Ed_K_Des);
}

BEGIN_MESSAGE_MAP(CSetTransParams, CDialog)
	ON_BN_CLICKED(IDOK, &CSetTransParams::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CSetTransParams::OnInitDialog()
{
	CDialog::OnInitDialog();

	//初始化参数
	InitParams(m_params, m_invparams);

	if (m_IsVector)
	{
		GetDlgItem(IDC_ED_X_DES)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED_Y_DES)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED_Z_DES)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED_XO_DES)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED_YO_DES)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED_ZO_DES)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED_K_DES)->EnableWindow(FALSE);
		
		if (!m_IsBursa)
		{
	 		GetDlgItem(IDC_ED_Z_SRC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ED_ZO_SRC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ED_K_SRC)->EnableWindow(FALSE);
		}
	}
	else
	{
		if (!m_IsBursa)
		{
			GetDlgItem(IDC_ED_Z_SRC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ED_ZO_SRC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ED_K_SRC)->EnableWindow(FALSE);

			GetDlgItem(IDC_ED_Z_DES)->EnableWindow(FALSE);
			GetDlgItem(IDC_ED_ZO_DES)->EnableWindow(FALSE);
			GetDlgItem(IDC_ED_K_DES)->EnableWindow(FALSE);
		}
	}

	return TRUE;
}

void CSetTransParams::GetTransParams(double* params)
{
	if (m_IsBursa)
	{
		//获取七参数
		params[0] = m_Ed_X_Src;
		params[1] = m_Ed_Y_Src;
		params[2] = m_Ed_Z_Src;
		params[3] = m_Ed_XO_Src;
		params[4] = m_Ed_YO_Src;
		params[5] = m_Ed_ZO_Src;
		params[6] = m_Ed_K_Src;
	}
	else
	{
		//获取四参数
		params[0] = m_Ed_X_Src;
		params[1] = m_Ed_Y_Src;
		params[2] = m_Ed_XO_Src;
		params[3] = m_Ed_YO_Src;
	}
}

void CSetTransParams::GetTransInvParams(double* params)
{
	if (m_IsBursa)
	{
		//获取七参数
		params[0] = m_Ed_X_Des;
		params[1] = m_Ed_Y_Des;
		params[2] = m_Ed_Z_Des;
		params[3] = m_Ed_XO_Des;
		params[4] = m_Ed_YO_Des;
		params[5] = m_Ed_ZO_Des;
		params[6] = m_Ed_K_Des;
	}
	else
	{
		//获取四参数
		params[0] = m_Ed_X_Des;
		params[1] = m_Ed_Y_Des;
		params[2] = m_Ed_XO_Des;
		params[3] = m_Ed_YO_Des;
	}
}

void CSetTransParams::OnBnClickedOk()
{
	CString str;

 	if (m_IsVector)
 	{
		GetDlgItem(IDC_ED_X_SRC)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_Y_SRC)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_XO_SRC)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_YO_SRC)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		if (!m_IsBursa)
		{
			GetDlgItem(IDC_ED_Z_SRC)->SetWindowText(_T("0"));
			GetDlgItem(IDC_ED_ZO_SRC)->SetWindowText(_T("0"));
			GetDlgItem(IDC_ED_K_SRC)->SetWindowText(_T("0"));

		}
		else
		{
			GetDlgItem(IDC_ED_Z_SRC)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}

			GetDlgItem(IDC_ED_ZO_SRC)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}

			GetDlgItem(IDC_ED_K_SRC)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}
		}

		GetDlgItem(IDC_ED_X_DES)->SetWindowText(_T("0"));
		GetDlgItem(IDC_ED_Y_DES)->SetWindowText(_T("0"));
		GetDlgItem(IDC_ED_Z_DES)->SetWindowText(_T("0"));
		GetDlgItem(IDC_ED_XO_DES)->SetWindowText(_T("0"));
		GetDlgItem(IDC_ED_YO_DES)->SetWindowText(_T("0"));
		GetDlgItem(IDC_ED_ZO_DES)->SetWindowText(_T("0"));		
		GetDlgItem(IDC_ED_K_DES)->SetWindowText(_T("0"));
 	}
 	else
 	{
		GetDlgItem(IDC_ED_X_SRC)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_Y_SRC)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_XO_SRC)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_YO_SRC)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_X_DES)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_Y_DES)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_XO_DES)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		GetDlgItem(IDC_ED_YO_DES)->GetWindowText(str);
		if (str.IsEmpty())
		{
			AfxMessageBox(_T("不能为空"));
			return;
		}

		if (m_IsBursa)
		{
			GetDlgItem(IDC_ED_Z_SRC)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}

			GetDlgItem(IDC_ED_ZO_SRC)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}

			GetDlgItem(IDC_ED_K_SRC)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}

			GetDlgItem(IDC_ED_Z_DES)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}

			GetDlgItem(IDC_ED_ZO_DES)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}

			GetDlgItem(IDC_ED_K_DES)->GetWindowText(str);
			if (str.IsEmpty())
			{
				AfxMessageBox(_T("不能为空"));
				return;
			}
		}

 		if(!m_IsBursa)
 		{
 			GetDlgItem(IDC_ED_Z_SRC)->SetWindowText(_T("0"));
 			GetDlgItem(IDC_ED_ZO_SRC)->SetWindowText(_T("0"));
 			GetDlgItem(IDC_ED_K_SRC)->SetWindowText(_T("0"));
 
 			GetDlgItem(IDC_ED_Z_DES)->SetWindowText(_T("0"));
 			GetDlgItem(IDC_ED_ZO_DES)->SetWindowText(_T("0"));		
 			GetDlgItem(IDC_ED_K_DES)->SetWindowText(_T("0"));
 		}
 	}

	OnOK();
}

void CSetTransParams::InitParams(_Params params, _Params invParams)
{
	GetDlgItem(IDC_ED_X_SRC)->SetWindowText(params.strXSrc);
	GetDlgItem(IDC_ED_Y_SRC)->SetWindowText(params.strYSrc);
	GetDlgItem(IDC_ED_Z_SRC)->SetWindowText(params.strZSrc);
	GetDlgItem(IDC_ED_XO_SRC)->SetWindowText(params.strX0Src);
	GetDlgItem(IDC_ED_YO_SRC)->SetWindowText(params.strY0Src);
	GetDlgItem(IDC_ED_ZO_SRC)->SetWindowText(params.strZ0Src);
	GetDlgItem(IDC_ED_X_DES)->SetWindowText(invParams.strXSrc);
	GetDlgItem(IDC_ED_Y_DES)->SetWindowText(invParams.strYSrc);
	GetDlgItem(IDC_ED_Z_DES)->SetWindowText(invParams.strZSrc);
	GetDlgItem(IDC_ED_XO_DES)->SetWindowText(invParams.strX0Src);
	GetDlgItem(IDC_ED_YO_DES)->SetWindowText(invParams.strY0Src);
	GetDlgItem(IDC_ED_ZO_DES)->SetWindowText(invParams.strZ0Src);
	GetDlgItem(IDC_ED_K_SRC)->SetWindowText(params.strKSrc);
	GetDlgItem(IDC_ED_K_DES)->SetWindowText(invParams.strKSrc);

	//UpdateData();
}

