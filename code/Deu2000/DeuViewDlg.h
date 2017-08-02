#pragma once


#include "Resource.h"
#include "afxcmn.h"

class CDeuViewDlg : public CXTPDialog
{
	DECLARE_DYNAMIC(CDeuViewDlg)

public:
	CDeuViewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuViewDlg();

// 对话框数据 
	enum { IDD = IDD_DLG_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);	
};
