#pragma once

#include "resource.h"

class CDeuDlgUserGroupsOpera : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgUserGroupsOpera)

public:
	CDeuDlgUserGroupsOpera(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgUserGroupsOpera();

	// �Ի�������
	enum { IDD = IDD_DLG_USERGROUPS_OPERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnUgroupSave();
	afx_msg void OnBnClickedBtnUgroupCancel();
	DECLARE_MESSAGE_MAP()

public:
	/* ѡ�еĽڵ����� */
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
