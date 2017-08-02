// DeuDlgGridSetting.cpp : 实现文件

#include "stdafx.h"
#include "DeuDlgGridSetting.h"
#include "DeuFunction.h"
#include "DeuGlobalParam.h"

// CDeuDlgGridSetting 对话框
IMPLEMENT_DYNAMIC(CDeuDlgGridSetting, CDialog)
void CDeuDlgGridSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX,IDC_PROID,mt_ProId);
	DDX_Text(pDX,IDC_PWD, mt_pwd);
	DDX_Control(pDX, IDC_COMBO_PRONAME, m_cbProname);
	DDX_Control(pDX, IDC_COMBO_FX, m_cbFx);
}

BEGIN_MESSAGE_MAP(CDeuDlgGridSetting, CDialog)
	ON_BN_CLICKED(IDOK, &CDeuDlgGridSetting::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_PRONAME, &CDeuDlgGridSetting::OnCbnSelchangeComboProName)
	ON_CBN_SELCHANGE(IDC_COMBO_FX, &CDeuDlgGridSetting::OnCbnSelchangeComboFx)
END_MESSAGE_MAP()


CDeuDlgGridSetting::CDeuDlgGridSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDeuDlgGridSetting::IDD, pParent)
	,mt_ProId("")
	,mt_pwd("")
    ,mt_Fx("")
	,mt_ProName("")
{
}

CDeuDlgGridSetting::~CDeuDlgGridSetting()
{
}

BOOL CDeuDlgGridSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	//省号
	for(int n=0; n<_Proname_num; n++)
	{
		m_cbProname.InsertString( n , sz_Proname[n] );
	}
	
	m_cbProname.SetCurSel( 0 );
	m_cbProname.EnableWindow(TRUE);

	//方向
	for(int n=0; n<_Fx_num; n++)
	{
		m_cbFx.InsertString( n , sz_Fx[n]);
	}
	m_cbFx.SetCurSel( 0 );

	//m_cbFx.EnableWindow(TRUE);
	m_cbFx.ShowWindow(SW_HIDE);

	UpdateData(FALSE);

	return TRUE;
}

void CDeuDlgGridSetting::OnBnClickedOk()
{
	/*
	BSTR ProId = ::SysAllocString((LPCWSTR)_T("")) ;
	BSTR pwd = ::SysAllocString((LPCWSTR)_T(""));
	BSTR Fx = ::SysAllocString((LPCWSTR)_T(""));
	BSTR ProName = ::SysAllocString((LPCWSTR)_T(""));

	int ret = InitGridSetting( ProName , ProId , pwd , Fx );
	
	m_ProId = ProId;
	m_pwd = pwd;
	m_Fx = Fx;
	m_ProName = ProName;

	this->OnOK() ;
	*/

    UpdateData(TRUE);

	CComboBox* p_combox1 = (CComboBox*)GetDlgItem(IDC_COMBO_PRONAME);
	p_combox1->GetWindowText(mt_ProName);

	/*
	CComboBox* p_combox2 = (CComboBox*)GetDlgItem(IDC_COMBO_FX);
	p_combox2->GetWindowText(mt_Fx);
	*/

	OnOK();
}

void CDeuDlgGridSetting::OnCbnSelchangeComboProName()
{

}

void CDeuDlgGridSetting::OnCbnSelchangeComboFx()
{

}

//做一些格网初始化的工作...
//int	CDeuDlgGridSetting::InitGridSetting( /*out*/BSTR & ProName ,/*out*/BSTR &  ProId , /*out*/BSTR & pwd , /*out*/BSTR & Fx )
//{
//	UpdateData();
//
//	//BSTR ProName;
//	CString strProName,strFx,m_ProId,m_pwd;
//	/*BSTR Fx ;
//	BSTR ProId;
//	BSTR pwd;*/
//
//	CComboBox* p_combox1 = (CComboBox*)GetDlgItem(IDC_COMBO_PRONAME);
//	p_combox1->GetWindowText(strProName);
//	ProName = strProName.AllocSysString();
//
//	CComboBox* p_combox2 = (CComboBox*)GetDlgItem(IDC_COMBO_FX);
//	p_combox2->GetWindowText(strFx);
//	Fx = strFx.AllocSysString();
//
//	ProId = mt_ProId.AllocSysString();
//	pwd = mt_pwd.AllocSysString();
//
//	return 0;
//}