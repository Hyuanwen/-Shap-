#pragma once
#include "afxwin.h"

// CDeuDlgCpList 对话框
class CDeuDlgCpList : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgCpList)

public:
	CDeuDlgCpList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgCpList();

	// 对话框数据
	enum { IDD = IDD_DLG_CPLIST };

public:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedButtonSetList();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()


public:
	CGridCtrl                            m_Grid;
	int                                  m_CpNum;
	CStructManager<ControlPoint>         m_ControlPoint;
};
