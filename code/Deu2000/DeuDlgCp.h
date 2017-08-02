#pragma once

#include "resource.h"

class CDeuDlgCp : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgCp)

public:
	CDeuDlgCp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgCp();

	// �Ի�������
	enum { IDD = IDD_DLG_CP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtncpCancel();
	afx_msg void OnBnClickedBtncpOk();
	DECLARE_MESSAGE_MAP()

public:
	BOOL    IsUpdate;
	CString m_X_SRC;
	CString m_Y_SRC;
	CString m_Z_SRC;
	CString m_X_DEST;
	CString m_Y_DEST;
	CString m_Z_DEST;
};
