#pragma once

#include "resource.h"

class CDeuDlgLogin : public CXTPDialog
{
	DECLARE_DYNAMIC(CDeuDlgLogin)

public:
	CDeuDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeuDlgLogin();

	// 对话框数据
	enum { IDD = IDD_DLG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnCancel();
	DECLARE_MESSAGE_MAP()

public:
	CButton   m_btnLogin;
	CComboBox m_Edit_Account;
	CEdit     m_Edit_Userpwd;
	CString   m_sEdit_Account;
    CString   m_sEdit_Userpwd;
};
