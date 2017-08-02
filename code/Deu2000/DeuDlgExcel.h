#pragma once

#include "resource.h"

// CDeuDlgExcel �Ի���
class CDeuDlgExcel : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgExcel)

public:
	CDeuDlgExcel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgExcel();

	// �Ի�������
	enum { IDD = IDD_DLG_EXCEL };

public:
	string              src_x;
	string              src_y;
	string              src_z;
	string              des_x;
	string              des_y;
	string              des_z;
	int                 lbt;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()

public:
	CString m_in_d;
	CString m_in_l;
	CString m_in_h;
	CString m_out_d;
	CString m_out_l;
	CString m_out_h;
	int     m_lbt;
};
