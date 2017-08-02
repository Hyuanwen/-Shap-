#pragma once

#include "resource.h"

class CDeuDlgUserGroups : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgUserGroups)

public:
	CDeuDlgUserGroups(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgUserGroups();

	// 对话框数据
	enum { IDD = IDD_DLG_USERGROUPS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedBtnCreateUgroup();
	afx_msg void OnBnClickedBtnUpdateUgroup();
	afx_msg void OnBnClickedBtnCancelUgroup();
	afx_msg void OnBnClickedBtnDelUgroup();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	
public:
	CTreeCtrl  m_TreeUGroup;
	CString    m_strDesc[6];
	CImageList m_ImgList;

public:
	void LoadTreeCtrl(bool IsInit=FALSE);
};
