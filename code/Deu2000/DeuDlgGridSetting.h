#pragma once
#include "resource.h"

// CDeuDlgGridSetting 对话框

class CDeuDlgGridSetting : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgGridSetting)

public:
	CDeuDlgGridSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgGridSetting();

	// 对话框数据
	enum { IDD =IDD_DLG_GRIDSETTING  };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboProName();
	afx_msg void OnCbnSelchangeComboFx();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	//定义存放的公共数据
	//BSTR m_ProId;
	//BSTR m_pwd;
	//BSTR m_Fx;
	//BSTR m_ProName;

	CString   mt_ProId;
	CString   mt_pwd;
	CString   mt_Fx;
	CString   mt_ProName;
	CComboBox m_cbProname;
	CComboBox m_cbFx;
	
//public:
	//做一些格网初始化的工作...
	//int	InitGridSetting( /*out*/BSTR  &ProName ,/*out*/BSTR  &ProId , /*out*/BSTR  &pwd , /*out*/BSTR  &Fx );
};
