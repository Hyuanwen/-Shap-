#pragma once


#include "resource.h"


class CDeuDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeuDlg)

public:
	CDeuDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuDlg();

// �Ի�������
	enum { IDD = IDD_DEUDLG };

public:
	CXTPDockingPaneManager m_paneManager;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��	
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();


};
