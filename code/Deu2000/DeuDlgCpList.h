#pragma once
#include "afxwin.h"

// CDeuDlgCpList �Ի���
class CDeuDlgCpList : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlgCpList)

public:
	CDeuDlgCpList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlgCpList();

	// �Ի�������
	enum { IDD = IDD_DLG_CPLIST };

public:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedButtonSetList();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()


public:
	CGridCtrl                            m_Grid;
	int                                  m_CpNum;
	CStructManager<ControlPoint>         m_ControlPoint;
};
