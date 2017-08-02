#pragma once

#include "resource.h"

class CDeuDlgUserGroupsOpera : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgUserGroupsOpera)

public:
	CDeuDlgUserGroupsOpera(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgUserGroupsOpera();

	// 对话框数据
	enum { IDD = IDD_DLG_USERGROUPS_OPERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnUgroupSave();
	afx_msg void OnBnClickedBtnUgroupCancel();
	DECLARE_MESSAGE_MAP()

public:
	/* 选中的节点名称 */
	CString m_strSelectedName;
	CString m_UserGroupName;
	DWORD   m_nStatus;

	CButton m_ChkSg_C;
	CButton m_ChkSl_C; 
	CButton m_ChkDb_C;
	CButton m_ChkSg_E;
	CButton m_ChkSl_E;
	CButton m_ChkDb_E;
	CEdit   m_edit_ugroup;
};
