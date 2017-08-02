/////////////////////////////////////////////////////////////////////
//     项目: 德毅智慧转换软件
//     描述:	用户维护窗口
//     作者：	hushichen
//     修改者：	----
//     CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////

#pragma once
#include "resource.h"

class CDeuDlgUsersOpera : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgUsersOpera)

public:
	CDeuDlgUsersOpera(CWnd* pParent = NULL, DWORD m_dwType=1);   // 标准构造函数
	virtual ~CDeuDlgUsersOpera();

	// 对话框数据
	enum { IDD = IDD_DLG_USERS_OPERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnUsersSave();
	afx_msg void OnBnClickedBtnUsersCancel();
	afx_msg void OnBnClickedBtnUroleSelect();
	afx_msg void OnBnClickedBtnUroleSelectall();
	afx_msg void OnBnClickedBtnUroleRemove();
	afx_msg void OnBnClickedBtnUroleRemoveall();
	DECLARE_MESSAGE_MAP()

public:
	/* 窗口操作类型 1. 增加 2.更新 */
	DWORD m_dwWndType;

	/* 用户当前的账号，保留的目的是做全局操作用 */
	CString m_strCurName;

	CEdit    m_username;
	CEdit    m_userpwd;
	CListBox m_list_src;
	CListBox m_list_dest;
	CButton  m_btn_select;
	CButton  m_btn_selectall;
	CButton  m_btn_remove;
	CButton  m_btn_removeall;
	CButton  m_btn_save;
};
