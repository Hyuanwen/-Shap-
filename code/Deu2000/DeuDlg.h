#pragma once


#include "resource.h"


class CDeuDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlg)

public:
	CDeuDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlg();

// 对话框数据
	enum { IDD = IDD_DEUDLG };

public:
	CXTPDockingPaneManager m_paneManager;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持	
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();


};
