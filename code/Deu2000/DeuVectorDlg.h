#pragma once


#include "Resource.h"





class CDeuVectorDlg : public CXTPDialog
{
	DECLARE_DYNAMIC(CDeuVectorDlg)

public:
	CDeuVectorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeuVectorDlg();

// �Ի�������
	enum { IDD = IDD_DLG_VECTOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CXTPTabControl m_wndTabControl;
	//CDeuPaneVector m_PaneVector;
	//CXTPDockingPaneManager m_paneManager;	
	CEdit m_wndPanes[7];

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	LRESULT OnDockingPaneNotify(WPARAM wParam, LPARAM lParam);

};
