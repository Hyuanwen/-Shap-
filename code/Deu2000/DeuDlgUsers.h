#pragma once

#include "resource.h"

class CDeuDlgUsers : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDeuDlgUsers)

public:
	CDeuDlgUsers(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgUsers();

	// �Ի�������
	enum { IDD = IDD_DLG_USERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnUserclose();
	afx_msg void OnBnClickedBtnUsersCreate();
	afx_msg void OnBnClickedBtnUsersUpdate();
	afx_msg void OnBnClickedBtnUsersDel();
	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_ListUser;
	
public:
	void LoadAllUser();
	void PowerMerge(CString strGroupId, CStringArray *p_array);
};
