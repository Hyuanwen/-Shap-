/////////////////////////////////////////////////////////////////////
//     ��Ŀ: �����ǻ�ת�����
//     ����:	�û�ά������
//     ���ߣ�	hushichen
//     �޸��ߣ�	----
//     CopyRight 2010 ljdy Corporation All Rights Reserved
/////////////////////////////////////////////////////////////////////

#pragma once
#include "resource.h"

class CDeuDlgUsersOpera : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgUsersOpera)

public:
	CDeuDlgUsersOpera(CWnd* pParent = NULL, DWORD m_dwType=1);   // ��׼���캯��
	virtual ~CDeuDlgUsersOpera();

	// �Ի�������
	enum { IDD = IDD_DLG_USERS_OPERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnUsersSave();
	afx_msg void OnBnClickedBtnUsersCancel();
	afx_msg void OnBnClickedBtnUroleSelect();
	afx_msg void OnBnClickedBtnUroleSelectall();
	afx_msg void OnBnClickedBtnUroleRemove();
	afx_msg void OnBnClickedBtnUroleRemoveall();
	DECLARE_MESSAGE_MAP()

public:
	/* ���ڲ������� 1. ���� 2.���� */
	DWORD m_dwWndType;

	/* �û���ǰ���˺ţ�������Ŀ������ȫ�ֲ����� */
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
